/*****************************************************************************/
/**
 *
 * @file yadma_proc.c
 *
 * This is the file which implements procfs read/write operations.
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
#include <linux/kernel.h>

#include "yadma.h"
#include "yadma_reg.h"
#include "yadma_proc.h"
#include "yadma_knl.h"
#include "adi_common.h"
#include "ad9361.h"


//#define USING_ADI_PORTING

/************************** Constant Definitions *****************************/

/* functions that using procfs */

/*
1.char *page :  The buffer where the data is to be inserted,if you decide to use it .
                       我的理解是kernel分配的1个小于一个page大小的buffer。buffer的具体大小再count参数中指出。
2.char **start: A pointer to a pointer to characters.This is useful if you don't want to use the buffer allocated by the kernel.
                       如果不使用内核分配的buffer，使用自己的buffer，则需要把buffer指针的地址传出。
3.off_T off:    The current position in the file.    app读取当前proc的offset。
4.int count:    The size of the buffer in the first argument.
5.int *eof :    Write a "1" here to indicate EOF
6.void *data:
Example code:
*/
#if 0
static int proc_read_foo(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	/* TODO: sprintf to page */
	logMsg("device_attribute %s.\n", buf);
	return count;
}


static int proc_write_foo(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
	/* TODO: copy buffer (length is count) to kernel variables */
	logMsg("proc write %s.\n", buf);
	return count;
}

#endif

#define DUMP_PROC_READ \
	log_verbose(KERN_INFO "%s read filp=0x%p, start = 0x%p, *start = %p, count = %d, data = %s @ 0x%p\n", __FUNCTION__, page, start, *start, count, (char*)start, data);

#define DUMP_PROC_WRITE \
	log_verbose(KERN_INFO "%s filp=0x%p, buffer = 0x%p, count = %ld\n", __FUNCTION__, file, buffer, count);

#define MODULE_IN_USE_LOCK mutex_lock(&privDataLock)
#define MODULE_UNLOCK mutex_unlock(&privDataLock);

static int ProcReadTxRxMem(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
	return count;
}

static int ProcReadTxMemCh1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
	return count;
}

static int ProcReadTxMemCh2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
	return count;
}

static int ProcReadRxMemCh1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
	return count;
}

static int ProcReadRxMemCh2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
	return count;
}

static int ProcReadSysInfo(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
	MODULE_IN_USE_LOCK;
	MODULE_UNLOCK;
	int len;
	len = sprintf(page, "System Timing = %ld\n", yadmaPrivData->SysTiming);
	return len;
}

static int ProcReadTxFreqch1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
	MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->TxFreqCh1);
	MODULE_UNLOCK;
	return len;
}

static int ProcReadRxFreqch1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
    MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->RxFreqCh1);
	MODULE_UNLOCK;
	return len;
}

static int ProcReadTxFreqch2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
    MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->TxFreqCh2);
	MODULE_UNLOCK;
	return len;
}

static int ProcReadRxFreqch2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
    MODULE_IN_USE_LOCK;
 	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->RxFreqCh2);
	MODULE_UNLOCK;
	return len;
}


static int ProcReadTxGainch1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
    MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->TxGainCh1);
	MODULE_UNLOCK;
	return len;
}

static int ProcReadRxGainch1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
    MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->RxGainCh1);
	MODULE_UNLOCK;
	return len;
}

static int ProcReadTxGainch2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
    MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->TxGainCh2);
	MODULE_UNLOCK;
	return len;
}

static int ProcReadRxGainch2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
    MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->RxGainCh2);
	MODULE_UNLOCK;
	return len;
}


static int ProcReadRSSIch1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
    MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->RSSICh1);
	MODULE_UNLOCK;
	return len;
}

static int ProcReadRSSIch2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
    MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->RSSICh2);
	MODULE_UNLOCK;
	return len;
}

static int ProcReadRFStatech1(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
    MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->RFStateCh1);
	MODULE_UNLOCK;
	return len;
}

static int ProcReadRFStatech2(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
    MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->RFStateCh1);
	MODULE_UNLOCK;
	return len;
}


static int ProcReadSysTiming(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
	MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->RFStateCh2);
	MODULE_UNLOCK;
	return len;
}

