/*****************************************************************************/
/**
 *
 * @file yadma.c
 *
 * This is the Linux base PC side driver for high volume data transfering
 * with FPGA, which Implements DMA logic.
 *
 * Author: Xilinx, Inc.
 *
 * 2007-2010 (c) GNU
 *
 * MODIFICATION HISTORY:
 *
 * Ver   Date     Changes
 * ----- -------- -------------------------------------------------------
 * 1.0  10/15/13  First release
 *
 *****************************************************************************/

/***************************** Include Files *********************************/
#include <linux/pci.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/version.h>
#include <linux/ethtool.h>
#include <linux/netlink.h>
#include <net/sock.h>

#include <linux/mm.h>
#include <linux/spinlock.h>
#include <linux/semaphore.h>
#include <linux/pagemap.h>
#include <asm/scatterlist.h>
#include <linux/time.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/list.h>
#include "yadma.h"
#include "yadma_reg.h"


#include "yadma_knl.h"
#include "yadma_proc.h"
#include "yadma_sysfs.h"
#include "adi_common.h"


/************************** Constant Definitions *****************************/

/** @name Macros for PCI probing
 * @{
 */
#define PCI_VENDOR_ID_DMA   0x10EE      /**< Vendor ID - Xilinx */

#define PCI_DEVICE_ID_DMA   0x7014      /**< Xilinx's Device ID */

/** Driver information */
#define DRIVER_NAME         "yadma"
#define DRIVER_DESCRIPTION  "Yet Another DMA Linux driver"
#define DRIVER_VERSION      "1.0"

/** Driver Module information */
MODULE_AUTHOR("Yadma, Inc.");
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL");

PrivateDataStru* yadmaPrivData = NULL;;

/** PCI device structure which probes for targeted design */
static struct pci_device_id ids[] = {
        { PCI_VENDOR_ID_DMA,    PCI_DEVICE_ID_DMA,
          PCI_ANY_ID,               PCI_ANY_ID,
          0,            0,          0UL },
          { }     /* terminate list with empty entry */
};

/**
 * Macro to export pci_device_id to user space to allow hot plug and
 * module loading system to know what module works with which hardware device
 */
MODULE_DEVICE_TABLE(pci, ids);


/************************** Function Prototypes ******************************/
static int __devinit yadma_pcie_probe(struct pci_dev *pdev, const struct pci_device_id *ent);
static void __devexit  yadma_remove(struct pci_dev *pdev);
static int yadma_dev_open(struct inode * in, struct file * filp);
static int yadma_dev_release(struct inode * in, struct file * filp);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int yadma_dev_ioctl(struct inode * in, struct file * filp,
                          unsigned int cmd, unsigned long arg);
#else
static long yadma_dev_ioctl(struct file * filp,
                          unsigned int cmd, unsigned long arg);
#endif

static void yadma_stats(unsigned long __opaque);
static void yadma_demo(unsigned long __opaque);

static void  frame_report(unsigned long data);
char the_tasklet_data[]="my_tasklet_function was called";
DECLARE_TASKLET( the_tasklet, frame_report, (unsigned long) &the_tasklet_data );
DEFINE_MUTEX(privDataLock);
static struct workqueue_struct *yadmaWorkQue;
static struct work_struct *yadmaWork;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,19)
static irqreturn_t yadma_interrupt_handler(int irq, void *dev_id, struct pt_regs *regs);
#else
static irqreturn_t yadma_interrupt_handler(int irq, void *dev_id);
#endif

static DmaChannel* yadma_create_slot_based_channel(struct device *dev, int bd_count, int slot_count, ssize_t slot_size);
static void yadma_destroy_channel(struct device *dev, DmaChannel* chan);
static void* yadma_next_block(DmaChannel *chan);

static void netlink_send_to_userspace(KucMessage*kuc, bool multicast);

#if 1
void yadma_write_ctrl_bar(int offset, u32 value)
{
    if(yadmaPrivData && offset < yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_len &&
        yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_virt_addr != NULL) {
        yadmaWriteReg(yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_virt_addr, offset, value);
        printk("Write REG %x = %x\n", offset, value);
    }
}

static u32 yadma_read_ctrl_bar(int offset)
{
    u32 value = 0;
    if(yadmaPrivData && offset < yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_len &&
        yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_virt_addr != NULL) {
        value = yadmaReadReg(yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_virt_addr, offset);
    }
    return value;
}

static void yadma_channel_write_addtion(DmaChannel* ch, u32 off, u32 value)
{
	void *p;

    if(ch) {
		*(u32*)(ch->virt_addr_array[ch->cur_block] + YADMA_BLOCK_SIZE + off) = value;
    	//log_verbose(KERN_INFO "%s: %p, block_size=%d, block=%d, off=%d\n", __FUNCTION__, ch->virt_addr_array[ch->cur_block], ch->block_size, ch->cur_block, off);
	}
}

static u32 yadma_channel_read_addtion(DmaChannel* ch, u32 off)
{
    u32 value;
    value = *(u32*)(ch->virt_addr + ch->block_size * ch->cur_block + YADMA_BLOCK_SIZE + off);
    return value;
}

#endif

/** Description:
 *  Allocate a DMA channel which has 'bd_count'  buffer descriptors; Each buffer desc
 *  has 'slot_count' slots; Each slot has 'slot_size' bytes of memory. The whole block
 *  of physical memory for each buffer descriptor should be physical contionous.
 *
 *  @bd_count       The number of the buffer descriptors associated with this channel
 *  @slot_count     The slot count for each buffer.
 *  @slot_size      The slot size for each slot.
 */
static DmaChannel* yadma_create_slot_based_channel(struct device *dev, int bd_count, int slot_count, ssize_t slot_size)
{
	dma_addr_t phys_addr;
	void* virt_addr;
	size_t length;


	DmaChannel *pch = kmalloc(sizeof(DmaChannel), GFP_KERNEL);
	if(pch){
		spin_lock_init(&(pch->chnl_lock));
		memset(pch, 0, sizeof(DmaChannel));

		pch->chnl_state = 0;
		pch->cur_block = 0;
		pch->cur_slot = 0;

		/* allocate the physical continous memory for the buffer */
		length = bd_count * slot_count * slot_size;
		virt_addr = dma_alloc_coherent(dev, length, &phys_addr, GFP_ATOMIC);
        log_verbose(KERN_INFO "Allocated a DMA Buffer size: %d, virt %p, phys %p.\n", length, virt_addr, phys_addr);

        if(virt_addr) {
			pch->phys_addr = phys_addr;
			pch->virt_addr = virt_addr;
			pch->total_length = length;
			pch->slot_size = slot_size;
			pch->block_count = bd_count;
			pch->block_size = slot_size * slot_count;
			pch->slot_count = slot_count;
		} else {
			kfree(pch);
			pch = NULL;
		}
	}

	return pch;
}

static unsigned int first_block_pointer[MAX_CHANS] =
{
	REG_TX_BD0_POINTER,
	REG_RX_BD0_POINTER,
};

