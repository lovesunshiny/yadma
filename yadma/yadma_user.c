/*****************************************************************************/
/**
*
* @file yadma_user.c
*
* This header file contains user space API implementation.
* MODIFICATION HISTORY:
*
* Ver   Date     Changes
* ----- -------- -------------------------------------------------------
* 1.0   5/15/12  First version
*
******************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <poll.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/user.h>
#include <signal.h>

#include <linux/genetlink.h>
#include <sys/mman.h>
#include <time.h>

#include "yadma.h"
#include "yadma_user.h"
#include "yadma_proc.h"
#include "hexdump_user.h"
#include "yadma_api.h"


//#define DUMP_NETLINK_DATA

/* The DMA channel management structure in user space,
 * It should be coherent with kernel space.
 */
typedef struct
{
	int file_desc;			/* File descriptor */
	char* user_space_addr; /* The memory belongs to a channel are physical continous
								and mmapped to user space as this*/
    /* Save user space address for each block */
    char* user_space_addr_array[YADMA_BLOCK_COUNT];
	int slot_size;			/* The Slot size of all blocks are same */
	int slot_count;			/* How many slots each block has */
	int block_size;			/* The Block size */
	int block_count;		/* The Block count */
	int chan;				/* Channel Index */
	int cur_block;			/* Current block using by user space */
	int cur_slot;			/* Current slot using by user space */
	int k_block;			/* Last block reported by kernel interrupt */
	int k_slot;				/* Last slot reported by kernel interrupt */
    int k_frame;            /* Last frame number reported by kernel interrupt */
} DmaChannel;


