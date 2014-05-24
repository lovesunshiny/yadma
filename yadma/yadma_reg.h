/*****************************************************************************/
/**
*
* @file yadma_reg.h
*
* This header file contains identifiers and register-level driver functions
* and macros that can be used to access YA Direct Memory Access device.
*
* For more information about the operation of this device, see the hardware
* specification documentation.
*
* MODIFICATION HISTORY:
*
* Ver   Date     Changes
* ----- -------- -------------------------------------------------------
* 1.0   5/15/12  First version
*
******************************************************************************/

#ifndef YADMA_REG_H   /* prevent circular inclusions */
#define YADMA_REG_H   /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#define HANDLE_MSI_ISR
#define CHANNEL_STRUCT_FOR_CPIT
/************************** Constant Definitions *****************************/

/** @name Device register offset definitions. Register access is 32-bit.
 *  @{
 */

/* Common FPGA registers */
#define REG_VERSION_INFO        0x0000      /**< FPGA Version */
#define REG_SET_FRAME_NUM       0x0001      /**< System timing by set frame number */
#define REG_ADJUST_TIMING       0x0002      /**< For ajusting system timing */
#define REG_ROUTE_AND_CTRL      0x0003      /**< PCIE route and control register */

#define REG_RF_GAIN             0x0004      /**< Attenuation setting for tx/rx channel 0/1 */
#define REG_LED_AND_RESET       0x0005      /**< Led control; adc/agc/rf enable and reset */
#define REG_INT_MASK_AND_SLOTS  0x0006      /**< Interrupt mask and interval: n+1 slots */
#define REG_FRAME_AND_SLOT_NUM  0x0007      /**< Frame and Slot number when interrupt occurs */
#define REG_DSP_SOFT_RESET      0x0008		/**< Write 1 and then write 0 to reset DSP/DMA */

#define REG_BD_COUNT            0x0009      /**< Block descriptor's count */
#define REG_CUR_BD              0x000A      /**< Current block number the FPGA is processing;
                                                User space can use the previous one */
#define REG_TX_BD_COUNT			0x000B		/**< Block count for TX channel */

#define REG_SPI_R_END_ADDR      0x0010      /**< SPI end address of refresh operation */
#define REG_SPI_R_LENGTH        0X0011      /**< The length of the spi read/refresh operation */

#define REG_SPI_R_CONTROL       0x0012      /**< SPI read control: reset or refresh */

#define BIT_SPI_REFRESH        (1 << 0)
#define BIT_SPI_RESET          (1 << 16)

#define REG_SPI_R_STATUS        0x0013      /**< SPI read status */
#define BIT_SPI_R_BUSY          (1 << 0)
#define BIT_SPI_W_BUSY          (1 << 8)
#define BIT_SPI_OVERFLOW        (1 << 16)

#define REG_PCIE_WAIT_CYCLE     0x001c       /**< pcit transmit wait clock cycle */
#define REG_AFC_DAC_VALUE       0x001F      /**< The read/write interface for AFC register, which adjust 10MHz OCXO */


#define REG_ADI_START_OFFSET    0x200       /**< 0x200 -0x5FF is mapped to AD9361 registers directly */
#define REG_ADI_END_OFFSET      0x5FF

#define REG_SMAPLE_RATE_IF       0x1200      /**< Signal samping reate and IF path selection */
#define REG_START_CELL_SEARCH    0x1203      /**< Start cell search/ system sync process */
#define REG_CHANNEL_SWAP         0x1204      /**< Start cell search/ system sync process */
#define REG_NCO_CONFIG           0x1205      /**< Config the nco working frequency point */
#define REG_UPLINK_FREQ_OFFSET   0x1206      /**< Uplink frequency offset */
#define REG_DOWNLINK_FREQ_OFFSET 0x1207     /**< Downlink frequency offset, read only */
#define REG_AFC_CFG              0X1208      /**< AFC config Mode ctrl*/
#define REG_PSC_CORR_LEVEL       0x1209      /**< The CellSearch level */

#define REG_SYNC_STATUS          0x1210      /**< The CellSearch sync status */
#define REG_FREQ_EST             0x1211      /**< The FPGA estimate frequency */
#define REG_TIMING_EST           0x1212      /**< The FPGA estimate timing */
#define REG_AGC_GAIN_READ        0x1213      /**< The CellSearch level */


// REVISIT @ 2014/4/26
#define REG_PLL1_REF_SEL        0xA1C
#define REG_PLL1_UPDATA         0xC34



