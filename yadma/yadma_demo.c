/*****************************************************************************/
/**
*
* @file yadma_user.c
*
* This use space program for demo how to use yadma.
* MODIFICATION HISTORY:
*
* Ver   Date     Changes
* ----- -------- -------------------------------------------------------
* 1.0   5/15/12  First version
*
******************************************************************************/

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
#include <signal.h>

#include <linux/genetlink.h>
#include <sys/mman.h>

#include "yadma.h"
#include "yadma_user.h"
#include "yadma_proc.h"
#include "hexdump_user.h"
#include "yadma_api.h"
#include "yadma_reg.h"



/* Command command output buffer */
static char cmd_out_buffer[4096];

static int is_dma_mmapped = 0;
static int is_ko_inserted = 0;
static int is_driver_initialized = 0;

#define COMMAND_NOT_AVAILABLE "N/A"
/**
 * This function executes a shell command, and output its result.
 * @param cmd, the command to be excuted.
 * @param result, a buffer, at least 256bytes, to save the shell outputs.
 */
static int exec_shell_cmd(const char * cmd, char* result)
{
    int ret = -1;
    FILE *fp = NULL;
    char line[256];

    memset (result, 0, 256);

    /* set the defalut value */
    strncpy (result, COMMAND_NOT_AVAILABLE, 4);

    /* Open the command for reading. */
    fp = popen(cmd, "r");
    if (fp != NULL)
    {
        /* read the line from file */
        while(!feof(fp))
        {
            if(fgets (line, 256, fp) != NULL){
                /* copy the data */
                strncpy(result+strlen(result), line, strnlen (line, 256));
            }
        }

        ret = 0;
        /* close the file */
        pclose (fp);
    }

    logMsg("Executes: %s, outputs: \n%s\n", cmd, result);
    return ret;
}

/*-----------------------------------------------------------------------------
 *
 */
static char show_main_menu(void)
{
    printf("Run this commands in order please!\n");

    printf("0. Insmod yadma.ko;\n");

    printf("1. Netlink Receive;\n");
    printf("2. Netlink Send (Register);\n");

    printf("3. Sysfs DMA Read\n");
    printf("4. Sysfs DMA Write;\n");

    printf("5. Procfs DMA Read;\n");
    printf("6. Procfs DMA Write;\n");

    printf("7. Char Dev DMA Read;\n");
    printf("8. Char Dev DMA Write;\n");

    printf("9. Remove yadma.ko;\n");
    printf("a. Python Fake Intr Demo;\n");
    printf("b. PCIE loopback Demo;\n");
    printf("c. RF Slope test;\n");
    printf("d. Frequency offset test with param\n");
    printf("e. Frequency offset adjust\n");
    printf("q. Quit.\n");

    printf("Select which to run:\n");

    char in;
    do {
        in = getchar();
    } while (isspace(in));
    while (getchar() != '\n');
    return in;
}

/*-----------------------------------------------------------------------------
 *
 */

static char show_continue_or_break_submenu(void)
{
    char in;
    printf("Continue or Break?\n");
    printf("Input 'c' for continue.\n");
    printf("Input 'b' for break.\n");
    do {
        do {
            in = getchar();
        } while (isspace(in));
        while (getchar() != '\n');
        printf("input = %c\n", in);
        if(in == 'c' || in == 'b')
            break;
    } while(1);

    return in;
}

/*-----------------------------------------------------------------------------
 *  0.
 */

static void test_insmod(void)
{
    char c;

    do {
        printf("test_insmod...\n");
        if(!is_ko_inserted && (exec_shell_cmd("insmod yadma.ko", cmd_out_buffer) == 0)) {
            is_ko_inserted = 1;
        }
    } while (0); /* Run only one time */

    if(is_ko_inserted) {
        if(!is_driver_initialized && (DriverInit() == true)) {
            is_driver_initialized = 1;
        }
    }

    StartBoard();

    AdjustFrequencyOffset(0);
}

/*-----------------------------------------------------------------------------
 *  1.
 */