static int ProcReadFPGAReset(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
    MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->FPGAReset);
	MODULE_UNLOCK;
	return len;
}

static int ProcReadIrqInterval(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    DUMP_PROC_READ;
    MODULE_IN_USE_LOCK;
	int len;
	len = sprintf(page, "%ld\n", yadmaPrivData->IrqInterval);
	MODULE_UNLOCK;
	return len;
}


static void_func_ptr yadmaProcReadFuncs[YADMA_FILE_COUNT] =
{
#if (MAX_CHANS == 1)
    (void_func_ptr)&ProcReadTxRxMem,
#endif
#if (MAX_CHANS >= 2 )
    (void_func_ptr)&ProcReadTxMemCh1,
    (void_func_ptr)&ProcReadTxMemCh2,
#if (MAX_CHANS == 4)
    (void_func_ptr)&ProcReadRxMemCh1,
    (void_func_ptr)&ProcReadRxMemCh2,
#endif
#endif
    (void_func_ptr)ProcReadSysInfo,
    (void_func_ptr)&ProcReadTxFreqch1,
    (void_func_ptr)&ProcReadRxFreqch1,
    (void_func_ptr)&ProcReadTxFreqch2,
    (void_func_ptr)&ProcReadRxFreqch2,

    (void_func_ptr)&ProcReadTxGainch1,
    (void_func_ptr)&ProcReadRxGainch1,
    (void_func_ptr)&ProcReadTxGainch2,
    (void_func_ptr)&ProcReadRxGainch2,

    (void_func_ptr)&ProcReadRSSIch1,
    (void_func_ptr)&ProcReadRSSIch2,
    (void_func_ptr)&ProcReadRFStatech1,
    (void_func_ptr)&ProcReadRFStatech2,

    (void_func_ptr)&ProcReadSysTiming,
    (void_func_ptr)&ProcReadFPGAReset,
    (void_func_ptr)&ProcReadIrqInterval,

};

static int ProcWriteTxRxMem(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
	return count;
}

static int ProcWriteTxMemCh1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
	return count;
}

static int ProcWriteTxMemCh2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
	return count;
}

static int ProcWriteRxMemCh1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
	return count;
}

static int ProcWriteRxMemCh2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
	return count;
}

static int ProcWriteSysInfo(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
	return count;
}

static int ProcWriteTxFreqch1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
    MODULE_IN_USE_LOCK;
    unsigned long freq, vco;
    freq = simple_strtoul(buffer, NULL, 10);
#ifdef USING_ADI_PORTING
    vco = set_rfpll_rate(TX_RFPLL, freq, 61440000);
    printk("freq = %ud, vco = %ud\n", freq, vco);
    yadmaPrivData->TxFreqCh1 = freq;
    if(vco > 0)
		config_rfpll_vco(ADI_FDD_MODE, ADI_TX_CH, vco, 61440000);
#else
    // REVISIT @ 2014/5/8
    // send the parameter to the private parameter 
    yadmaPrivData->TxFreqCh1 = freq;
    struct paraRlt res;
    paraCal(DEFAULT_DUPLEX_MODE, yadmaPrivData->RxFreqCh1, yadmaPrivData->TxFreqCh1, DEFAULT_REF_CLK, ADI_VCO_LOW_FREQ, ADI_VCO_HIGH_FREQ, &res);
    ad9362_tx_freq(&res);
#endif
	MODULE_UNLOCK;
	return count;
}

static int ProcWriteRxFreqch1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
    MODULE_IN_USE_LOCK;
    unsigned long freq, vco;
    freq = simple_strtoul(buffer, NULL, 10);
#ifdef USING_ADI_PORTING
    vco = set_rfpll_rate(RX_RFPLL, freq, 61440000);
    printk("freq = %ud, vco = %ud\n", freq, vco);
        // REVISIT @ 2014/5/8
    // send the parameter to the private parameter 
    yadmaPrivData->RxFreqCh1  = freq;
    
    
    if(vco > 0);
		config_rfpll_vco(ADI_FDD_MODE, ADI_RX_CH, 2100000000, 61440000);