#define DMA_PARAM_CHECK(p, min, max) \
	do { \
		if(p >= min && p< max){ /* Do nothing */} \
		else { \
			logMsg("%s:Invallid Paramter %s = %d\n!", __FUNCTION__, #p, p); \
			return NULL; \
		} \
	} while(0)

#define DMA_PARAM_CHECK_VOID(p, min, max) \
	do { \
		if(p >= min && p< max){ /* Do nothing */} \
		else { \
			logMsg("%s:Invallid Paramter %s = %d\n!", __FUNCTION__, #p, p); \
			return; \
		} \
	} while(0)


/* Variables shared in File range */
static DmaChannel yadmaChans[MAX_CHANS];
static int yadmaInitialized = false;
static int sock_fd = -1;
static struct sockaddr_nl src_addr;
static struct sockaddr_nl dest_addr;
static KucMessage* yadmaIntrKuc;
static short *demo_buffer = NULL;
static short *sample_data = NULL;
int sample_fd = -1;


static int is_valid_dma_channel(int ch)
{
    if(yadmaChans[ch].user_space_addr == NULL || yadmaChans[ch].file_desc == -1 || yadmaChans[ch].user_space_addr == 0xFFFFFFFF)
        return false;
    else
        return true;
}

int DriverInit(void)
{
	int i;
    InitPcieKuc();
    memset(&yadmaChans, 0, sizeof(yadmaChans));
	for(i = 0; i < MAX_CHANS; i++) {
		yadmaChans[i].slot_count = YADMA_SLOT_COUNT;
		yadmaChans[i].slot_size = YADMA_SLOT_SIZE;
		yadmaChans[i].block_count = YADMA_BLOCK_COUNT;
		yadmaChans[i].block_size = YADMA_SLOT_COUNT*YADMA_SLOT_SIZE;
		yadmaChans[i].user_space_addr = NULL;
		yadmaChans[i].file_desc = -1;
        yadmaChans[i].cur_block = 0;
        yadmaChans[i].cur_slot = 0;
        yadmaChans[i].k_slot = 0;
        yadmaChans[i].k_slot = 0;
	}

	sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
	if(sock_fd < 0) {
		logMsg("Netlink socket create failed %d!\n", sock_fd);
	} else {
		logMsg("Netlink socket %d is created.\n", sock_fd);
	}

	/* Bind source address */
	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = getpid(); /* self pid */
	bind(sock_fd, (struct sockaddr*)&src_addr, sizeof(src_addr));

	/* Set Dest address */
	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.nl_family = AF_NETLINK;
	dest_addr.nl_pid = 0; /* For Linux Kernel */
	dest_addr.nl_groups = 0; /* unicast */

    yadmaIntrKuc = malloc(MAX_PAYLOAD);
    if(!yadmaIntrKuc){
        logMsg("Allocate global KUC struture failed!\n");
    } else {
		memset(yadmaIntrKuc, 0, MAX_PAYLOAD);
		yadmaIntrKuc->len = NLMSG_SPACE(sizeof(KucMessage) + sizeof(RegsiterStruct));
		yadmaIntrKuc->type = KUC_TYPE_REGISTER;
		RegsiterStruct *ds = (DemoStruct*)yadmaIntrKuc->data;
		ds->id = 0x11111; /* magic number */
		strncpy(ds->name, "yadma user", 32);
		/* Register pid to kernel */
		Send2KernelByNetLink(yadmaIntrKuc);
    }

#ifdef PYTHON_INTERFACE_DEBUG
	demo_buffer = malloc(YADMA_FRAME_SIZE);
	if(!demo_buffer)
	{
		logMsg("Allocate the demo buffer failed.\n");
	}

	sample_fd = open("sample.dat",O_RDWR);
	sample_data = mmap(0, YADMA_SAMPLE_FILE_SIZE, PROT_READ, MAP_SHARED, sample_fd, 0);

	if(!sample_data)
	{
		logMsg("mmap 'sample.dat' failed.\n");
	}

#endif

	yadmaInitialized = true;
	return true;
}

/* Caller's Guide:
 *
 * 1. Allocate a KuMessage like
 *    KucMessage *pmsg = malloc(NLMSG_SPACE(sizeof(KucMessage) + PlayloadLength));
 *
 * 2. Type convert KucMessage to specific type. e.g:
 *    GainStru *gain = (GainStru*)pmsg->data;
 *
 * 3. Fill in type specific Structure's and KucMessage
 *    gain->path = TX1;
 * 	  pmsg->len = sizeof(GainStru) + KUC_COMMAND_FIELD_LENGTH;
 *
 * 4. Send it using the function below.
 */

static	struct iovec send_iov;
static	struct msghdr send_msg;
int Send2KernelByNetLink(KucMessage* kuc)
{
	ASSERT(kuc->len <= MAX_PAYLOAD);

	kuc->nlh.nlmsg_len = kuc->len;
	kuc->nlh.nlmsg_pid = getpid();
	kuc->nlh.nlmsg_flags = 0;

	send_iov.iov_base = (void *)&(kuc->nlh);
	send_iov.iov_len = kuc->nlh.nlmsg_len;
	send_msg.msg_name = (void *)&dest_addr;
	send_msg.msg_namelen = sizeof(dest_addr);
	send_msg.msg_iov = &send_iov;
	send_msg.msg_iovlen = 1;

	int ret;
	ret = sendmsg(sock_fd, &send_msg, 0);
	if ( ret < 0) {
		logMsg("Error: sendmsg % bytes, return %d!\n", send_msg.msg_iov->iov_len, errno);
	}
	return ret;
}

int RecvFromKernelFromNetLink(KucMessage* kuc)
{

	int len;

	struct iovec iov;

	/*save the address that message will be received from it */
	struct sockaddr_nl sa;
	struct msghdr msg;
	struct nlmsghdr *nh;

	/* kuc->len is the lenght of a specific structure at data[0] + nlmsg header length */
	kuc->nlh.nlmsg_len = kuc->len;

	iov.iov_base = (void *)&(kuc->nlh); /* where is the base */
	iov.iov_len = kuc->nlh.nlmsg_len;  /* the whole length */

	 /* to save the sender's address */
	msg.msg_name = (void *)&sa;
	msg.msg_namelen = sizeof(sa);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

#ifdef DUMP_NETLINK_DATA
	logMsg("Waiting for message from kernel...\n");
#endif

	/* return the total length of received message, including nlmsghdr */
	len = recvmsg(sock_fd, &msg, 0);

#if SUPPORT_MULTIPLE_PART
	/* msg --> iov --> nlmsghdr -- in front of --> KucMessage */
	for (nh = (struct nlmsghdr *)kuc ; NLMSG_OK (nh, len); len-= nh->nlmsg_len, nh = NLMSG_NEXT (nh, len)) {
		/* The end of multipart message. */
		if (nh->nlmsg_type == NLMSG_DONE) {
			return; /* TODO: should jump to msg_handler belowing */
		}

		if (nh->nlmsg_type == NLMSG_ERROR) {
			/* Do some error handling. */

		}
		/* Continue with parsing payload. */
		...
	}
#endif

msg_handler:

	if (len == 0) {
		logMsg("Zero Length Message received?\n");
	}
	else if (len == -1) {
		logMsg("Error occured? Number is %d.\n", errno);
	}
	else {
#ifdef DUMP_NETLINK_DATA
		logMsg("Received netlink message: type = %d, len = %d \n", kuc->type, len);
		print_hex_dump_bytes("@", DUMP_PREFIX_ADDRESS, kuc, len);
#endif
		switch(kuc->type)
		{

		}
	}
	
	return len;
}

static int parse_bar_operation(BarOpStru *bop)
{
    int ret = 0;
	RegPair* rp = bop->data;
	if(bop->count <=0 || bop->count > 128)
		return false;
		
	if((unsigned int)bop->bar < MAX_BARS) {
		int i;
        for(i = 0; i < bop->count; i++) {
            ret = 1;
            if(bop->op == KUC_BAR_OP_READ) {
                log_verbose("Rresp REG%x=VAL%x\n", rp->reg, rp->value);
            } else if(bop->op == KUC_BAR_OP_WRITE) {
                log_verbose("Wresp REG%x=VAL%x\n", rp->reg, rp->value);
            } else {
                log_verbose("Unknown BAR operation\n");
                ret = 0;
                break;
            }
            rp++;
        }
	} else {
        log_verbose("Unknown BAR Number.\n");
    }
    return ret;
}
/* return the interrrupt mask that identify which interrupt occured
 *  and output parameters frame/slot number */
int WaitForInterrupt(int *fn, int *sn, int *bl)
{
    int len, ret;
    static add = 0;
    long tmp1,tmp2,tmp3;
    int coars_freq_est_value, fine_freq_est_value,freq_est_value;
    signed short sync_status,coars_freq_est,fine_freq_est,timing_est,freq_est;
    struct timespec now;
    static int slot = 0;
#ifndef PYTHON_INTERFACE_DEBUG
    if(yadmaInitialized == true) {
        len = RecvFromKernelFromNetLink(yadmaIntrKuc);
        if(len > 0) {			
            if(yadmaIntrKuc->type == KUC_TYPE_INTERRUPT) {
				InterruptStru* in = (InterruptStru*)(yadmaIntrKuc->data);

                *fn = in->frame;
                *sn = in->slot;
                *bl = in->block;
                ret = in->mask;
            
                sync_status = in->sync_status;
                coars_freq_est = in->coars_freq_est;
                fine_freq_est = in->fine_freq_est;
				timing_est = in->timing_est;
				freq_est = in->freq_est;
			//	printf("coars_freq_est = %d\n",coars_freq_est);
			//	printf("fine_freq_est = %d\n",fine_freq_est);
				tmp1 = (long)coars_freq_est;
				tmp2 = (long)fine_freq_est;
				tmp3 = (long)freq_est;
				freq_est_value = (tmp3*3840000*8)/8388608;
				coars_freq_est_value = (tmp1*3840000)/(32768*128);
				fine_freq_est_value = (tmp2*3840000)/(32768*128);
				add = add + fine_freq_est_value;
				printf("sync_stautus = %d\n",sync_status);
				//printf("add = %d\n",add);
				printf("freq_est_value = %d\n",freq_est_value);			
				printf("coars_freq_est_value = %d\n",coars_freq_est_value);
				printf("fine_freq_est_value = %d\n",fine_freq_est_value);
				printf("timing_est = %d\n",timing_est);
				
                //
                //logMsg("Interrupts %04x received: ch=%d, block=%d \n",\
				//	ret, in->ch, in->block);
					
					
#ifdef DUMP_NETLINK_DATA
				logMsg("--------------Interrupt @time %ld -----------------------\n", in->time.tv_sec *1000000000 + in->time.tv_nsec);
				clock_gettime(CLOCK_REALTIME, &now);
                logMsg("Interrupts %04x received: ch=%d, block=%d,frame=%d, slot=%d.\n",\
					ret, in->ch, in->block, in->frame, in->slot);
                logMsg("Time Delay = %ld nanoseconds.\n", (now.tv_sec - in->time.tv_sec) * 1000000000L + now.tv_nsec - in->time.tv_nsec);
#endif
                /* persistent the kernel timing information */
                SaveKernelStatus(in->ch, in->block, in->frame, in->slot);
                
                // REVISIT @ 2014/4/21 by bangxi
                // add the ret value to judge it is interrupt received 
                ret = 1;
			} else if(yadmaIntrKuc->type == KUC_TYPE_BAR_OP) {
                BarOpStru *bop;
				bop = (BarOpStru*)yadmaIntrKuc->data;
				parse_bar_operation(bop);
			    RegPair* rp = bop->data;
                
                // REVISIT @ 2014/4/21 by bangxi
                // add the ret value to judge it is par command received 
                // 2 : OP read 
                // 3 : OP write 
                if (bop->op == KUC_BAR_OP_READ) {

					printf("bop->value = %x, bop->data = %x , rp = %x", rp->value, rp->reg, yadmaIntrKuc);
				    ret = 2;
				}
				else if (bop->op == KUC_BAR_OP_WRITE) 
				    ret = 3;   
				
            } else {
				/* Not a kuc type can be handled */
                ret = -3;
            }
        }
    } else {
        /* Driver not initilized */
        ret = -2;
    }
#else
    //Triggered every 10 slots
    slot = slot + YADMA_INTERUPT_SLOTS;
    *sn = slot%40;
    *fn = slot/40;

	//copy one slot of sample data to demo buffer, that maybe changed by consummer
    //Rounding the source file 'sample.dat every 10 frames.
	memcpy(demo_buffer + YADMA_SAMPLES_PER_SLOT * (*sn) * 2, \
        sample_data + YADMA_FRAME_SIZE/2 * ((*fn)%(YADMA_SAMPLE_FILE_SIZE/YADMA_FRAME_SIZE))\
         + YADMA_SAMPLES_PER_SLOT * (*sn) * 2, YADMA_SLOT_SIZE*YADMA_INTERUPT_SLOTS);

    usleep(15000);

    /* only support mutiple slot interrtupt when run python demo */
    ret = INT_MULTIPLE_SLOT_END;
#endif
    return ret;
}

int DriverRemove(void)
{
	int i;
	for(i = 0; i < MAX_CHANS; i++) {
		UnmapDmaChannel(i);
	}

    if(yadmaIntrKuc) {
        free(yadmaIntrKuc);
        yadmaIntrKuc = NULL;
	}

#ifdef PYTHON_INTERFACE_DEBUG
	if(demo_buffer)
		free(demo_buffer);

	munmap(sample_data, YADMA_SAMPLE_FILE_SIZE);
	close(sample_fd);
#endif

	/* close the netlink socket */
	close(sock_fd);

	return true;
}

/*-----------------------------------------------------------------------------
 *  mmap the channel's physical continous memory into user space by a Procfs file.
 */

void* MapDmaChannelByProcfs(int ch)
{
	int fd, prot, len;
	char fn[256];
	void * addr = NULL;

	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);

	sprintf(fn, "%s/%s", YADMA_PROC_DIR, yadmaFileNames[ch]);
	prot = PROT_WRITE;

	len = YADMA_BLOCK_COUNT * YADMA_SLOT_COUNT * YADMA_SLOT_SIZE;
	fd = open(fn,O_RDWR);
	addr = mmap(0, len, prot, MAP_SHARED, fd, 0);

	if( !addr ) {
		logMsg("mmap %s failed\n",fn);
		close(fd);
	} else {
		yadmaChans[ch].file_desc = fd;
		yadmaChans[ch].user_space_addr = addr;
		logMsg("Channnel %d is mapped, fd = %d, user space addr = 0x%p.\n", ch, fd, addr);
	}
	return addr;
}

/*-----------------------------------------------------------------------------
 *  mmap the channel's physical continous memory into user space by a Sysfs file.
 */
void* MapDmaChannelBySysfs(int ch)
{
	int fd, prot, len;
	char fn[256];
	void * addr = NULL;

	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);

/*
	memset(&demo_buffer+6, 'a', 1024-6);
	memset(&demo_buffer+1024, 'b', 1024);
	memset(&demo_buffer+2048, 'c', 1024);
	memset(&demo_buffer+3072, 'd', 1024);
*/
#ifdef PYTHON_INTERFACE_DEBUG
	logMsg("Channnel %d is mapped.\n", ch);
	yadmaChans[ch].file_desc = 1001;
	yadmaChans[ch].user_space_addr = demo_buffer;
	return demo_buffer;
#endif
}

