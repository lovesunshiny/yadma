/*****************************************************************************/
/**
 *
 * @file yadma.h
 *
 * This is header file for yadma kernel space code.
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


#ifndef YADMA_KNL_H
#define YADMA_KNL_H
#include <linux/semaphore.h>
typedef struct {
	const char* name;
	int bar_type;
	int bar_size;
} BarEntry;

static const BarEntry bar_table[MAX_BARS] =
{
	{"DMA Receive BAR", BAR_TYPE_MEM, 64*1024*1024}, /* BAR 0 */
	{"DMA Send BAR", BAR_TYPE_MEM, 64*1024} /* BAR 1 */
};


extern u32 DriverState;

typedef struct {
  u32  chnl_state;        /**< Flag to indicate state of the channel */
  spinlock_t chnl_lock;

#ifdef CHANNEL_STRUCT_FOR_CPIT
  dma_addr_t phys_addr_array[MAX_BD_COUNTS];    /**< Physical address of buffer, IO or RAM */
  void* virt_addr_array[MAX_BD_COUNTS];           /**< Virtual address of buffer */
#endif

  dma_addr_t phys_addr;    /**< Physical address of buffer, IO or RAM */
  void* virt_addr;           /**< Virtual address of buffer */

  u32 	total_length;        /**< Total size of ring in bytes */

  u32	block_count;
  u32	block_size;
  u32	slot_count;
  u32 	slot_size;           /**< Slot size of the buffer */

  u32  cur_block;  	      /**< Current Buffer Descriptor number */
  u32  cur_slot;		  /**< Current slot number i.e Userspace read/write position */
  u32	u_block;		/**< Last block finished by user space */
  u32	u_slot;			/**< Last slot finished by user space */
} DmaChannel;


/** @name Private per-device data
 * The PCI device entry points to this as driver-private data. In some
 * cases, pointer back to PCI device entry is also required.
 * @{
 */
typedef struct privData {
    struct pci_dev * pdev;             /**< PCI device entry */
	u32	 drv_state;
	spinlock_t drv_lock;

    /** BAR information discovered on probe. BAR0 is understood by this driver.
     * Other BARs will be used as app. drivers register with this driver.
     */
    u32 bar_high_addr;				/** < PCI address hight 32bits */
    u32 bar_mask;                      /**< Bitmask for BAR information */

	DmaChannel *dma_chans[MAX_CHANS];

	struct cdev *yadma_cdev;	  			/* Char device structure		*/
	dev_t yadma_dev;

	void* TxMemCh1;
	void* TxMemCh2;
	void* RxMemCh1;
	void* RxMemCh2;

	u32 TxFreqCh1;
	u32 RxFreqCh1;
	u32 TxFreqCh2;
	u32 RxFreqCh2;

	u32 TxGainCh1;
	u32 RxGainCh1;
	u32 TxGainCh2;
	u32 RxGainCh2;

	u32 RSSICh1;
	u32 RSSICh2;
	u32 RFStateCh1;
	u32 RFStateCh2;

	u32 SysTiming;
	u32 FPGAReset;
	u32 IrqInterval;

    struct {
		int	index;					   /** index in the bar table */
        u32 bar_len;         /**< Length of device memory */
        u64 bar_phys_addr;   /**< Base address of device memory */
        void __iomem *bar_virt_addr;   /**< VA - mapped address */
    } bar_info[MAX_BARS];

} PrivateDataStru;

/*@}*/
void yadma_write_ctrl_bar(int offset, u32 value);

extern PrivateDataStru* yadmaPrivData;
extern struct semaphore privDataLock;

/* mmap one time for small memory allocation channels */
int yadma_slot_based_channel_mmap(int ch, struct vm_area_struct *vma);

/* mmap multiple times for big memory allocation channels */
int yadma_block_based_channel_mmap(int ch, struct vm_area_struct *vma);

#ifdef DEBUG_YADMA
#define log_verbose(args...)    printk(args)
#ifdef DEBUG_MMAP_INFO
#define DUMP_MMAP_INFO(ch) \
    log_verbose(KERN_INFO "%s: channel=%d, vm_start=%#x, vm_end=%#x, offset=%#x, proto=%x\n", \
    __FUNCTION__, ch, vma->vm_start, vma->vm_end,  vma->vm_pgoff, vma->vm_page_prot);
#else
#define DUMP_MMAP_INFO(ch)
#endif
#else
#define log_verbose(x...)
#endif

#endif