static unsigned int block_count[MAX_CHANS] =
{
	CUR_TX_BD_COUNT,
	CUR_RX_BD_COUNT,
};

static void yadma_init_block_based_descriptors(int channel, int bd_count)
{
    int i;
    DmaChannel *ch;
    for(i = 0; i < bd_count; i++) {
		ch = yadmaPrivData->dma_chans[channel];
		if(ch->phys_addr_array[i] != NULL)
			yadma_write_ctrl_bar(first_block_pointer[channel] + i, ch->phys_addr_array[i]);
    }
}

static void fill_incremental_number(char * buffer, int size)
{
	int i;
	for(i = 0; i < size/2/2; i ++) {
		*((unsigned short*)buffer+2*i) = i & 0xFFFF;
		*((unsigned short*)buffer+2*i+1) = 65535-(i & 0xFFFF);
	}
}

/** Description:
 *  Allocate a DMA channel which has 'bd_count'  buffer descriptors; Each block
 *  has 'block_size' bytes of memory. The all blocks
 *  of physical memory for each buffer descriptor should be physical contionous.
 *
 *  @bd_count       The number of the buffer descriptors associated with this channel
 *  @block_size      The slot size for each slot.
 */
static DmaChannel* yadma_create_block_based_channel(struct device *dev, int channel, ssize_t block_size)
{
	dma_addr_t phys_addr;
	void* virt_addr;
	size_t length;
	int i;


	DmaChannel *pch = kmalloc(sizeof(DmaChannel), GFP_KERNEL);
	if(pch){
		spin_lock_init(&(pch->chnl_lock));
		memset(pch, 0, sizeof(DmaChannel));

		pch->chnl_state = 0;
		pch->cur_block = 0;
		pch->cur_slot = 0;

		/* allocate the physical continous memory for the buffer */
		length =  block_size;
		for(i = 0; i < block_count[channel]; i++) {
			virt_addr = dma_alloc_coherent(dev, length, &phys_addr, GFP_ATOMIC);
			log_verbose(KERN_INFO "Allocated a DMA Buffer size: %d, virt %p, phys %p.\n", length, virt_addr, phys_addr);

			if(virt_addr) {
				pch->phys_addr_array[i] = phys_addr;
				pch->virt_addr_array[i] = virt_addr;
				pch->total_length = length;
				pch->slot_size = block_size;
				pch->block_count = block_count[channel];
				pch->block_size = block_size;
				pch->slot_count = 1;
#ifdef INCLUDE_TEST_CODE
				fill_incremental_number(virt_addr, block_size-YADMA_ADDTION_SIZE);
#endif
			} else {
				kfree(pch);
				pch = NULL;
			}
		}
	}

	return pch;
}

/** Description:
 *  Destroy a DMA channel: free its DMA buffer and descriptors.
 *  Caller should warrant no DMA hardware still use the buffers.
 *
 *  @chan The DMA channel to be free.
 */

static void yadma_destroy_channel(struct device *dev, DmaChannel* chan)
{
	int i;

	if(chan) {
		if(chan->virt_addr && chan->phys_addr) {
			log_verbose(KERN_INFO "Free a DMA Buffer size: %d, virt %p, phys %p.\n", \
					chan->total_length, chan->virt_addr, chan->phys_addr);

			dma_free_coherent(dev, chan->total_length, chan->virt_addr, chan->phys_addr);
		}

		for(i = 0; i < MAX_BD_COUNTS; i++) {
			if(chan->phys_addr_array[i] && chan->virt_addr_array[i]) {
				log_verbose(KERN_INFO "Free a DMA Buffer size: %d, virt %p, phys %p.\n", \
						chan->block_size, chan->virt_addr_array[i], chan->phys_addr_array[i]);

				dma_free_coherent(dev, chan->block_size, chan->virt_addr_array[i], chan->phys_addr_array[i]);
			}
		}
		kfree(chan);
	}
}

/** Description:
 *  Get next buffer descriptor of the DMA channel
 *
 *  @chan The DMA channel
 */

static void* yadma_next_block(DmaChannel *chan)
{
	void *addr;
	if(chan)
	{
		chan->cur_block++;
		if(chan->cur_block >= chan->block_count)
			chan->cur_block = 0;

		addr = chan->virt_addr + chan->cur_block * chan->block_size;
        log_verbose(KERN_INFO "Switch to next block %d, @%p.\n", chan->cur_block, addr);
	}
	return addr;
}


static struct file_operations yadma_cdev_file_ops =
{
	.owner = THIS_MODULE,
    .open = yadma_dev_open,
    .release = yadma_dev_release,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
    .ioctl = yadma_dev_ioctl,
#else
    .unlocked_ioctl = yadma_dev_ioctl,
#endif
};


/** The following code is for registering as a character device driver.
 * The GUI will use /dev/yadma_state file to read state & statistics.
 * Incase of any failure, the driver will come up without device
 * file support, but statistics will still be visible in the system log.
 */

static int yadma_setup_cdev(PrivateDataStru* priv)
{
	int err;

    /* First allocate a major/minor number. */
    err = alloc_chrdev_region(&priv->yadma_dev, 0, 1, "yadma_chrdev");
    if(IS_ERR((int *)err))
        log_verbose(KERN_ERR "Error allocating char device region\n");
    else
    {
        /* Register our character device */
        priv->yadma_cdev = cdev_alloc();
        if(IS_ERR(priv->yadma_cdev))
        {
            log_verbose(KERN_ERR "Alloc error registering device driver\n");
            unregister_chrdev_region(priv->yadma_dev, 1);
            err = priv->yadma_cdev;
        }
        else
        {
            priv->yadma_cdev->owner = THIS_MODULE;
            priv->yadma_cdev->ops = &yadma_cdev_file_ops;
            priv->yadma_cdev->dev = priv->yadma_dev;
            err = cdev_add(priv->yadma_cdev, priv->yadma_dev, 1);
            log_verbose(KERN_INFO "Allocate and add char dev  0x%x\n", priv->yadma_dev);

            if(err < 0)
            {
                log_verbose(KERN_ERR "Error, then unregistering the char dev.\n");
                unregister_chrdev_region(priv->yadma_dev, 1);
            }
        }
    }

    return err;
}



/** yadma Driver information */
static struct pci_driver yadma_driver = {
    .name = DRIVER_NAME,
    .id_table = ids,
    .probe = yadma_pcie_probe,
    .remove = __devexit_p(yadma_remove),
};

/** Private Data of this driver */
static u32 yadmaDriverState = YADMA_UNINITIALIZED;
static int yadmaUserOpen;
struct timer_list stats_timer, demo_timer;

#ifdef HANDLE_MSI_ISR
static unsigned long long PendingMask = 0x0LL;
static int LastIntr[MAX_CHANS]={ 0, };
static int MSIEnabled=0;
static void IntrBH(unsigned long unused);
DECLARE_TASKLET(DmaBH, IntrBH, 0);
#endif



/* for exclusion of all program flows (processes, ISRs and BHs) */
static DEFINE_SPINLOCK(DmaLock);
static DEFINE_SPINLOCK(IntrLock);
static DEFINE_SPINLOCK(DmaStatsLock);