short GetDmaBuffer(int ch, int pos)
{
	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);
	DMA_PARAM_CHECK(pos, 0, 4096);
	return demo_buffer[pos];
}

/*-----------------------------------------------------------------------------
 *  mmap the channel's physical continous memory into user space by a Devfs file.
 */

void* MapDmaChannelByDevfs(int ch)
{
	int fd, prot, len;
	char fn[256];
	void * addr = NULL;

	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);

	sprintf(fn, "%s/%s", YADMA_DEVFS_DIR, yadmaFileNames[ch]);
	prot = PROT_WRITE;


	len = YADMA_BLOCK_COUNT * YADMA_SLOT_COUNT * YADMA_SLOT_SIZE;
	fd = open(fn,O_RDWR);
	addr = mmap(0, len, prot, MAP_SHARED, fd, 0);

	if( !addr ) {
		logMsg("mmap %s failed\n",fn);
		close(fd);
	} else {
		yadmaChans[ch].file_desc = fd;
		yadmaChans[ch].user_space_addr = addr;
	}

	logMsg("Channnel %d is mapped.\n", ch);
	return addr;
}

int MapTxRxDmaChannel(int ch)
{
    int bl;
	int fd, prot, len;
	char fn[256];
	void * addr = NULL;
    long int offset;

	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);

	memset(fn, 0, 256);
	sprintf(fn, "%s/%s", YADMA_PROC_DIR, yadmaFileNames[ch]);
	if(ch==TX_CHAN)
		prot = PROT_WRITE;
	else
		prot = PROT_READ;

	len = YADMA_BLOCK_SIZE+YADMA_ADDTION_SIZE;

	fd = open(fn,O_RDWR);
    yadmaChans[ch].file_desc = fd;

    if(yadmaChans[ch].block_count > YADMA_BLOCK_COUNT)
        yadmaChans[ch].block_count = YADMA_BLOCK_COUNT;

    for(bl = 0; bl < yadmaChans[ch].block_count; bl++) {
        offset = bl << PAGE_SHIFT;
        addr = mmap(0, len, prot, MAP_SHARED, fd, offset);
#ifdef DEBUG_MMAP_POINTER
        if( !addr || addr == -1 ) {
            logMsg("mmap %s at offset %#x failed\n",fn, offset);
        } else {
            logMsg("Channnel %d is mapped, fd = %d, user space addr = 0x%p.\n", ch, fd, addr);
            print_hex_dump_bytes("@", DUMP_PREFIX_ADDRESS, addr, 16);
        }
	logMsg("yadmaChans[%d].user_space_addr_array[%d]=%p\n", ch, bl, yadmaChans[ch].user_space_addr_array[bl]);
#endif
        yadmaChans[ch].user_space_addr_array[bl] = addr;
    }

    /* save the first block's address to pass the channel validation check */
    yadmaChans[ch].user_space_addr = yadmaChans[ch].user_space_addr_array[0];

    close(fd);

    return YADMA_SUCCESS;
}