static void test_netlink_receive(void)
{
    char c;

    /* should not receive a message exceed the max payload limit */
    KucMessage* recvMsg = (KucMessage*)malloc(MAX_PAYLOAD);
    if(recvMsg) {
        recvMsg->len = MAX_PAYLOAD;
        do {
            /* Read message from kernel */
            RecvFromKernelFromNetLink(recvMsg);
            printf("Received message: type = %d; length = %d\n", recvMsg->type, recvMsg->len);
            if(recvMsg->type == KUC_TYPE_INTERRUPT) {

            }
        } while ((c = show_continue_or_break_submenu())!= 'b');
        free(recvMsg);
    }
}




/*-----------------------------------------------------------------------------
 *  2.
 */
/* 80 digits */
static const char* test_pattern_1 = "01234567890123456789012345678901234567890123456789012345678901234567890123456789";

static void test_netlink_send(void)
{
    char c;
    KucMessage* sndMsg = (KucMessage*)malloc(MAX_PAYLOAD);
    if(sndMsg) {
        do {
            memset(sndMsg, 0, MAX_PAYLOAD);
            sndMsg->len = NLMSG_SPACE(sizeof(KucMessage) + sizeof(DemoStruct));
            sndMsg->type = KUC_TYPE_REGISTER;
            DemoStruct *ds = (DemoStruct*)sndMsg->data;
            ds->channel = TX_CHAN_1;
            ds->fs = 1; /* proc fs */
            ds->times = 100; /* 100 times */
            ds->interval = 5; /* interrupt per 5 slots */
            strncpy(ds->pattern, test_pattern_1, strlen(test_pattern_1));

            printf("Sending message to kernel, len = %d\n", sndMsg->len);

            /* Send message to kernel */
            Send2KernelByNetLink(sndMsg);

        } while ((c = show_continue_or_break_submenu())!= 'b');
        free(sndMsg);
    }
}


/*-----------------------------------------------------------------------------
 *  3.
 */

static void test_sysfs_read(void)
{
    char c;
    do {
        printf("test_sysfs_read...on RX_CHAN_1 \n");
        void* rx_chan_1 = MapDmaChannelBySysfs(RX_CHAN_1);
        printf("Read Message:\n%s", (char*)rx_chan_1);
        UnmapDmaChannel(RX_CHAN_1);
    } while ((c = show_continue_or_break_submenu())!= 'b');
}

/*-----------------------------------------------------------------------------
 *  4.
 */

static void test_sysfs_write(void)
{
    char c;
    do {
        printf("test_sysfs_write...on TX_CHAN_1 \n");
        void* tx_chan_1 = MapDmaChannelBySysfs(TX_CHAN_1);

        UnmapDmaChannel(TX_CHAN_1);
    } while ((c = show_continue_or_break_submenu())!= 'b');
}
/*-----------------------------------------------------------------------------
 *  5.
 */

static void test_procfs_read(void)
{
    char c;
    do {
        printf("test_procfs_read...on RX_CHAN_2 \n");
        void* rx_chan_2 = MapDmaChannelByProcfs(RX_CHAN_2);

        UnmapDmaChannel(RX_CHAN_2);
    } while ((c = show_continue_or_break_submenu())!= 'b');
}

/*-----------------------------------------------------------------------------
 *  6.
 */

static void test_procfs_write(void)
{
    char c;
    do {
        printf("test_procfs_write...on TX_CHAN_2 \n");
        void* tx_chan_2 = MapDmaChannelByProcfs(TX_CHAN_2);

        UnmapDmaChannel(TX_CHAN_2);
    } while ((c = show_continue_or_break_submenu())!= 'b');
}
/*-----------------------------------------------------------------------------
 *  7.
 */

static void test_char_device_read(void)
{
    char c;
    do {
        printf("test_char_device_read...\n");
    } while ((c = show_continue_or_break_submenu())!= 'b');
}


/*-----------------------------------------------------------------------------
 *  8.
 */