// REVISIT @ 2014/4/25
// remove the n-1 to n. because in current FPGA code read BD. the RX buffer pointer
// is the current availiable buffer. previous FPGA code, the read BD -1 is the availiable
// receive buffer
//#define PREV_BD(n, max)         ((n-1)<0? (max) : (n-1))
#define PREV_BD(n, max)         ((n-1)<0? (n) : (n))


#define REG_TX0_BUF_ADDR        0x0050      /**< 32 bit pcie bus address for TX DMA channel 0  */
#define REG_TX1_BUF_ADDR        0x0051      /**< 32 bit pcie bus address for TX DMA channel 1  */
#define REG_RX0_BUF_ADDR        0x0052      /**< 32 bit pcie bus address for RX DMA channel 0  */
#define REG_RX1_BUF_ADDR        0x0053      /**< 32 bit pcie bus address for RX DMA channel 1  */


#define MAX_BD_COUNTS           32			/**< register placeholder size */

/**< block based channel: RX */
#define CUR_RX_BD_COUNT			32			/**< RX block used in real */
#define REG_RX_BD0_POINTER         0x1400
#define REG_RX_BD1_POINTER         0x1401
#define REG_RX_BD2_POINTER         0x1402
#define REG_RX_BD3_POINTER         0x1403
#define REG_RX_BD4_POINTER         0x1404
#define REG_RX_BD5_POINTER         0x1405
#define REG_RX_BD6_POINTER         0x1406
#define REG_RX_BD7_POINTER         0x1407
//          :
//          :
#define REG_RX_BD31_POINTER        0x1431

/**< block based channel: TX */
#define CUR_TX_BD_COUNT			4			/**< TX block used in real */
#define REG_TX_BD0_POINTER		0x1480
#define REG_TX_BD1_POINTER		0x1481
#define REG_TX_BD2_POINTER		0x1482
#define REG_TX_BD3_POINTER		0x1483

/* Register masks. The following constants define bit locations of various
 * control bits in the registers. For further information on the meaning of
 * the various bit masks, refer to the hardware spec.
 *
 * Masks have been written assuming HW bits 0-31 correspond to SW bits 0-31
 */
/** @name Bitmasks of REG_VERSION_INFO register.
 * @{
 */
#define BIT_MASK_YEAR               0xFF000000
#define BIT_MASK_MONTH              0x00FF0000
#define BIT_MASK_DAY                0x0000FF00
#define BIT_MASK_AUTHOR             0x000000F0
#define BIT_MASK_VERSION            0x0000000F

 /** @name Bitmasks of REG_SET_FRAME_NUM register.
 * @{ Change the system frame number when next frame.
 */
#define BIT_MASK_FRAME_NUMBER_SET   0x7FFFF

 /** @name Bitmasks of REG_ADJUST_TIMING register.
 * @{ Deprecated
 */
#define BIT_MASK_ADJUST_SIGN
#define BIT_MASK_ADJUST_VALUE

 /** @name Bitmasks of REG_ROUTE_AND_CTRL register.
 * @{
 */
#define BIT_MASK_RX0_EN
#define BIT_MASK_RX1_EN
#define BIT_MASK_TX0_EN
#define BIT_MASK_TX1_EN
#define BIT_MASK_ROUTE
#define BIT_MASK_LS_RF
#define BIT_MASK_SW0
#define BIT_MASK_SW1
#define BIT_MASK_TX_AND_RX

#define ROUTE_CTL_PCIE_LOOPBACK_MODE      0x11
#define ROUTE_CTL_NORMAL_RF_MODE          0x211
#define ROUTE_CTL_NORMAL_BB_MODE          0x10211



 /** @name Bitmasks of REG_RF_GAIN register.
 * @{
 */
#define BIT_MASK_TX0_GAIN
#define BIT_MASK_TX1_GAIN
#define BIT_MASK_RX0_GAIN
#define BIT_MASK_RX1_GAIN

 /** @name Bitmasks of REG_LED_AND_RESET register.
 * @{
 */
#define BIT_MASK_LED0
#define BIT_MASK_LED1
#define BIT_MASK_DAC_RESET
#define BIT_MASK_RF_RESET
#define BIT_MASK_AGC_EN
#define BIT_MASK_RF_EN

#define LED_RESET_DEFAULT_SETTING   0xFFFFFFFF

 /** @name Bitmasks of REG_INT_MASK_AND_MULTI register.
 * @{
 */
#define BIT_MASK_INT_MASK           0xFFFF
#define BIT_MASK_INT_SLOTS          0x3F0000