int UnmapTxRxDmaChannel(int ch)
{
    int bl;
	int fd, prot, len;
	char fn[256];
	void * addr = NULL;

	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);

	sprintf(fn, "%s/%s", YADMA_PROC_DIR, yadmaFileNames[ch]);
	prot = PROT_READ;

	len = YADMA_BLOCK_SIZE+YADMA_ADDTION_SIZE;

	fd = open(fn,O_RDWR);

    if(yadmaChans[ch].block_count > YADMA_BLOCK_COUNT)
        yadmaChans[ch].block_count = YADMA_BLOCK_COUNT;
        yadmaChans[ch].block_count = YADMA_BLOCK_COUNT;

    for(bl = 0; bl < yadmaChans[ch].block_count; bl++) {
        addr = yadmaChans[ch].user_space_addr_array[bl];
		if(addr==NULL) {
			logMsg("Channnel %d unmap failed, fd = %d, bl = %d.\n", ch, fd, bl);
		}

        if(addr ) {
            munmap(addr, yadmaChans[ch].block_size);
        }
        yadmaChans[ch].user_space_addr_array[bl] = NULL;
    }

    close(fd);

    yadmaChans[ch].file_desc = -1;
    return YADMA_SUCCESS;
}

int UnmapDmaChannel(int ch)
{
	int ret = false;
	if(yadmaChans[ch].user_space_addr != NULL && yadmaChans[ch].file_desc != -1 && yadmaChans[ch].user_space_addr != 0xFFFFFFFF) {
		munmap(yadmaChans[ch].user_space_addr, yadmaChans[ch].block_count * yadmaChans[ch].block_count);
		close(yadmaChans[ch].file_desc);
		yadmaChans[ch].user_space_addr = NULL;
		yadmaChans[ch].file_desc = -1;
		ret = true;
		logMsg("Channnel %d is unmapped.\n", ch);
	}
	return ret;
}