static void test_char_device_write(void)
{
    char c;
    do {
        printf("test_char_device_write...\n");
    } while ((c = show_continue_or_break_submenu())!= 'b');
}

/*-----------------------------------------------------------------------------
 *  9.
 */

static void test_rmmod(void)
{
    char c;
    do {
        printf("test_rmmod...\n");
        if((exec_shell_cmd("rmmod yadma", cmd_out_buffer) == 0)) {
            is_ko_inserted = 0;
            printf("%s\n",cmd_out_buffer);
        }
    } while (0);
}


static void test_python_demo(void)
{
    char c;
    int s = 0;
    printf("test_python_demo...\n");

    /* mmap it before using the channel 0 */
    MapDmaChannelBySysfs(0);
    do {
        int fn, sn, bl;
        char *pslot;
        WaitForInterrupt(&fn, &sn, &bl);
        printf("frame = %d, slot =%d\n", fn, sn);
        pslot = GetSlotPointer(0, 0, sn);

        printf("offset = %X\n", ((void*)pslot - GetSlotPointer(0, 0, 0)));
        print_hex_dump_bytes("@", DUMP_PREFIX_ADDRESS, pslot, 32);
    } while (s++ < 80);
}
static unsigned short slot_pattern[YADMA_SLOT_COUNT] = {0};
static void FillSlotWithPattern(int ch, int block, int slot)
{
	int i;
	unsigned short *ps;
	ps = (unsigned short*) GetSlotPointer(ch, block, slot);
	for(i = 0; i < YADMA_SAMPLES_PER_SLOT * 2; i++) {
		ps[i] = (slot_pattern[slot]+i) & 0x7FF;
	}
}

static int CompareSlotWithPattern(int ch, int block, int slot)
{
	int i, ret = 0;
	unsigned short *ps;
	ps = (unsigned short*) GetSlotPointer(ch, block, slot);
	for(i = 0; i < YADMA_SAMPLES_PER_SLOT * 2; i++) {
		if(ps[i] != ((slot_pattern[slot]+i) & 0x7FF)) {
			printf("Bad data @ block = %d, slot = %d, %dth sample:\n", block, slot, i/2);
			printf("Value = %ud, Pattern = %ud\n", ps[i], slot_pattern[slot]);
			ret = -1;
			break;
		}
	}
	if(ret == 0) {
			//printf("Match data @ block = %d, slot = %d, %dth sample:\n", block, slot, i/2);
			//printf("Value = %ud, Pattern = %ud\n", ps[i-1], slot_pattern[slot]);
	}
	return ret;
}
static void test_block_base_dma(void)
{
    char c;
    int i = 0;

    printf("test_block_base_dma...\n");

    /* mmap it before using the channel 1 */
    MapDmaChannelByProcfs(TX_CHAN_1);
    MapDmaChannelByProcfs(RX_CHAN_1);

    do {
        int block, slot, count;
        char *  prx, *ptx;
        int int_fn, int_sn, int_bl; /* frame and slot number reported by interrupt */
        int fn, sn, bl; /* temporary variables */

        count = YADMA_INTERUPT_SLOTS;
        WaitForInterrupt(&int_fn, &int_sn, &int_bl);

        /* Write Tx Buffer */

		if(YADMA_SUCCESS == GetNextNSlot(TX_CHAN_1, int_bl, int_sn, YADMA_INTERUPT_SLOTS/2, &block, &slot))
		{
			//printf("Nblock = %d, NSlot = %d\n",block, slot);
			while(count-- > 0) {

				static unsigned long idx = 0;

#ifdef INCREMENTAL_NUMBER
                ptx = GetSlotPointer(TX_CHAN_1, block, slot);
                if(ptx) {
					*(unsigned long*) ptx = idx;
					logMsg("%x ", idx);
					idx++;
				}
#endif
				slot_pattern[slot] = idx & 0x7FF;
				idx++;

				FillSlotWithPattern(TX_CHAN_1, block, slot);

				/* user has write data to this slot, then release it */
                ReleaseSlots(TX_CHAN_1, block, slot);
                bl = block;
				sn = slot;
                GetNextNSlot(TX_CHAN_1, bl, sn, 1, &block, &slot);
            }
        }

        /* Read Rx Buffer */
        count = YADMA_INTERUPT_SLOTS;

		if(YADMA_SUCCESS == GetPrevNSlot(RX_CHAN_1, int_bl, int_sn, YADMA_INTERUPT_SLOTS+2, &block, &slot))
		{
			//printf("\nPBlock = %d, PSlot = %d\n", block, slot);
			if(slot < 0 || slot >= YADMA_SLOT_COUNT)
				return;

			while(count-- > 0) {
#ifdef INCREMENTAL_NUMBER
                prx = GetSlotPointer(RX_CHAN_1, block, slot);
                if(prx) {
					logMsg("%x ", *(unsigned long*) prx);
				}
#endif
				CompareSlotWithPattern(RX_CHAN_1, block, slot);

                /* user has read data from this slot, then release it */
                ReleaseSlots(RX_CHAN_1, block, slot);
				bl = block;
				sn = slot;
                GetNextNSlot(RX_CHAN_1, bl, sn, 1, &block, &slot);
            }
        }
        //printf("\n");
    } while (i++ < 100000);
}