#else
    // REVISIT @ 2014/5/8
    // send the parameter to the private parameter 
    yadmaPrivData->RxFreqCh1 = freq;
    
    struct paraRlt res;
    paraCal(DEFAULT_DUPLEX_MODE, yadmaPrivData->RxFreqCh1, yadmaPrivData->TxFreqCh1, DEFAULT_REF_CLK, ADI_VCO_LOW_FREQ, ADI_VCO_HIGH_FREQ, &res);
    ad9362_rx_freq(&res);
#endif
	MODULE_UNLOCK;
	return count;
}

static int ProcWriteTxFreqch2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
    MODULE_IN_USE_LOCK;
    unsigned long freq, vco;
    freq = simple_strtoul(buffer, NULL, 10);
#ifdef USING_ADI_PORTING
    vco = set_rfpll_rate(TX_RFPLL, freq, 61440000);
    printk("freq = %ud, vco = %ud\n", freq, vco);
    yadmaPrivData->TxFreqCh2 = freq;
    if(vco > 0)
		config_rfpll_vco(ADI_FDD_MODE, ADI_TX_CH, vco, 61440000);
#else

    // REVISIT @ 2014/5/8
    // send the parameter to the private parameter 
    yadmaPrivData->TxFreqCh2 = freq;

    struct paraRlt res;
    paraCal(DEFAULT_DUPLEX_MODE, yadmaPrivData->RxFreqCh2, yadmaPrivData->TxFreqCh2, DEFAULT_REF_CLK, ADI_VCO_LOW_FREQ, ADI_VCO_HIGH_FREQ, &res);
    ad9362_tx_freq(&res);
#endif
	MODULE_UNLOCK;
	return count;
}

static int ProcWriteRxFreqch2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
    MODULE_IN_USE_LOCK;
    unsigned long freq, vco;
    freq = simple_strtoul(buffer, NULL, 10);
#ifdef USING_ADI_PORTING
    vco = set_rfpll_rate(RX_RFPLL, freq, 61440000);
    printk("freq = %ud, vco = %ud\n", freq, vco);
    yadmaPrivData->RxFreqCh2  = freq;
    if(vco > 0);
		config_rfpll_vco(ADI_FDD_MODE, ADI_RX_CH, 2100000000, 61440000);
#else

    // REVISIT @ 2014/5/8
    // send the parameter to the private parameter 
    yadmaPrivData->RxFreqCh2  = freq;
    struct paraRlt res;
    paraCal(DEFAULT_DUPLEX_MODE, yadmaPrivData->RxFreqCh2, yadmaPrivData->TxFreqCh2, DEFAULT_REF_CLK, ADI_VCO_LOW_FREQ, ADI_VCO_HIGH_FREQ, &res);
    ad9362_rx_freq(&res);
#endif
	MODULE_UNLOCK;
	return count;
}


static int ProcWriteTxGainch1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
    MODULE_IN_USE_LOCK;
    unsigned long gain;

    gain = simple_strtoul(buffer, NULL, 10);
    ad9362_tx_att(gain, yadmaPrivData->TxGainCh2);
    yadmaPrivData->TxGainCh1 = gain;
    printk("Set Tx1 gain: %ud\n", gain);
	MODULE_UNLOCK;
	return count;
}

static int ProcWriteRxGainch1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
    MODULE_IN_USE_LOCK;
    unsigned long gain;

    gain = simple_strtoul(buffer, NULL, 10);
    ad9362_rx_gain(gain, yadmaPrivData->RxGainCh2);
    yadmaPrivData->TxGainCh1 = gain;
    printk("Set Rx1 gain: %ud\n", gain);
    MODULE_UNLOCK;
	return count;
}

static int ProcWriteTxGainch2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
    MODULE_IN_USE_LOCK;
    unsigned long gain;
    gain = simple_strtoul(buffer, NULL, 10);
    ad9362_tx_att(yadmaPrivData->TxGainCh1, gain);
    yadmaPrivData->TxGainCh2 = gain;
    printk("Set Tx2 gain: %ud\n", gain);
    MODULE_UNLOCK;
	return count;
}