/*-----------------------------------------------------------------------------
 *  Get the user space address of slot, which belongs to 'block' of channel 'ch';
 */
void* GetSlotPointer(int ch, int block, int slot)
{
	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);
	DMA_PARAM_CHECK(block, 0, YADMA_BLOCK_COUNT);
	DMA_PARAM_CHECK(slot, 0, YADMA_SLOT_COUNT);

	if(yadmaChans[ch].file_desc != -1 && yadmaChans[ch].user_space_addr != 0xFFFFFFFF) {
		return (yadmaChans[ch].user_space_addr + block * yadmaChans[ch].block_size + slot * yadmaChans[ch].slot_size);
	} else {
		printf("file_desc = %d, user space addr = %#x\n", yadmaChans[ch].file_desc, yadmaChans[ch].user_space_addr);
		return NULL;
	}

}


/*-----------------------------------------------------------------------------
 *  Get the user space address of block 'block' of channel 'ch'.
 */

char* GetBlockPointer(int ch, int block)
{
	char *p;
//	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);
//	DMA_PARAM_CHECK(block, 0, YADMA_BLOCK_COUNT);

#if 0 //#if (MAX_CHANS != 1)MapDmaBuffer
	if(block != yadmaChans[ch].cur_block) {
		logMsg("Error: try to get block occupied by driver space!\n");
		return NULL;
	}

	if(is_valid_dma_channel(ch)) {
		return (yadmaChans[ch].user_space_addr + block * yadmaChans[ch].block_size);
	} else {
		return NULL;
	}
#else
    //logMsg("yadmaChans[%d].user_space_addr_array[%d]=%p\n", ch, block, yadmaChans[ch].user_space_addr_array[block]);
    p = (yadmaChans[ch].user_space_addr_array[block]);
    return p;
#endif
}