static void test_pcie_loopback(void)
{
    char c;
    int i = 0;

    printf("test_pcie_loopback...\n");

    /* mmap it before using the channel 1 */
    MapDmaChannelByProcfs(TX_CHAN_1);
    MapDmaChannelByProcfs(RX_CHAN_1);

    do {
        int block, slot, count;
        char *  prx, *ptx;
        int int_fn, int_sn, int_bl; /* frame and slot number reported by interrupt */
        int fn, sn, bl; /* temporary variables */

        count = YADMA_INTERUPT_SLOTS;
        WaitForInterrupt(&int_fn, &int_sn, &int_bl);

        /* Write Tx Buffer */

		if(YADMA_SUCCESS == GetNextNSlot(TX_CHAN_1, int_bl, int_sn, YADMA_INTERUPT_SLOTS/2, &block, &slot))
		{
			//printf("Nblock = %d, NSlot = %d\n",block, slot);
			while(count-- > 0) {

				static unsigned long idx = 0;

#ifdef INCREMENTAL_NUMBER
                ptx = GetSlotPointer(TX_CHAN_1, block, slot);
                if(ptx) {
					*(unsigned long*) ptx = idx;
					logMsg("%x ", idx);
					idx++;
				}
#endif
				slot_pattern[slot] = idx & 0x7FF;
				idx++;

				FillSlotWithPattern(TX_CHAN_1, block, slot);

				/* user has write data to this slot, then release it */
                ReleaseSlots(TX_CHAN_1, block, slot);
                bl = block;
				sn = slot;
                GetNextNSlot(TX_CHAN_1, bl, sn, 1, &block, &slot);
            }
        }

        /* Read Rx Buffer */
        count = YADMA_INTERUPT_SLOTS;

		if(YADMA_SUCCESS == GetPrevNSlot(RX_CHAN_1, int_bl, int_sn, YADMA_INTERUPT_SLOTS+2, &block, &slot))
		{
			//printf("\nPBlock = %d, PSlot = %d\n", block, slot);
			if(slot < 0 || slot >= YADMA_SLOT_COUNT)
				return;

			while(count-- > 0) {
#ifdef INCREMENTAL_NUMBER
                prx = GetSlotPointer(RX_CHAN_1, block, slot);
                if(prx) {
					logMsg("%x ", *(unsigned long*) prx);
				}
#endif
				CompareSlotWithPattern(RX_CHAN_1, block, slot);

                /* user has read data from this slot, then release it */
                ReleaseSlots(RX_CHAN_1, block, slot);
				bl = block;
				sn = slot;
                GetNextNSlot(RX_CHAN_1, bl, sn, 1, &block, &slot);
            }
        }
        //printf("\n");
    } while (i++ < 100000);
}