static int ProcWriteRxGainch2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
    MODULE_IN_USE_LOCK;
    unsigned long gain;

    gain = simple_strtoul(buffer, NULL, 10);
    ad9362_rx_gain(yadmaPrivData->RxGainCh1, gain);
    yadmaPrivData->TxGainCh2 = gain;
    printk("Set Rx2 gain: %ud\n", gain);
    MODULE_UNLOCK;
	return count;
}


static int ProcWriteRSSIch1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
	return count;
}

static int ProcWriteRSSIch2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
	return count;
}

static int ProcWriteRFStatech1(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
    MODULE_IN_USE_LOCK;
    AD9362_Config();
    printk("RF STATE Init OK \n");
    MODULE_UNLOCK;
	return count;
}

static int ProcWriteRFStatech2(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
    MODULE_IN_USE_LOCK;
    unsigned long freq;
    freq = simple_strtoul(buffer, NULL, 10);
	/* Set nco frequency */
	yadma_write_ctrl_bar(0xD, freq);
	/* Set nco gain */
	yadma_write_ctrl_bar(0xE, 0x7FFF);
	MODULE_UNLOCK;
	return count;
}


static int ProcWriteSysTiming(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
	return count;
}

static int ProcWriteFPGAReset(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
    MODULE_IN_USE_LOCK;
	yadma_write_ctrl_bar(REG_DSP_SOFT_RESET, 1);
	yadma_write_ctrl_bar(REG_DSP_SOFT_RESET, 0);
	MODULE_UNLOCK;
	return count;
}

static int ProcWriteIrqInterval(struct file *file,  const char *buffer,  unsigned long count, void *data)
{
    DUMP_PROC_WRITE;
	return count;
}



static void_func_ptr yadmaProcWriteFuncs[YADMA_FILE_COUNT] =
{
#if (MAX_CHANS == 1)
    (void_func_ptr)&ProcWriteTxRxMem,
#endif
#if (MAX_CHANS >= 2 )
	(void_func_ptr)&ProcWriteTxMemCh1,
    (void_func_ptr)&ProcWriteRxMemCh1,
#if (MAX_CHANS == 4)
	(void_func_ptr)&ProcWriteTxMemCh2,
	(void_func_ptr)&ProcWriteRxMemCh2,
#endif
#endif
    (void_func_ptr)&ProcWriteSysInfo,
	(void_func_ptr)&ProcWriteTxFreqch1,
	(void_func_ptr)&ProcWriteRxFreqch1,
	(void_func_ptr)&ProcWriteTxFreqch2,
	(void_func_ptr)&ProcWriteRxFreqch2,

	(void_func_ptr)&ProcWriteTxGainch1,
	(void_func_ptr)&ProcWriteRxGainch1,
	(void_func_ptr)&ProcWriteTxGainch2,
	(void_func_ptr)&ProcWriteRxGainch2,

	(void_func_ptr)&ProcWriteRSSIch1,
	(void_func_ptr)&ProcWriteRSSIch2,
	(void_func_ptr)&ProcWriteRFStatech1,
	(void_func_ptr)&ProcWriteRFStatech2,

	(void_func_ptr)&ProcWriteSysTiming,
	(void_func_ptr)&ProcWriteFPGAReset,
	(void_func_ptr)&ProcWriteIrqInterval,

};

static int tx_buffer_mmap(struct file *filp, struct vm_area_struct * vma)
{
	int err;


	DUMP_MMAP_INFO(TX_CHAN);
	MODULE_IN_USE_LOCK;
    err = yadma_block_based_channel_mmap(TX_CHAN, vma);
	MODULE_UNLOCK;
	return err;
}

static int rx_buffer_mmap(struct file *filp, struct vm_area_struct * vma)
{
	int err;


	DUMP_MMAP_INFO(RX_CHAN);
	MODULE_IN_USE_LOCK;
    err = yadma_block_based_channel_mmap(RX_CHAN, vma);
	MODULE_UNLOCK;
	return err;
}

static int tx_ch1_buffer_mmap(struct file *filp, struct vm_area_struct * vma)
{
	int err;
	MODULE_IN_USE_LOCK;
	DUMP_MMAP_INFO(TX_CHAN_1);

    err = yadma_slot_based_channel_mmap(TX_CHAN_1, vma);
	MODULE_UNLOCK;
	return err;
}