/*-----------------------------------------------------------------------------
 *  Get the user space address of channel 'ch'.
 */

void* GetChannelPointer(int ch)
{
	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);
	return yadmaChans[ch].user_space_addr;
}

#ifdef RING_BUFFER_MANAGEMENT
int GetNextNSlot(int ch, int cur_block, int cur_slot, int nextn, int *pblock, int* pslot)
{
    if(is_valid_dma_channel(ch)) {
        int block, slot;
        block = cur_block;
        slot = cur_slot;
        while(nextn-- > 0) {
            slot = slot + 1;
            if(slot >= yadmaChans[ch].slot_count) {
                slot = 0;
                block = block + 1;
                if(block >= yadmaChans[ch].block_count)
                    block = 0;
            }
        }
        *pblock = block;
        *pslot = slot;
        //printf("NextNSlot block = %d, slot = %d\n", *pblock, *pslot);
        *pblock = 0;
        return YADMA_SUCCESS;
    } else {
        return YADMA_FAILURE;
    }
}

int GetPrevNSlot(int ch, int cur_block, int cur_slot, int prevn, int *pblock, int* pslot)
{
    if(is_valid_dma_channel(ch)) {
        int block, slot;
        block = cur_block;
        slot = cur_slot;
        while(prevn-- > 0) {
            slot = slot - 1;
            if(slot < 0) {
                slot =  yadmaChans[ch].slot_count - 1;
                block = block - 1;
                if(block < 0)
                    block = yadmaChans[ch].block_count - 1;
            }
        }
        *pblock = block;
        *pslot = slot;
        return YADMA_SUCCESS;
    } else {
        return YADMA_FAILURE;
    }
}