static void test_rf_slope()
{
    char c;
    int dac;

    do {
        printf("Input 10Mhz DAC value (HEX):");
        int n = scanf("%x", &dac);
        if(n > 0) {
			printf("DAC = 0x%x\n", dac);
		} else if (errno != 0) {
            printf("scanf %d\n", errno);
        } else {
            printf("No matching characters\n");
        }

		KucMessage *kuc = malloc(MAX_PAYLOAD);
		if(kuc) {

			kuc->len = NLMSG_SPACE(sizeof(KucMessage) + sizeof(BarOpStru) + sizeof(RegPair));
			kuc->type = KUC_TYPE_BAR_OP;

			BarOpStru *bop = (BarOpStru *)kuc->data;
			bop->count = 1;
			bop->op = KUC_BAR_OP_WRITE;
			bop->bar = BAR_FPGA_CTRL;

			RegPair *rp = (RegPair*)bop->data;
			rp->reg = REG_AFC_DAC_VALUE;
			rp->value = dac;

			printf("Send DAC to driver.\n");
			Send2KernelByNetLink(kuc);
			free(kuc);
		}

    } while ((c = show_continue_or_break_submenu())!= 'b');
}

static void test_freq_offset_adjust()
{
    char c;
    int offset;
    double a, b;

    do {

        printf("Input frequeny offset (DEC):");
        int n = scanf("%d", &offset);
        if(n > 0) {
			printf("offset = %d\n", offset);
		} else if (errno != 0) {
            printf("scanf %d\n", errno);
        } else {
            printf("No matching characters\n");
        }


		AdjustFrequencyOffset(offset);

    } while ((c = show_continue_or_break_submenu())!= 'b');
}

static void test_freq_offset_adjust_with_param_input()
{
    char c;
    int offset;
    double a, b;

    do {
        printf("Input value y (float):");
        int n = scanf("%lf", &a);
        if(n > 0) {
			printf("a = %lf\n", a);
		} else if (errno != 0) {
            printf("scanf %d\n", errno);
        } else {
            printf("No matching characters\n");
        }

        printf("Input value fRF (float):");
        n = scanf("%lf", &b);
        if(n > 0) {
			printf("b = %f\n", b);
		} else if (errno != 0) {
            printf("scanf %d\n", errno);
        } else {
            printf("No matching characters\n");
        }

        printf("Input frequeny offset (DEC):");
        n = scanf("%d", &offset);
        if(n > 0) {
			printf("offset = %d\n", offset);
		} else if (errno != 0) {
            printf("scanf %d\n", errno);
        } else {
            printf("No matching characters\n");
        }

		SetAFCParam(a, b);

		AdjustFrequencyOffset(offset);

    } while ((c = show_continue_or_break_submenu())!= 'b');
}
/*-----------------------------------------------------------------------------
 *
 */

int main(int argc, char **argv)
{
    char key;

    do {
        key = show_main_menu();
        printf("key = %c\n", key);
        switch(key) {
        case '0':
            test_insmod();
            break;
        case '1':
            test_netlink_receive();
            break;
        case '2':
            test_netlink_send();
            break;
        case '3':
            test_sysfs_read();
            break;
        case '4':
            test_sysfs_write();
            break;
        case '5':
            test_procfs_read();
            break;
        case '6':
            test_procfs_write();
            break;
        case '7':
            test_char_device_read();
            break;
        case '8':
            test_char_device_write();
            break;
        case '9':
            test_rmmod();
            break;
        case 'a':
            test_python_demo();
            break;
        case 'b':
            test_pcie_loopback();
            break;
        case 'c':
			test_rf_slope();
			break;
		case 'd':
			test_freq_offset_adjust_with_param_input();
			break;
		case 'e':
			test_freq_offset_adjust();
			break;
        default:
            break;
        }
    } while(key != 'q');

    // Show Quit.
    printf("The test is finised. Quit now.\n");
}