/* Character device file operations */
static int yadma_dev_open(struct inode * in, struct file * filp)
{
    if(yadmaDriverState != YADMA_INITIALIZED)
    {
        log_verbose(KERN_INFO "Driver not yet ready!\n");
        return -1;
    }

    log_verbose(KERN_INFO "Char device open\n");
    spin_lock_bh(&DmaStatsLock);
    yadmaUserOpen++;                 /* To prevent more than one GUI */
    spin_unlock_bh(&DmaStatsLock);

    return 0;
}

static int yadma_dev_release(struct inode * in, struct file * filp)
{
    if(!yadmaUserOpen)
    {
        /* Should not come here */
        log_verbose(KERN_INFO "Device not in use\n");
        return -EFAULT;
    }

    log_verbose(KERN_INFO "Char device release\n");
    spin_lock_bh(&DmaStatsLock);
    yadmaUserOpen-- ;
    spin_unlock_bh(&DmaStatsLock);

    return 0;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int yadma_dev_ioctl(struct inode * in, struct file * filp,
                          unsigned int cmd, unsigned long arg)
#else
static long yadma_dev_ioctl(struct file * filp,
                          unsigned int cmd, unsigned long arg)
#endif
{
    int retval=0;

	GainStru gain_tx1;

    if(yadmaDriverState != YADMA_INITIALIZED)
    {
        /* Should not come here */
        log_verbose("Driver not yet ready!\n");
        return -1;
    }

    log_verbose(KERN_INFO "Run char dev ioctl with code %d.\n", cmd);

    /* Check cmd type and value */
    if(_IOC_TYPE(cmd) != YADMA_MAGIC) return -ENOTTY;
    if(_IOC_NR(cmd) > YADMA_MAX_CMD) return -ENOTTY;

    /* Check read/write and corresponding argument */
    if(_IOC_DIR(cmd) & _IOC_READ)
        if(!access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd)))
            return -EFAULT;
    if(_IOC_DIR(cmd) & _IOC_WRITE)
        if(!access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd)))
            return -EFAULT;

    /* Looks ok, let us continue */
    switch(cmd)
    {

    case IOCTL_SET_TX1_GAIN:
        if(copy_from_user(&gain_tx1, (GainStru *)arg, sizeof(GainStru)))
        {
            log_verbose("\ncopy_from_user failed\n");
            retval = -EFAULT;
            break;
        }

		break;

    default:
        log_verbose("Invalid command %d\n", cmd);
        retval = -1;
        break;
    }

    return retval;
}
/* LOG-1
 *  The following issues occur when insmod yadma.ko to the kernel
 * root@tsinghua:/opt/work/yadma/driver/yadma# uname -a
   Linux tsinghua 3.5.0-17-generic #28-Ubuntu SMP Tue Oct 9 19:32:08 UTC 2012 i686 i686 i686 GNU/Linux

   ** It's fixed by compile the kernel source and using the new kernel image.

[   94.667567] yadma: disagrees about version of symbol kfree_skb
[   94.667570] yadma: Unknown symbol kfree_skb (err -22)
[   94.667573] yadma: disagrees about version of symbol netlink_broadcast
[   94.667574] yadma: Unknown symbol netlink_broadcast (err -22)
[   94.667576] yadma: disagrees about version of symbol __alloc_skb
[   94.667577] yadma: Unknown symbol __alloc_skb (err -22)
[   94.667580] yadma: disagrees about version of symbol init_net
[   94.667581] yadma: Unknown symbol init_net (err -22)
[   94.667585] yadma: disagrees about version of symbol netlink_unicast
[   94.667585] yadma: Unknown symbol netlink_unicast (err -22)
[   94.667587] yadma: disagrees about version of symbol netlink_kernel_release
[   94.667588] yadma: Unknown symbol netlink_kernel_release (err -22)
[   94.667591] yadma: disagrees about version of symbol netlink_kernel_create
[   94.667592] yadma: Unknown symbol netlink_kernel_create (err -22)

*/


/* LOG-2
 * Do not crash after using the empty REG read/write functions.
 *
[  885.031149] yadmaPrivData at f180ba80
[  885.031157] netlink initialized, sock = -260868608.
[  885.031158] register proc files.
[  885.031163] Create procfs /proc//proc/yadma/TxFreqCh1
[  885.031165] Create procfs /proc//proc/yadma/RxFreqCh1
[  885.031166] Create procfs /proc//proc/yadma/TxFreqCh2
[  885.031167] Create procfs /proc//proc/yadma/RxFreqCh2
[  885.031168] Create procfs /proc//proc/yadma/TxGainCh1
[  885.031169] Create procfs /proc//proc/yadma/RxGainCh1
[  885.031171] Create procfs /proc//proc/yadma/TxGainCh2
[  885.031172] Create procfs /proc//proc/yadma/RxGainCh2
[  885.031173] Create procfs /proc//proc/yadma/RSSICh1
[  885.031175] Create procfs /proc//proc/yadma/RSSICh2
[  885.031176] Create procfs /proc//proc/yadma/RFStateCh1
[  885.031177] Create procfs /proc//proc/yadma/RFStateCh2
[  885.031178] Create procfs /proc//proc/yadma/SysTiming
[  885.031180] Create procfs /proc//proc/yadma/FPGAReset
[  885.031181] Create procfs /proc//proc/yadma/IrqInterval
[  885.031182] Create procfs /proc//proc/yadma/TxMemCh1
[  885.031184] Create procfs /proc//proc/yadma/TxMemCh2
[  885.031185] Create procfs /proc//proc/yadma/RxMemCh1
[  885.031187] Create procfs /proc//proc/yadma/RxMemCh2
[  885.031187] Inserting YADMA driver in kernel.
[  885.031221] Allocated a DMA Buffer size: 230400, virt f1fc0000, phys 31fc0000.
[  885.031222] Allocate DMA memory for channel -99088127 success.
[  885.031244] Allocated a DMA Buffer size: 230400, virt eff00000, phys 2ff00000.
[  885.031245] Allocate DMA memory for channel -99088127 success.
[  885.031264] Allocated a DMA Buffer size: 230400, virt eff40000, phys 2ff40000.
[  885.031265] Allocate DMA memory for channel -99088127 success.
[  885.031286] Allocated a DMA Buffer size: 230400, virt eff80000, phys 2ff80000.
[  885.031287] Allocate DMA memory for channel -99088127 success.
[  885.031296] PCI device enable success.
[  885.031296] PCI device is set as master.
[  885.031302] Request PCI regions success.
[  885.031303] Set DMA mask as 32bits.
[  885.031318] ioremap: [BAR 0] Base PA f7c08000 Len 32768 VA f9da0000
[  885.031319] Bar mask is 0xf7767e01
[  885.031320] DMA interrupt disable.
[  885.031321] Read base@ 0xf9da0000 offset@ 0x  (null).
[  885.031322] Write 0x0 to base@ 0xf9da0000 offset@ 0x  (null).
[  885.031322] Set pci drvdata.
[  885.031323] Setup char dev.
[  885.031326] Allocate and add char dev  263192576
[  885.031326] Device registered with major number 251
[  885.031327] probe: Starting stats timer fa182478 after 250
[  885.031328] End of probe
*/
/********************************************************************/
/*  PCI probing function */
/********************************************************************/
static int __devinit yadma_pcie_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    int pciRet, chrRet;
    int i;

    /* Initialize DMA buffers that will be mapped with user space.
     */