/*-----------------------------------------------------------------------------
 *  Get the user space address of current block of channel 'ch'.
 */

void* GetCurrentBlockPointer(int ch)
{
	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);
	if(is_valid_dma_channel(ch))
		return GetBlockPointer(ch, yadmaChans[ch].cur_block);
	else
		return NULL;
}

void* GetNextNBlockPointer(int ch, int nblock)
{
	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);
	int next;

    if(is_valid_dma_channel(ch)){
        while(nblock-- > 0) {
            next = yadmaChans[ch].cur_block + 1;
            if(next >= yadmaChans[ch].block_count)
                next = 0;
        }

		return GetBlockPointer(ch, next);
	}
	return NULL;
}

/*-----------------------------------------------------------------------------
 *  Get the user space address of next block of channel 'ch'.
 */

void* GetNextBlockPointer(int ch)
{
	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);
	int next;

    if(is_valid_dma_channel(ch)){
		next = yadmaChans[ch].cur_block + 1;
		if(next >= yadmaChans[ch].block_count)
			next = 0;

		return GetBlockPointer(ch, next);
	}
	return NULL;
}

/*-----------------------------------------------------------------------------
 *  Switch to next block for channel 'ch'.
 */

void SwitchToNextBlock(int ch)
{
	DMA_PARAM_CHECK_VOID(ch, 0, MAX_CHANS);

	//TODO: Lock
	yadmaChans[ch].cur_block ++;
	if(yadmaChans[ch].cur_block >= yadmaChans[ch].block_count)
		yadmaChans[ch].cur_block = 0;
}

/*-----------------------------------------------------------------------------
 *  Switch to next slot for channel 'ch'.
 */

void SwitchToNextSlot(int ch)
{
	DMA_PARAM_CHECK_VOID(ch, 0, MAX_CHANS);

	//TODO: Lock
	yadmaChans[ch].cur_slot ++;
	if(yadmaChans[ch].cur_slot >= yadmaChans[ch].slot_count) {
		SwitchToNextBlock(ch);
		yadmaChans[ch].cur_slot = 0;
	}
}

/*-----------------------------------------------------------------------------
 *  Switch to previous block for channel 'ch'.
 */

void SwitchToPrevBlock(int ch)
{
	DMA_PARAM_CHECK_VOID(ch, 0, MAX_CHANS);

	//TODO: Lock
	yadmaChans[ch].cur_block --;
	if(yadmaChans[ch].cur_block < 0)
		yadmaChans[ch].cur_block = yadmaChans[ch].block_count-1;
}

/*-----------------------------------------------------------------------------
 *  Switch to previous slot for channel 'ch'.
 */

void SwitchToPrevSlot(int ch)
{
	DMA_PARAM_CHECK_VOID(ch, 0, MAX_CHANS);

	//TODO: Lock
	yadmaChans[ch].cur_slot --;
	if(yadmaChans[ch].cur_slot < 0) {
		SwitchToPrevBlock(ch);
		yadmaChans[ch].cur_slot =  yadmaChans[ch].slot_count-1;
	}
}

