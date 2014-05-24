/*****************************************************************************/
/**
 *
 * @file yadma_sysfs.c
 *
 * This is the file which implements sysfs parameters read/write operations,
 * and mmap the kernel memory to userspace functions.
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
#include <linux/proc_fs.h>

#include <linux/mm.h>
#include <linux/spinlock.h>
#include <linux/pagemap.h>
#include <asm/scatterlist.h>

#include <linux/delay.h>
#include <linux/list.h>
#include "yadma.h"
#include "yadma_reg.h"
#include "yadma_sysfs.h"
#include "yadma_knl.h"



/************************** Constant Definitions *****************************/

/* Interface Between Userspace that using sysfs */



/*-------------------------------------IRQ Interval-----------------------------------------*/
ssize_t show_irq_interval(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_irq_interval(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

/*-------------------------------------FREQ point -----------------------------------------*/
ssize_t show_tx1_freq(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_tx1_freq(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_tx2_freq(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}


ssize_t set_tx2_freq(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_rx1_freq(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_rx1_freq(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_rx2_freq(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_rx2_freq(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

/*-------------------------------------RF Gain-----------------------------------------*/
ssize_t show_tx1_gain(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_tx1_gain(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_tx2_gain(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}


ssize_t set_tx2_gain(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_rx1_gain(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_rx1_gain(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_rx2_gain(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_rx2_gain(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

/*-------------------------------------RSSI and State-----------------------------------------*/
ssize_t show_tx1_rssi(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_tx1_rssi(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_tx2_rssi(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}


ssize_t set_tx2_rssi(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_rx1_rf_state(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_rx1_rf_state(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_rx2_rf_state(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_rx2_rf_state(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

/*-------------------------------------Timing and Reset ---------------------------------------*/

ssize_t show_sys_timing(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t set_sys_timing(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}

ssize_t show_fpga_reset(struct device *dev, struct device_attribute *attr, char *buf)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}


ssize_t set_fpga_reset(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	log_verbose("%s: buffer content: %s.\n", __FUNCTION__ , buf);
	return 0;
}


/* Sysfs device attributes are used to exchange parameters between kernel and user space */
static DEVICE_ATTR(IrqInterval, S_IRUGO | S_IWUSR, show_irq_interval, set_irq_interval);

static DEVICE_ATTR(TxFreqCh1, S_IRUGO | S_IWUSR, show_tx1_freq, set_tx1_freq);
static DEVICE_ATTR(TxFreqCh2, S_IRUGO | S_IWUSR, show_tx2_freq, set_tx2_freq);
static DEVICE_ATTR(RxFreqCh1, S_IRUGO | S_IWUSR, show_rx1_freq, set_rx1_freq);
static DEVICE_ATTR(RxFreqCh2, S_IRUGO | S_IWUSR, show_rx2_freq, set_rx2_freq);

static DEVICE_ATTR(TxGainCh1, S_IRUGO | S_IWUSR, show_tx1_gain, set_tx1_gain);
static DEVICE_ATTR(TxGainCh2, S_IRUGO | S_IWUSR, show_tx2_gain, set_tx2_gain);
static DEVICE_ATTR(RxGainCh1, S_IRUGO | S_IWUSR, show_rx1_gain, set_rx1_gain);
static DEVICE_ATTR(RxGainCh2, S_IRUGO | S_IWUSR, show_rx2_gain, set_rx2_gain);

static DEVICE_ATTR(RSSICh1, S_IRUGO | S_IWUSR, show_tx1_rssi, set_tx1_rssi);
static DEVICE_ATTR(RSSICh2, S_IRUGO | S_IWUSR, show_tx2_rssi, set_tx2_rssi);
static DEVICE_ATTR(RFStateCh1, S_IRUGO | S_IWUSR, show_rx1_rf_state, set_rx1_rf_state);
static DEVICE_ATTR(RFStateCh2, S_IRUGO | S_IWUSR, show_rx2_rf_state, set_rx2_rf_state);


static DEVICE_ATTR(SysTiming, S_IRUGO | S_IWUSR, show_sys_timing, set_sys_timing);
static DEVICE_ATTR(FPGAReset, S_IRUGO | S_IWUSR, show_fpga_reset, set_fpga_reset);


static struct attribute *dev_attrs[] = {
		&dev_attr_TxFreqCh1.attr,
		&dev_attr_TxFreqCh2.attr,
		&dev_attr_RxFreqCh1.attr,
		&dev_attr_RxFreqCh2.attr,

		&dev_attr_TxGainCh1.attr,
		&dev_attr_TxGainCh2.attr,
		&dev_attr_RxGainCh1.attr,
		&dev_attr_RxGainCh2.attr,

		&dev_attr_RSSICh1.attr,
		&dev_attr_RSSICh2.attr,
		&dev_attr_RFStateCh1.attr,
		&dev_attr_RFStateCh2.attr,

		&dev_attr_SysTiming.attr,
		&dev_attr_FPGAReset.attr,
		&dev_attr_IrqInterval.attr,

		NULL,
};


/* sysfs bin_attributes are used to be mmapped into userspace */
static int rx_mem_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;

	DUMP_MMAP_INFO(RX_CHAN);

    err = yadma_block_based_channel_mmap(RX_CHAN, vma);

	return err;
}

static int tx_mem_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;

	DUMP_MMAP_INFO(TX_CHAN);

    err = yadma_block_based_channel_mmap(TX_CHAN, vma);

	return err;
}

static int tx_mem_ch1_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;

	DUMP_MMAP_INFO(TX_CHAN_1);

    err = yadma_slot_based_channel_mmap(TX_CHAN_1, vma);

	return err;
}
static int tx_mem_ch2_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;

	DUMP_MMAP_INFO(TX_CHAN_2);

    err = yadma_slot_based_channel_mmap(TX_CHAN_2, vma);

	return err;
}
static int rx_mem_ch1_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;

	DUMP_MMAP_INFO(TX_CHAN_1);

    err = yadma_slot_based_channel_mmap(RX_CHAN_1, vma);

	return err;
}
static int rx_mem_ch2_mmap(struct file * filp, struct kobject * kobj, struct bin_attribute *attr,  struct vm_area_struct *vma)
{
	int err;

	DUMP_MMAP_INFO(TX_CHAN_1);

    err = yadma_slot_based_channel_mmap(RX_CHAN_2, vma);

	return err;
}


/* Keep coherent with yadmaFileNames */
static struct bin_attribute  bin_attr_TxMem = {
     .attr = {
         .name = "TxMemCh1",
//         .owner = THIS_MODULE,
         .mode = S_IRUGO | S_IWUGO,
     },
     .size = YADMA_MEM_SIZE,
//     .read = yadma_read_sysfs_tx1,
//     .write = yadma_write_sysfs_tx1,
     .mmap = tx_mem_mmap,
};

static struct bin_attribute  bin_attr_RxMem = {
     .attr = {
         .name = "RxMemCh1",
//         .owner = THIS_MODULE,
         .mode = S_IRUGO | S_IWUGO,
     },
     .size = YADMA_MEM_SIZE,
//     .read = yadma_read_sysfs_tx1,
//     .write = yadma_write_sysfs_tx1,
     .mmap = rx_mem_mmap,
};

static struct bin_attribute  bin_attr_TxMemCh1 = {
     .attr = {
         .name = "TxMemCh1",
//         .owner = THIS_MODULE,
         .mode = S_IRUGO | S_IWUGO,
     },
     .size = YADMA_MEM_SIZE,
//     .read = yadma_read_sysfs_tx1,
//     .write = yadma_write_sysfs_tx1,
     .mmap = tx_mem_ch1_mmap,
};

static struct bin_attribute  bin_attr_TxMemCh2 = {
     .attr = {
         .name = "TxMemCh2",
//         .owner = THIS_MODULE,
         .mode = S_IRUGO | S_IWUGO,
     },
     .size = YADMA_MEM_SIZE,
//     .read = yadma_read_sysfs_tx2,
//     .write = yadma_write_sysfs_tx2,
     .mmap = tx_mem_ch2_mmap,
};

static struct bin_attribute  bin_attr_RxMemCh1 = {
     .attr = {
         .name = "RxMemCh1",
//         .owner = THIS_MODULE,
         .mode = S_IRUGO | S_IWUGO,
     },
     .size = YADMA_MEM_SIZE,
 //    .read = yadma_read_sysfs_rx1,
 //    .write = yadma_write_sysfs_rx1,
     .mmap = rx_mem_ch1_mmap,
};

static struct bin_attribute  bin_attr_RxMemCh2 = {
     .attr = {
         .name = "RxMemCh2",
//         .owner = THIS_MODULE,
         .mode = S_IRUGO | S_IWUGO,
     },
     .size = YADMA_MEM_SIZE,
//     .read = yadma_read_sysfs_rx2,
//     .write = yadma_write_sysfs_rx2,
     .mmap = rx_mem_ch2_mmap,
};

static struct bin_attribute *bin_attrs_group[] = {
#if (CHANNEL_TYPE == BLOCK_BASED_CHANNEL)
#if (MAX_CHANS == 2)
        &bin_attr_TxMem,
        &bin_attr_RxMem,
#endif
#endif

#if (CHANNEL_TYPE == SLOT_BASED_CHANNEL)
#if (MAX_CHANS >= 2)
		&bin_attr_TxMemCh1,
		&bin_attr_TxMemCh2,
#if (MAX_CHANS == 4)
		&bin_attr_RxMemCh1,
		&bin_attr_RxMemCh2,
#endif
#endif
#endif
};

static struct attribute_group yadma_dev_attr_grp = {
		.attrs = dev_attrs,
		.name = DRIVER_NAME,

};


void register_sysfs_files(struct kobject *kobj)
{
	int i, ret;

	/* Create control files */
	ret = sysfs_create_group(kobj, &yadma_dev_attr_grp);
	if (ret) {
		printk(KERN_ERR, "Failed to create sysfs device attributes\n");
	} else {
		printk(KERN_INFO "Attribute group %s are created.\n",yadma_dev_attr_grp.name);
	}

	/* Create buffer files */
	for(i = 0; i < MAX_CHANS; i++) {
		ret = sysfs_create_bin_file(kobj, bin_attrs_group[i]);
		if (ret) {
			printk(KERN_ERR "Failed to create sys file/n");
		} else {
			printk(KERN_INFO "Bin Attribute %s are created.\n",bin_attrs_group[i]->attr.name);
		}
	}
}

void unregister_sysfs_files(struct kobject *kobj)
{
	int i, ret;

    /* remove the registered sysfs attributes */
    sysfs_remove_group(kobj, &yadma_dev_attr_grp);

	printk(KERN_INFO "Attribute group %s are removed.\n",yadma_dev_attr_grp.name);

	/* remove buffer files */
	for(i = 0; i < MAX_CHANS; i++) {
		sysfs_remove_bin_file(kobj, bin_attrs_group[i]);
		printk(KERN_INFO "Remove sys bin_attribute file %s.\n", bin_attrs_group[i]->attr.name);
	}
}