#ifdef CHANNEL_STRUCT_FOR_CPIT
    for(i=0; i< MAX_CHANS; i++)
    {
		DmaChannel *ch;
        ch = yadma_create_block_based_channel(&(pdev->dev), i, YADMA_BLOCK_SIZE + YADMA_ADDTION_SIZE);
        if(ch == NULL) {
            log_verbose(KERN_ERR "Unable to create DMA Channel %d.\n", i);
            for(i = 0; i < MAX_CHANS; i++) {
                if(yadmaPrivData->dma_chans[i]) {
                    yadma_destroy_channel(&(pdev->dev), ch);
                    yadmaPrivData->dma_chans[i] = NULL;
                }
            }
            return YADMA_FAILURE;
        } else {
			yadmaPrivData->dma_chans[i] = ch;
			log_verbose("Allocate DMA memory for channel %d success @0x%p .\n", i,  ch);
		}
    }
#else /* CHANNEL_STRUCT_FOR_THU */
    for(i=0; i<MAX_CHANS; i++)
    {
        yadmaPrivData->dma_chans[i] = yadma_create_slot_based_channel(&(pdev->dev), YADMA_BLOCK_COUNT, YADMA_SLOT_COUNT,YADMA_SLOT_SIZE);
        if(yadmaPrivData->dma_chans[i] == NULL) {
            log_verbose(KERN_ERR "Unable to create DMA Channel %d.\n", i);
            for(i = 0; i < MAX_CHANS; i++) {
                if(yadmaPrivData->dma_chans[i]) {
                    yadma_destroy_channel(&(pdev->dev), yadmaPrivData->dma_chans[i]);
                    yadmaPrivData->dma_chans[i] = NULL;
                }
            }
            return YADMA_FAILURE;
        } else {
			log_verbose("Allocate DMA memory for channel %d success @0x%p .\n", i,  yadmaPrivData->dma_chans[i]);
		}
    }
#endif

    /* Initialize device before it is used by driver. Ask low-level
     * code to enable I/O and memory. Wake up the device if it was
     * suspended. Beware, this function can fail.
     */
	pciRet = pci_enable_device(pdev);
	if (pciRet < 0)
	{
	    log_verbose(KERN_ERR "PCI device enable failed.\n");
	    return pciRet;
	}
    else
    {
        log_verbose(KERN_INFO "PCI device enable success.\n");
    }
    /*
     * Enable bus-mastering on device. Calls pcibios_set_master() to do
     * the needed architecture-specific settings.
     */
    log_verbose(KERN_INFO "PCI device is set as master.\n");
    pci_set_master(pdev);

    /* Reserve PCI I/O and memory resources. Mark all PCI regions
     * associated with PCI device as being reserved by owner. Do not
     * access any address inside the PCI regions unless this call returns
     * successfully.
     */
    pciRet = pci_request_regions(pdev, DRIVER_NAME);
    if (pciRet < 0) {
        log_verbose(KERN_ERR "Could not request PCI regions.\n");
        pci_disable_device(pdev);
        return pciRet;
    } else {
        log_verbose(KERN_INFO "Request PCI regions success.\n");
    }

    /* Returns success if PCI is capable of 32-bit DMA */
#if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,36)
    pciRet = pci_set_dma_mask(pdev, DMA_32BIT_MASK);
#else
    pciRet = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
#endif

    if (pciRet < 0) {
        log_verbose(KERN_ERR "pci_set_dma_mask failed\n");
        pci_release_regions(pdev);
        pci_disable_device(pdev);
        return pciRet;
    } else {
        log_verbose(KERN_INFO "Set DMA mask as 32bits.\n");
    }

    /* Map all BARs of the PCI device.
     * First read all the BAR-related information.
     * remap it to a virtual address.
     */
    for(i=0; i<MAX_BARS; i++) {
        u32 size;

        /* At least BAR0 must be there. */
        if ((size = pci_resource_len(pdev, i)) == 0) {
            if (i == 0) {
                log_verbose(KERN_ERR "BAR %d not valid, aborting.\n", i);
                pci_release_regions(pdev);
                pci_disable_device(pdev);
                return YADMA_FAILURE;
            }
            else {
                log_verbose(KERN_INFO "Get BAR %d resource length failed, continue to next BAR.\n", i);
                continue;
            }
        }
        /* Set a bitmask for all the BARs that are present. */
        else
            (yadmaPrivData->bar_mask) |= ( 1 << i );

        /* Check all BARs for memory-mapped or I/O-mapped. The driver is
         * intended to be memory-mapped.
         */
        if (!(pci_resource_flags(pdev, i) & IORESOURCE_MEM)) {
            log_verbose(KERN_ERR "BAR %d is of wrong type, aborting.\n", i);
            pci_release_regions(pdev);
            pci_disable_device(pdev);
            return YADMA_FAILURE;
        }

        /* Get base address of device memory and length for all BARs */
        yadmaPrivData->bar_info[i].bar_phys_addr = pci_resource_start(pdev, i);
        yadmaPrivData->bar_info[i].bar_len = size;

        /* Map bus memory to CPU space. The ioremap may fail if size
         * requested is too long for kernel to provide as a single chunk
         * of memory, especially if users are sharing a BAR region. In
         * such a case, call ioremap for more number of smaller chunks
         * of memory. Or mapping should be done based on user request
         * with user size. Neither is being done now - maybe later.
         */
        if((yadmaPrivData->bar_info[i].bar_virt_addr =
            ioremap((yadmaPrivData->bar_info[i].bar_phys_addr), size)) == 0UL)
        {
            log_verbose(KERN_ERR "Cannot map BAR %d space, invalidating.\n", i);
            (yadmaPrivData->bar_mask) &= ~( 1 << i );
        }
        else
        {
            log_verbose(KERN_INFO "ioremap: [BAR %d] Base PA %p Len %x VA %p\n", i,
                (yadmaPrivData->bar_info[i].bar_phys_addr),
                (yadmaPrivData->bar_info[i].bar_len),
                (yadmaPrivData->bar_info[i].bar_virt_addr));
        }
    }
    log_verbose(KERN_INFO "Bar mask is 0x%x\n", (yadmaPrivData->bar_mask));

    /* Disable global interrupts */
    log_verbose(KERN_INFO "DMA interrupt disable.\n");
    yadmaIntDisable(yadmaPrivData->bar_info[0].bar_virt_addr);

    yadmaPrivData->pdev=pdev;

    /* Initialize DMA common registers !!!! */

	/* Reset FPGA */
	yadma_write_ctrl_bar(REG_DSP_SOFT_RESET, 1);
	yadma_write_ctrl_bar(REG_DSP_SOFT_RESET, 0);
	
	
   // yadma_write_ctrl_bar(0xf, 0x10001);
	

    // RESET the Chip 
	yadma_write_ctrl_bar(REG_LED_AND_RESET, 0);
	WAIT(1);
	yadma_write_ctrl_bar(REG_LED_AND_RESET, 0xFFFFFFFF);

	/* Set nco frequency */
	yadma_write_ctrl_bar(0xD, 0x3FFFFF);

	/* Set nco gain */
	yadma_write_ctrl_bar(0xE, 0x7FFF);

#ifdef CHANNEL_STRUCT_FOR_CPIT
	/* Set block pointers; Length is set by FPGA */
    yadma_init_block_based_descriptors(TX_CHAN, CUR_TX_BD_COUNT);
	yadma_init_block_based_descriptors(RX_CHAN, CUR_RX_BD_COUNT);

    //adc config
    yadma_write_ctrl_bar(0x614,0xc1);
    yadma_write_ctrl_bar(0x617,0x1f);
    yadma_write_ctrl_bar(0x700,0xab);
    yadma_write_ctrl_bar(0x702,0x04);
    yadma_write_ctrl_bar(0x711,0x00);
    yadma_write_ctrl_bar(0x6ff,0x01); //enable above configurations


    //ADC直流校准流程

    yadma_write_ctrl_bar(0x70c,0x23);
    yadma_write_ctrl_bar(0x6ff,0x1);

    //wait(1ms)
    mdelay(1000);
    
    // set the AFC DAC value  
    yadma_write_ctrl_bar(0x01F,0x800);
    
    // change the channel 0 and channel 1 data to the WCDMA function
    yadma_write_ctrl_bar(REG_CHANNEL_SWAP,0x00000);
    
    
    yadma_write_ctrl_bar(0xB97,0x63);   // Set the 10Mhz output to 10Mhz 
    yadma_write_ctrl_bar(0xC34,0x01);   // EWnable the 10Mhz set 


    yadma_write_ctrl_bar(0x70C,0x63);   // remove the ADC DC
    yadma_write_ctrl_bar(0x6ff,0x01);

    yadma_write_ctrl_bar(0x9, 31);    // set RX DMA buffer number
    yadma_write_ctrl_bar(REG_TX_BD_COUNT, 3); //set TX DMA buffer number

	yadma_write_ctrl_bar(REG_PCIE_WAIT_CYCLE, 0);
    yadma_write_ctrl_bar(REG_SMAPLE_RATE_IF, 0x003);             // use the IF input . sampel rate is 2x
    yadma_write_ctrl_bar(REG_NCO_CONFIG, 0xF0000000);         // nco frequency to -7.68Mhz

    yadma_write_ctrl_bar(REG_PSC_CORR_LEVEL, 0x20);         // Set the PSC cell search corr amp level

    /* Set Route and Control register, no TX and RX */
    yadma_write_ctrl_bar(REG_ROUTE_AND_CTRL, 0 ); ///* 0x11211 THU NCO TEST*/  0x10810 /* LTE*/); //TX & RX @ RF enabled

#else
    /* Set DMA buffer to DMA channels */
    yadma_write_ctrl_bar(REG_TX0_BUF_ADDR, yadmaPrivData->dma_chans[TX_CHAN_1]->phys_addr);
    yadma_write_ctrl_bar(REG_RX0_BUF_ADDR, yadmaPrivData->dma_chans[RX_CHAN_1]->phys_addr);
    yadma_write_ctrl_bar(REG_TX1_BUF_ADDR, yadmaPrivData->dma_chans[TX_CHAN_2]->phys_addr);
    yadma_write_ctrl_bar(REG_TX1_BUF_ADDR, yadmaPrivData->dma_chans[RX_CHAN_2]->phys_addr);

    /* Set Route and Control register */
    yadma_write_ctrl_bar(REG_ROUTE_AND_CTRL, ROUTE_CTL_PCIE_LOOPBACK_MODE);
#endif

    /* Set interrupt interval register */
    yadma_write_ctrl_bar(REG_INT_MASK_AND_SLOTS, (YADMA_INTERUPT_SLOTS-1) << 16);

    /* Save private data pointer in device structure */
    /*
    log_verbose(KERN_INFO "Set pci drvdata.\n");
    pci_set_drvdata(pdev, yadmaPrivData);
	*/

	/* Setup character device "/dev/yadma" */
    log_verbose(KERN_INFO "Setup char dev.\n");
	yadma_setup_cdev(yadmaPrivData);

    if(!IS_ERR((int *)chrRet))
    {
		log_verbose(KERN_INFO "Device registered with major number %d\n",
			MAJOR(yadmaPrivData->yadma_dev));

		/* Initialise all stats pointers */
		for(i=0; i<MAX_CHANS; i++)
		{

		}


        /* Start stats polling routine */
        log_verbose(KERN_INFO "probe: Starting stats timer %p after %d\n",
                                            &stats_timer, HZ);
        /* Now start timer */
        init_timer(&stats_timer);
        stats_timer.expires=jiffies + HZ;
        stats_timer.data=(unsigned long) pdev;
        stats_timer.function = yadma_stats;
        add_timer(&stats_timer);
    }

    yadmaDriverState = YADMA_INITIALIZED;



#ifdef HANDLE_MSI_ISR
    /* Now enable interrupts using MSI mode */
    if(!pci_enable_msi(pdev))
    {
        log_verbose(KERN_INFO "MSI enabled\n");
        MSIEnabled = 1;
    }

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18)
    pciRet = request_irq(pdev->irq, yadma_interrupt_handler, SA_SHIRQ, "yadma", pdev);
#else
    pciRet = request_irq(pdev->irq, yadma_interrupt_handler, IRQF_SHARED, "yadma", pdev);
#endif

    if(pciRet)
    {
        log_verbose(KERN_ERR "yadma could not allocate interrupt %d\n", pdev->irq);
    }
    else
    {
        log_verbose(KERN_INFO "Allocate MSI interrupt %d.\n", pdev->irq);
    }

    /* Now, enable global interrupts. Engine interrupts will be enabled
     * only when they are used.
     */
    log_verbose("Value of HZ is %d\n", HZ);
    //yadmaIntEnable(yadmaPrivData->bar_info[0].bar_virt_addr);

#endif
	/* register sysfs files */
	register_sysfs_files(&pdev->dev.kobj);

    log_verbose("End of probe\n");
	return 0;
out_release_attr_group:

out_release_irq:
	free_irq(pdev->irq, pdev);

}