static int tx_ch2_buffer_mmap(struct file *filp, struct vm_area_struct * vma)
{
	int err;
	MODULE_IN_USE_LOCK;
	DUMP_MMAP_INFO(TX_CHAN_2);

    err = yadma_slot_based_channel_mmap(TX_CHAN_2, vma);
	MODULE_UNLOCK;
	return err;
}

static int rx_ch1_buffer_mmap(struct file *filp, struct vm_area_struct * vma)
{
	int err;
	MODULE_IN_USE_LOCK;
	DUMP_MMAP_INFO(RX_CHAN_1);

    err = yadma_slot_based_channel_mmap(RX_CHAN_1, vma);
	MODULE_UNLOCK;
	return err;
}


static int rx_ch2_buffer_mmap(struct file *filp, struct vm_area_struct * vma)
{
	int err;

	DUMP_MMAP_INFO(RX_CHAN_2);
	MODULE_IN_USE_LOCK;
    err = yadma_slot_based_channel_mmap(RX_CHAN_2, vma);
	MODULE_UNLOCK;
	return err;
}

const struct file_operations yadmaBufFileOp[MAX_CHANS] = {
#if (CHANNEL_TYPE == BLOCK_BASED_CHANNEL)
#if (MAX_CHANS == 2)
    { .mmap = tx_buffer_mmap, },
    { .mmap = rx_buffer_mmap, },
#endif
#endif

#if (CHANNEL_TYPE == SLOT_BASED_CHANNEL)
#if (MAX_CHANS >= 2 )
    { .mmap = tx_ch1_buffer_mmap, },
    { .mmap = rx_ch1_buffer_mmap, },
#if (MAX_CHANS == 4)
    { .mmap = tx_ch2_buffer_mmap, },
    { .mmap = rx_ch2_buffer_mmap, }
#endif
#endif
#endif
};

static struct proc_dir_entry *yadma_proc_dir = NULL;

void register_proc_files()
{
	int i;


	yadma_proc_dir = proc_mkdir(DRIVER_NAME, NULL );

	/* Create control files */
	for(i = MAX_CHANS; i < MAX_FILES + MAX_CHANS; i++) {
		struct proc_dir_entry *file = create_proc_entry(yadmaFileNames[i], YADMA_PROC_ACESS_RIGHTS, yadma_proc_dir);

		if ( file == NULL ) {
			/* remove all enties under /proc/yadma */
			remove_proc_entry(YADMA_PROC_DIR, NULL );
			printk(KERN_ALERT "Error: Could not initialize %s/%s\n",
				YADMA_PROC_DIR,
			    yadmaFileNames[i]);
			return;
		} else {
			file->read_proc = (read_proc_t *)yadmaProcReadFuncs[i];
			file->write_proc = (write_proc_t *)yadmaProcWriteFuncs[i];
            log_verbose(KERN_INFO "Create procfs %s/%s\n", YADMA_PROC_DIR, yadmaFileNames[i]);
		}
	}

	/* Create buffer files */
	for(i = 0; i < MAX_CHANS; i++) {

		struct proc_dir_entry *file = proc_create_data(yadmaFileNames[i], YADMA_PROC_ACESS_RIGHTS, yadma_proc_dir, &yadmaBufFileOp[i], NULL);

		if ( file == NULL ) {
			/* remove all enties under /proc/yadma */
			remove_proc_entry(YADMA_PROC_DIR, NULL );
			printk(KERN_ALERT "Error: Could not initialize %s/%s\n",
				YADMA_PROC_DIR,
			    yadmaFileNames[i]);
			return;
		} else {
           log_verbose(KERN_INFO "Create procfs %s/%s\n", YADMA_PROC_DIR, yadmaFileNames[i]);
        }
	}
}

void unregister_proc_files(void)
{
	int i;
	for( i=0;i<YADMA_FILE_COUNT;i++ ) {
		remove_proc_entry(yadmaFileNames[i], yadma_proc_dir);
	}

	remove_proc_entry(DRIVER_NAME, NULL);
	printk(KERN_INFO "%s are removed.\n",YADMA_PROC_DIR);

}