/*-----------------------------------------------------------------------------
 *  Get the user space address of next slot of channel 'ch';
 */
void* GetNextSlotPointer(int ch)
{
	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);

    if(is_valid_dma_channel(ch)) {
		int block, slot;
		block = yadmaChans[ch].cur_block;
		slot = yadmaChans[ch].cur_slot + 1;
		if(slot >= yadmaChans[ch].slot_count) {
			slot = 0;
			block = yadmaChans[ch].cur_block + 1;
			if(block >= yadmaChans[ch].block_count)
				block = 0;
		}
		return (GetSlotPointer(ch, block, slot));
	} else {
		return NULL;
	}
}

/*-----------------------------------------------------------------------------
 *  Get the user space address of nslot, which belongs to 'block' of channel 'ch';
 */
void* GetNextNSlotPointer(int ch, int nextn)
{
    int slot, block;
	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);
	DMA_PARAM_CHECK(block, 0, YADMA_BLOCK_COUNT);
	DMA_PARAM_CHECK(nextn, 0, YADMA_SLOT_COUNT);

    if(GetNextNSlot(ch, yadmaChans[ch].cur_block, yadmaChans[ch].cur_slot, nextn, &block, &slot) == YADMA_SUCCESS) {
        if(yadmaChans[ch].file_desc != -1 && yadmaChans[ch].user_space_addr != 0xFFFFFFFF) {
            return (yadmaChans[ch].user_space_addr + block * yadmaChans[ch].block_size + slot * yadmaChans[ch].slot_size);
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}
/*-----------------------------------------------------------------------------
 *  Get the user space address of current slot of channel 'ch';
 */
void* GetCurrentSlotPointer(int ch)
{
	DMA_PARAM_CHECK(ch, 0, MAX_CHANS);

    if(is_valid_dma_channel(ch)) {
		return (GetSlotPointer(ch, yadmaChans[ch].cur_block, yadmaChans[ch].cur_slot));
	} else {
		return NULL;
	}
}
#endif

/*-----------------------------------------------------------------------------
 *  Tell kernel the 'ch -- block --  before 'slot' is not occupied by user space.
 */

void ReleaseSlots(int ch, int block, int slot)
{
	int send_len;
	DMA_PARAM_CHECK_VOID(ch, 0, MAX_CHANS);
	DMA_PARAM_CHECK_VOID(block, 0, YADMA_BLOCK_COUNT);
	DMA_PARAM_CHECK_VOID(slot, 0, YADMA_SLOT_COUNT);

    /* The slot has been processed by user space program.
     * Then set next slot as current slot.
     */
    if(is_valid_dma_channel(ch)) {
        yadmaChans[ch].cur_block = block;
		yadmaChans[ch].cur_slot = slot;
    }

	send_len = NLMSG_SPACE(sizeof(KucMessage)) + sizeof(FinishStru);
	/* Using netlink socket to tell driver user space
	   has finished processing for slot 'nslot' */
	KucMessage*kuc = (KucMessage*)malloc(send_len);
	if(kuc) {
		kuc->len = send_len;
		FinishStru *fi = (FinishStru*)kuc->data;
		fi->block = block;
		fi->slot = slot;
		fi->ch = ch;
		Send2KernelByNetLink(kuc);
		free(kuc);
	} else {
		logMsg("Error: Out of memory!\n");
	}
}


/*-----------------------------------------------------------------------------
 *  Save the block and slot number just processed by kernel space.
 */

void SaveKernelStatus(int ch, int block, int frame, int slot)
{
	DMA_PARAM_CHECK_VOID(block, 0, YADMA_BLOCK_COUNT);
	DMA_PARAM_CHECK_VOID(slot, 0, YADMA_SLOT_COUNT);

    if(is_valid_dma_channel(ch)) {
		yadmaChans[ch].k_block = block;
		yadmaChans[ch].k_slot = slot;
        yadmaChans[ch].k_frame = frame;
	}
}