static void __devexit  yadma_remove(struct pci_dev *pdev)
{
  struct privData *lp;
    int i;
#ifdef HANDLE_MSI_ISR
    u32 girqval;
    u64 base;
#endif

    log_verbose("Came to yadma_remove\n");
    /*
     * lp = pci_get_drvdata(pdev);
	 */

    /* The driver state flag has already been changed */

    // mdelay(1000);

    /* Stop the polling routines */
    spin_lock_bh(&DmaStatsLock);
    log_verbose(KERN_INFO "Disable stats timer.\n");
    del_timer_sync(&stats_timer);
    spin_unlock_bh(&DmaStatsLock);

    spin_lock_bh(&DmaLock);
		/* Do something need in lock */
    spin_unlock_bh(&DmaLock);

#ifdef HANDLE_MSI_ISR
    base = (u64)(yadmaPrivData->bar_info[0].bar_virt_addr);
    log_verbose(KERN_INFO "Disable DMA interrupt @%p.\n", base);
    yadmaIntDisable(base);

    /* Disable MSI and interrupts */
    log_verbose(KERN_INFO "Free IRQ.\n");
    free_irq(pdev->irq, pdev);


    if(MSIEnabled) {
        pci_disable_msi(pdev);
        log_verbose(KERN_INFO "PCI Disable MSI.\n");
    }
    girqval = yadmaReadReg(base, REG_ROUTE_AND_CTRL);
    log_verbose("While disabling interrupts, got %x\n", girqval);
#endif


    for(i=0; i<MAX_BARS; i++)
    {
        if((yadmaPrivData->bar_mask) & ( 1 << i )) {
            log_verbose(KERN_INFO "iounmap: BAR %d virt = %p.\n", i, yadmaPrivData->bar_info[i].bar_virt_addr);
            iounmap(yadmaPrivData->bar_info[i].bar_virt_addr);
        }
    }

    if(yadmaPrivData->yadma_cdev != NULL)
    {
		log_verbose("Unregistering char device driver 0x%x\n", yadmaPrivData->yadma_dev);
		cdev_del(yadmaPrivData->yadma_cdev);
		unregister_chrdev_region(yadmaPrivData->yadma_dev, 1);
    }

	log_verbose(KERN_INFO "PCI release regions and disable device.\n");
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);

	/* unregister sysfs files when driver is removed */
    log_verbose(KERN_INFO "unregister sysfs files.\n");
	unregister_sysfs_files(&pdev->dev.kobj);

    /* Reset DMA - this includes disabling interrupts and DMA. */
	log_verbose(KERN_INFO "Destroy DMA channels...\n");
	/* Stop DMA RX and TX first */
    yadma_write_ctrl_bar(REG_ROUTE_AND_CTRL, 0 );
    for(i=0; i<MAX_CHANS; i++)
    {
		yadma_destroy_channel(&(pdev->dev), yadmaPrivData->dma_chans[i]);
		yadmaPrivData->dma_chans[i] = NULL;
    }
}

static struct sock *nl_sk = NULL;
static int nl_pid = -1;
static bool parse_bar_operation(BarOpStru *bop)
{
    bool ret = 0;
	RegPair* rp = bop->data;
	if((u32)bop->bar < MAX_BARS) {
		int i;
		for(i = 0; i < bop->count; i++) {
			ret = 1;
            if(rp->reg * 4 < yadmaPrivData->bar_info[bop->bar].bar_len) {
				if(bop->op == KUC_BAR_OP_READ) {
					rp->value = yadmaReadReg(yadmaPrivData->bar_info[bop->bar].bar_virt_addr, rp->reg);
					printk("KRead %x, value %x\n", rp->reg, rp->value);
				} else if(bop->op == KUC_BAR_OP_WRITE) {
					yadmaWriteReg(yadmaPrivData->bar_info[bop->bar].bar_virt_addr, rp->reg, rp->value);
					printk("Write %x, value %x\n", rp->reg, rp->value);
				} else {
                    log_verbose(KERN_ERR "Unknown BAR operation\n");
                    ret = 0;
                    break;
				}
			} else {
                log_verbose(KERN_ERR "Operation is over the BAR's length");
                ret = 0;
                break;
            }
			rp++;
		}
	} else {
        log_verbose(KERN_ERR "Unknown BAR.\n");
    }
    return ret;
}

static void netlink_data_ready (struct sk_buff *__skb)
{
	struct nlmsghdr *nlh = NULL;
	struct sk_buff *skb;

	mutex_lock(&privDataLock);
	skb = skb_get (__skb);

	if(skb->len >= NLMSG_SPACE(0))
	{
		nlh = nlmsg_hdr(skb);

#ifdef DUMP_NETLINK_DATA
		//nlh = (struct nlmsghdr *)skb->data;
		log_verbose("%s Received msg @0x%p.\n", __FUNCTION__, nlh);

		/* dump the received buffer */
		print_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_ADDRESS, 16, 1, nlh, nlh->nlmsg_len, true);
#endif
		nl_pid = nlh->nlmsg_pid; /*pid of sending process */
		KucMessage * kuc = (KucMessage *)nlh;
		switch(kuc->type)
		{
			case KUC_TYPE_GAIN: {
				GainStru * gain;
				gain = (GainStru*)kuc->data;
				break;
			}
			case KUC_TYPE_FINISH: {
				FinishStru * fi;
				fi = (FinishStru*)kuc->data;
				break;
			}
			case KUC_TYPE_BAR_OP: {
				BarOpStru *bop;
				bop = (BarOpStru*)kuc->data;
				if(parse_bar_operation(bop)){
                    /* return the read/write result back */                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
                    netlink_send_to_userspace(kuc, 0);
                }
				break;
			}
			case KUC_TYPE_REGISTER: {
				log_verbose("Process id = %d is registered.\n", nl_pid);
				nl_pid = nlh->nlmsg_pid;
				break;
			}

            case KUC_TYPE_VERSION_INFO: {
                break;
            }

            case KUC_TYPE_BOARD_INFO: {
                break;
            }

			default:
				break;
		}
	}
	/* keep kfree_skb in pair with skb_get */
	kfree_skb(skb);
	//Wake interrupt if time for process received data is too long
	//wake_up_interruptible(sk->sleep);

	/* A kernel thread is waiting for message coming down from user-space */
	// skb = skb_recv_datagram(nl_sk, 0, 0, &err);
	mutex_unlock(&privDataLock);
}

static void netlink_init(void)
{
 	nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, 0, netlink_data_ready, NULL, THIS_MODULE);
    log_verbose(KERN_INFO "netlink initialized, sock = 0x%p.\n", nl_sk);
}

static void netlink_destroy(void)
{
    log_verbose(KERN_INFO "netlink destroyed, sock = 0x%p.\n", nl_sk);
	netlink_kernel_release(nl_sk);
}

/* Assumption: Only one process is allowed to exchange data
 * with this driver through netlink */
static void netlink_send_to_userspace(KucMessage*kuc, bool multicast)
{
	struct sk_buff *skb_out = NULL;
	struct nlmsghdr *nlh = NULL;

	skb_out = nlmsg_new(kuc->len, GFP_ATOMIC);

	if(skb_out==NULL) {
		log_verbose("%s: Allocate skb buffer failed.\n", __FUNCTION__);
		return;
	}

	// NOT WORK: nlh = (struct nlmsghdr *)skb_out->data;
	nlh = nlmsg_put(skb_out,0,0,0,kuc->len - sizeof(struct nlmsghdr),0);

	/* copy the specific structure's content */
	memcpy(nlh, kuc, kuc->len);

	/* Fill the nl message header */
	nlh->nlmsg_len = kuc->len;
	nlh->nlmsg_pid = 0;  /* from kernel */
	nlh->nlmsg_flags = 0;

#ifdef DUMP_NETLINK_DATA
	log_verbose("%s: send message, sk_buff@0x%p, nlh@0x%p, nld@0x%p.\n", __FUNCTION__, \
									skb_out, nlh, NLMSG_DATA(nlh));
	/* dump the socket buffer */
	print_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_ADDRESS, 16, 1, nlh, nlh->nlmsg_len, true);
#endif

	if(multicast) {
		NETLINK_CB(skb_out).pid = 0;  /* from kernel */
		/* to mcast group 1<<0 */
		NETLINK_CB(skb_out).dst_group = 1;
		/*multicast the message to all listening processes*/
		netlink_broadcast(nl_sk, skb_out, 0, 1, GFP_ATOMIC);
	} else {
		NETLINK_CB(skb_out).pid = 0;	  /* from kernel */
		NETLINK_CB(skb_out).dst_group = 0;  /* unicast */
		if(nl_pid != -1) {
		    netlink_unicast(nl_sk, skb_out, nl_pid, MSG_DONTWAIT);
		} else {
		    nlmsg_free(skb_out);
		}
		//nlmsg_unicast(nl_sk, skb_out, nl_pid);
	}

	/* BE CAREFUL: You're not allowed to free the skb after you've sent it.
	 * nlmsg_unicast() will take care of that.
	 */

	/* Nerver call: nlmsg_free(skb_out); */
}

static void yadmaWorkFunc(struct work_struct *work)
{
    mutex_lock(&privDataLock);
    frame_report(work);
    mutex_unlock(&privDataLock);
}
#include "ad9361_api.h"
static int __init yadma_init(void)
{
    int i;
  /* Initialize the locks */
  spin_lock_init(&DmaLock);
  spin_lock_init(&IntrLock);
  spin_lock_init(&DmaStatsLock);

    //AD9362_write_Config();
    //AD9361_InitParam *init_param;
    //struct ad9361_rf_phy *phy;
    
    //init_param = (struct AD9361_InitParam *)kmalloc(sizeof(*init_param), GFP_KERNEL);
	//phy = (struct ad9361_rf_phy *)kmalloc(sizeof(*phy), GFP_KERNEL); 
    
    
    /*  AD9362 driver init */
    //ad9361_init(init_param);
    
    mutex_lock(&privDataLock);
    /* Allocate space for holding driver-private data - for storing driver
     * context.
     */
    yadmaPrivData = kmalloc(sizeof(PrivateDataStru), GFP_KERNEL);
    if(yadmaPrivData == NULL)
    {
        log_verbose(KERN_ERR "Unable to allocate YADMA private data.\n");
        return YADMA_FAILURE;
    } else {
		log_verbose("yadmaPrivData at 0x%p\n", yadmaPrivData);
		memset((void*)yadmaPrivData, 0, sizeof(PrivateDataStru));
        yadmaPrivData->TxFreqCh1 = DEFAULT_TX_FREQ;
        yadmaPrivData->TxFreqCh2 = DEFAULT_TX_FREQ;
        yadmaPrivData->RxFreqCh1 = DEFAULT_RX_FREQ;
        yadmaPrivData->RxFreqCh2 = DEFAULT_RX_FREQ;
	}

    yadmaWork = kzalloc(sizeof(*yadmaWork), GFP_KERNEL);
    yadmaWorkQue = create_singlethread_workqueue("yamdaWorkQueue");
    if(yadmaWorkQue && yadmaWork) {
        INIT_WORK(yadmaWork, yadmaWorkFunc);
    } else {
        log_verbose("No memory for allocating work queue\n");
    }
    mutex_unlock(&privDataLock);
#ifdef DEMO_IN_TIMER
  init_timer(&demo_timer);
  demo_timer.expires=jiffies + 5*HZ;
  demo_timer.function = yadma_demo;
  add_timer(&demo_timer);
#endif

  /* Initialize the netlink socket */
  netlink_init();

  /* Register procfs files */
  log_verbose(KERN_INFO "register proc files.\n");
  register_proc_files();

  /* Just register the driver. No kernel boot options used. */
  log_verbose(KERN_INFO "Inserting YADMA driver in kernel.\n");
  return pci_register_driver(&yadma_driver);
}

static void __exit yadma_cleanup(void)
{

    int oldstate, i;

    log_verbose("Came to yadma_cleanup\n");
    tasklet_disable( &the_tasklet );
	tasklet_kill( &the_tasklet );
    flush_workqueue(yadmaWorkQue);
    destroy_workqueue(yadmaWorkQue);
    //kfree(yadmaWork);

    mutex_lock(&privDataLock);
    /* Then, unregister driver with PCI in order to free up resources */
    log_verbose(KERN_INFO "pci unregister driver.\n");
    pci_unregister_driver(&yadma_driver);


#ifdef DEMO_IN_TIMER
    del_timer_sync(&demo_timer);
#endif
    /* First, change the driver state - so that other entry points
     * will not make a difference from this point on.
     */
    oldstate = yadmaDriverState;
    yadmaDriverState = YADMA_UNINITIALIZED;

	/* destroy netlink socket */
	netlink_destroy();

	/* remove procfs files */
	unregister_proc_files();

    if(yadmaPrivData != NULL)
    {
		log_verbose("Free yadma private data @ 0x%p", yadmaPrivData);
		kfree(yadmaPrivData);
		yadmaPrivData = NULL;
    }
    mutex_unlock(&privDataLock);
}

static void yadma_stats(unsigned long __opaque)
{
    struct pci_dev *pdev = (struct pci_dev *)__opaque;

    if(yadmaDriverState == YADMA_UNINITIALIZED)
        return;

}

#ifdef DEMO_IN_TIMER
static void yadma_demo(unsigned long __opaque)
{
	struct pci_dev *pdev = (struct pci_dev *)__opaque;
	int data_len = NLMSG_SPACE(sizeof(KucMessage)) + sizeof(InterruptStru);

    log_verbose(KERN_INFO "yadma periodic timer triggered at 0x%x.\n", jiffies);

    /* In timeout context, allocate memory with ATOMIC flag */
	KucMessage*kuc = (KucMessage*)kmalloc(data_len, GFP_ATOMIC);

	if(kuc) {
		memset(kuc, 0xFF, data_len);
		kuc->type = KUC_TYPE_INTERRUPT;
		kuc->len = data_len;

		InterruptStru *in = (InterruptStru*)kuc->data;
        getnstimeofday(&(in->time));
        in->mask = INT_MULTIPLE_SLOT_END;
        in->multi = YADMA_INTERUPT_SLOTS;
        in->ch = 0;
        in->block = 1;
        in->frame = 2;
        in->slot = 3;

        /* multicast to all group members */
        //netlink_send_to_userspace(kuc, 1);

       /* unicast to lastest received process */
        netlink_send_to_userspace(kuc, 0);
        kfree(kuc);
    }

    /* set the timer again */
	demo_timer.expires=jiffies + 50*HZ;
    demo_timer.function = yadma_demo;
	add_timer(&demo_timer);
}
#endif

static void IntrBH(unsigned long unused)
{
    struct pci_dev *pdev;

}

static u32 Acks(u32 dirqval)
{
    u32 retval=0;


    log_verbose(KERN_INFO "Acking %x with %x\n", dirqval, retval);
    return retval;
}

/* This function serves to handle the initial interrupt, as well as to
 * check again on pending interrupts, from the BH. If this is not done,
 * interrupts can stall.
 */
static int IntrCheck(struct pci_dev * dev)
{
    int retval = 0;
    struct PrivateDataStru *lp;

    /*
     * lp = pci_get_drvdata(dev);
     */

    //log_verbose(KERN_INFO "IntrCheck: device %x\n", (u32) dev);

    return retval;
}

/* Bottom Half Function: tasklet */
static void  frame_report(unsigned long data)
{

    int n, max, gain;
    DmaChannel * ch;
    //log_verbose(KERN_INFO "Handle an interrupt, irq = %d.\n", irq);

	int data_len = NLMSG_SPACE(sizeof(KucMessage)) + sizeof(InterruptStru);

    /* In timeout context, allocate memory with ATOMIC flag */
	KucMessage*kuc = (KucMessage*)kmalloc(data_len, GFP_ATOMIC);

    if(kuc) {
        memset(kuc, 0xFF, data_len);
        kuc->type = KUC_TYPE_INTERRUPT;
        kuc->len = data_len;

        InterruptStru *in = (InterruptStru*)kuc->data;
        getnstimeofday(&(in->time));
        in->mask = INT_MULTIPLE_SLOT_END;
        in->multi = YADMA_INTERUPT_SLOTS;
        in->ch = 0;
#ifdef CHANNEL_STRUCT_FOR_CPIT
        n = yadma_read_ctrl_bar(REG_CUR_BD) & 0xFF;
        max = yadma_read_ctrl_bar(REG_BD_COUNT) & 0xFF;
        in->block = PREV_BD(n, max);
        
        in->sync_status = yadma_read_ctrl_bar(REG_SYNC_STATUS);      /*REVISIT duanchenyi*/
        in->coars_freq_est = ((yadma_read_ctrl_bar(REG_FREQ_EST) & MASK_HIGH_WORD) >> 16);    /*REVISIT duanchenyi*/ 
        in->fine_freq_est = (yadma_read_ctrl_bar(REG_FREQ_EST) & MASK_LOW_WORD);     /*REVISIT duanchenyi*/
        in->freq_est = yadma_read_ctrl_bar(REG_DOWNLINK_FREQ_OFFSET);    /*REVISIT duanchenyi*/
        in->timing_est = yadma_read_ctrl_bar(REG_TIMING_EST);     /*REVISIT duanchenyi*/
        
		if(max > YADMA_BLOCK_COUNT || n > YADMA_BLOCK_COUNT) {
			//log_verbose("Wrong register max = %d, n = %d", max, n);
			kfree(kuc);
			return;
		}

        ch = yadmaPrivData->dma_chans[RX_CHAN];
        ch->cur_block = in->block;
        /* move the gain value to block addtion tail */

        gain = yadma_read_ctrl_bar(REG_AGC_GAIN_READ);

        //log_verbose(KERN_INFO "Frame Interrupt: n=%d, max=%d, ch=%p, gain=%d\n", n,max, ch, gain);
		/* dump the current block buffer */
		//print_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_ADDRESS, 4, 2, ch->virt_addr_array[ch->cur_block], 6144, true);

        yadma_channel_write_addtion(ch, YADMA_GAIN_OFFSET, gain);
#else
        in->block = 0; /* TODO, support mutiple block in FPGA */
        
#endif
        in->frame = (yadma_read_ctrl_bar(REG_FRAME_AND_SLOT_NUM) & BIT_MASK_CUR_FRAME) >> 8;
        in->slot = (yadma_read_ctrl_bar(REG_FRAME_AND_SLOT_NUM) & BIT_MASK_CUR_SLOT);
		if(in->frame > YADMA_BLOCK_COUNT || in->slot > YADMA_SLOT_COUNT
			|| in->frame < 0 || in->slot < 0) {
			log_verbose("Wrong register frame = %d, slot = %d", in->frame, in->slot);
			kfree(kuc);
			return;
		}
        /* multicast to all group members */
        //netlink_send_to_userspace(kuc, 1);

        /* unicast to lastest received process */
        netlink_send_to_userspace(kuc, 0);
        kfree(kuc);
    }
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,19)
static irqreturn_t yadma_interrupt_handler(int irq, void *dev_id, struct pt_regs *regs)
#else
static irqreturn_t yadma_interrupt_handler(int irq, void *dev_id)
#endif
{

   struct pci_dev *dev = dev_id;
   static debug_counter = 0;
   // 1. Cause race condition
   // tasklet_schedule( &the_tasklet );
    if(yadmaWorkQue && yadmaWork && debug_counter++ < 100)
        queue_work(yadmaWorkQue, yadmaWork);

  /* Handle DMA and any user interrupts */
  if(IntrCheck(dev) == YADMA_SUCCESS)
        return IRQ_HANDLED;
    else
        return IRQ_NONE;
}

int yadma_slot_based_channel_mmap(int ch, struct vm_area_struct *vma)
{
	int err;
	long int offset;

    if(yadmaPrivData == NULL || yadmaPrivData->dma_chans[ch] == NULL)
        return -EINVAL;

    log_verbose("Channel %d is mmapped to physical addr %#x.\n", ch, yadmaPrivData->dma_chans[ch]->phys_addr);

	offset = vma->vm_pgoff << PAGE_SHIFT;
	err = remap_pfn_range( vma,
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[ch]->phys_addr + offset) >> PAGE_SHIFT,
	        vma->vm_end - vma->vm_start,
	        vma->vm_page_prot
	        );

    return err;
}

int yadma_block_based_channel_mmap(int ch, struct vm_area_struct *vma)
{
	int err;
	long int block;

    if(yadmaPrivData == NULL || yadmaPrivData->dma_chans[ch] == NULL)
        return -EINVAL;

	block = vma->vm_pgoff;
	if(block >= block_count[ch])
		return -EINVAL;

    log_verbose("Channel %d is mmapped to block = %d, phys_addr =%#x.\n", ch, block, yadmaPrivData->dma_chans[ch]->phys_addr_array[block]);

	err = remap_pfn_range( vma,
	        vma->vm_start,
	        (yadmaPrivData->dma_chans[ch]->phys_addr_array[block]) >> PAGE_SHIFT,
	        vma->vm_end - vma->vm_start,
	        vma->vm_page_prot
	        );

    return err;
}
module_init(yadma_init);
module_exit(yadma_cleanup);