#define FRAME_INT_ENABLE            0x1
#define SLOT_INT_ENABLE             0x2
#define MULTI_SLOT_INT_ENABLE       0x4

 /** @name Bitmasks of REG_FRAME_AND_SLOT_NUM register.
 * @{
 */
#define BIT_MASK_CUR_FRAME          0x7FFFF00
#define BIT_MASK_CUR_SLOT           0x3F
#define MASK_LOW_WORD         0x0000FFFF
#define MASK_HIGH_WORD        0xFFFF0000

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

#ifdef __KERNEL__
/* Basic DMA read/write functions - are 32-bit */
#define YADMA_REG_READ32  ioread32
#define YADMA_REG_WRITE32 iowrite32

/*****************************************************************************/
/**
*
* Read the given register.
*
* @param    BaseAddress is the base address of the device
* @param    RegOffset is the register offset to be read
*
* @return   The 32-bit value of the register
*
* @note
* C-style signature:
*    u32 yadmaReadReg(u32 BaseAddress, u32 RegOffset)
*
******************************************************************************/
#ifdef DEBUG_YADMA_REG
static inline u32 yadmaReadReg(BaseAddress, RegOffset)
{
	printk("Read base@ 0x%p offset@ 0x%p.\n", BaseAddress, RegOffset);
	return 0;
}
#else
#define yadmaReadReg(BaseAddress, RegOffset)             \
    YADMA_REG_READ32((BaseAddress) + (RegOffset*4))
#endif

/*****************************************************************************/
/**
*
* Write the given register.
*
* @param    BaseAddress is the base address of the device
* @param    RegOffset is the register offset to be written
* @param    Data is the 32-bit value to write to the register
*
* @return   None.
*
* @note
* C-style signature:
*    void yadmaWriteReg(u32 BaseAddress, u32 RegOffset, u32 Data)
*
******************************************************************************/
#ifdef DEBUG_YADMA_REG
static inline u32 yadmaWriteReg(BaseAddress, RegOffset, Data)
{
	printk("Write 0x%x to base@ 0x%p offset@ 0x%p.\n", Data, BaseAddress, RegOffset);
	return 0;
}
#else
#define yadmaWriteReg(BaseAddress, RegOffset, Data)     \
    YADMA_REG_WRITE32((Data), (BaseAddress) + (RegOffset*4))
#endif

/****************************************************************************/
/**
* Enable global interrupt bits. This operation will read-modify-write
* the REG_DMA_CTRL_STATUS register.
*
* @param  BaseAddress is the BAR0 address.
*
* @note
* C-style signature:
*    void yadmaIntEnable(u32 BaseAddress)
*
*****************************************************************************/
#define yadmaIntEnable(BaseAddress)        \
{                           \
    u32 Reg = yadmaReadReg(BaseAddress, REG_INT_MASK_AND_SLOTS);   \
    Reg |= (FRAME_INT_ENABLE);            \
    yadmaWriteReg(BaseAddress, REG_INT_MASK_AND_SLOTS, Reg);       \
}


/****************************************************************************/
/**
* Clear global interrupt enable bits. This operation will read-modify-write
* the REG_DMA_CTRL_STATUS register.
*
* @param  BaseAddress is the BAR0 address.
*
* @note
* C-style signature:
*    void yadmaIntDisable(u32 BaseAddress)
*
*****************************************************************************/
#define yadmaIntDisable(BaseAddress)        \
{                           \
    u32 Reg = yadmaReadReg(BaseAddress, REG_INT_MASK_AND_SLOTS);   \
    Reg &= ~(MULTI_SLOT_INT_ENABLE);           \
    yadmaWriteReg(BaseAddress, REG_INT_MASK_AND_SLOTS, Reg);       \
}


/****************************************************************************/
/**
* Acknowledge asserted global interrupts.
*
* @param  BaseAddress is the base address of the device
* @param  Mask has the interrupt signals to be acknowledged and is made
*         by the caller OR'ing one or more of the INT_*_ACK bits.
*
* @note
* C-style signature:
*    u32 yadmaIntAck(u32 BaseAddress, u32 Mask)
*
*****************************************************************************/
/* Currently implemented like this. May have a performance hit. In
 * that case, will re-implement to avoid the extra read. !!!!
 */
#define yadmaIntAck(BaseAddress, Mask)  \
{                       \
    u32 Reg = yadmaReadReg(BaseAddress, REG_INT_ACK);   \
    Reg |= Mask;                    \
    yadmaWriteReg(BaseAddress, REG_INT_ACK, Reg);       \
}


/************************** Function Prototypes ******************************/
#endif

#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */

