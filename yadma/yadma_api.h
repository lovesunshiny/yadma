/**
 * @file
 *
 * @brief yadma API
 */

/*
 * Copyright 2014(C) Taiyi-TEK.
 *
 */


#ifndef YADMA_API_H
#define YADMA_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef unsigned int        u32_t;
typedef int                 int_t;
typedef unsigned short      u16_t;
typedef unsigned char       u8_t;
typedef unsigned char       bool_t;


/**
 * @defgroup  The Yadma Driver API
 *
 * @brief How to User Space Application Programming Interface
 *
 * The following graph discribes the flow chart for using the key APIs,
 * such as, WaitForInterrupt, GetDmaFrameBuffer, ReleaseSlots, etc.
 * Generally speaking, there is one main loop, which handles all of the wait/get/use
 * things of DMA buffers belongs to different channels.
 *
 * @dot
digraph test {
node [style=filled]
"Start" -> "insmod yadma.ko"
"DriverInit()" -> "MapDmaChannel(n)"
"insmod yadma.ko" -> "DriverInit()"
"MapDmaChannel(n)" -> "StartBoard()"
"StartBoard()" -> "WaitForInterrupt(fn, sn, bl)"
"ReleaseSlots(ch, bl, sn)" -> "WaitForInterrupt(fn, sn, bl)"
"WaitForInterrupt(fn, sn, bl)" -> "exit?"
"exit?" -> "DriverRemove()"
"exit?" -> "GetDmaFrameBuffer"
"GetDmaFrameBuffer" -> "Using the DMA buffer" -> "ReleaseSlots(ch, bl, sn)"
"rmmod yadma" -> "End"
"DriverRemove()" -> "rmmod yadma"
}

 * @enddot
 *
 * @{
 */

enum {
    RET_FAILED = 0,
    RET_SUCCESS = 1
};

enum AGCMode_E {
    AGC_MODE_MANUAL = 0,
    AGC_MODE_AUTO = 1,
};

enum RefClock_E {
    EXTERNAL_CLK = 1,
    INTERNAL_CLK = 2,
    GPS_CLK = 3
};

enum PLLStage_E {
    PLL_STAGE_1 = 1,
    PLL_STAGE_2 = 2,
};

enum PLLState_E {
    PLL_LOCKED = 1,
    PLL_NOT_LOCKED = 0
};

enum Transceiver_E {
    Transceiver_1 = 1,
    Transceiver_2 = 2,
};

enum Alarm_E {
    DMA_OVERFLOW_ALARM =    0x1,
    SYNC_LOST_ALARM =       0x2,
    INPUT_TOO_HIGH_ALARM =  0x4,
};



/**
 * @brief A structure to represent version information.
 *
 */
/**
 * @brief
 *
 *
 */
typedef struct //_version_info
{
    u32_t   boardVersion; /**<  */
    u32_t   driverVersion; /**<  */
} VersionInfo_T;

/**
 * @brief A structure to represent board information.
 *
 */
typedef struct //_board_info
{
    u32_t   boardType; /**<  */
    u32_t   workBand; /**<  */
    u32_t   serialNum; /**<  */
} BoardInfo_T;

typedef struct
{
    int slotGain;
	char slotData[];
} SlotBuffer_T;

typedef struct
{
	char frameData[YADMA_BLOCK_SIZE/YADMA_SAMPLE_RATE]; /** frameData has differents size according the sampling rate */
    int frameGain; /** Gain is located at the first DWORD of additional data */
} FrameBuffer_T;

typedef struct
{
    int frameType;
} SystemCfg_T;

typedef struct
{
    int csRssi;
	int csRsrp;
}ChannelStatus_T;
/**
 * @brief 版本号读取
 *
 * 读取板卡本信息，以便维护更新.
 *         The version information including board version and driver version.
 * @sa  VersionInfo
 *
 * @param version [out]  The pointer to save version information.
 */

void ReadVersion(VersionInfo_T *version);


/**
 * @brief 获取板卡信息（型号，频带，编号）
 *
 * 提供板卡的基本信息，提高系统扩展性和稳定性；
 *
 * \sa  BoardInfo
 *
 * @param info [out]  The pointer to save version information.
 */

void GetBoardInfo(BoardInfo_T *info);


/**
 * @brief Initial the PCIe 
 *        called before any pci write operate 
 *        This function will 
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */


bool_t InitPcieKuc (void);

/**
 * @brief 启动板卡工作
 *
 * 启动射频及相关部分的电源，准备进行数据采集
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t StartBoard(void);

/**
 * @brief 停止板卡工作
 *
 * 停止采集操作，为保护电路，需要关闭射频部分的电源
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t StopBoard(void);

/**
 * @brief 设置上行信号中心频点
 *
 * 设置上行接收链路的中心频点 (Unit: KHz)
 *
 * @param freq [in] The frequency point in KHz unit.
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */

 bool_t SetUpLinkFreqPoint(u32_t freq);

/**
 * @brief 设置下行信号中心频点
 *
 * 设置下行接收链路的中心频点 (Unit: KHz)
 *
 * @param freq [in] The frequency point in KHz unit.
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */

bool_t SetDownLinkFreqPoint(u32_t freq);

/**
 * @brief  设置下行信号带宽
 *
 * 设置下行接收链路的检测带宽 (Unit: KHz)
 *
 * @param bw [in] The frequency bandwidth in KHz unit.
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */

bool_t SetDownlinkBandWidth(u32_t bw);

/**
 * @brief  设置上行信号带宽
 *
 * 设置上行接收链路的检测带宽 (Unit: KHz)
 *
 * @param bw [in] The frequency bandwidth in KHz unit.
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */

bool_t SetUplinkBandWidth(u32_t bw);

/**
 * @brief  上行增益控制模式设置
 *
 * 设置上行接收链路增益控制模式：自动控制,APP控制
 *
 * @param mode [in] The AGC working mode.
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t  SetUplinkAGCMode(int mode);

/**
 * @brief  下行增益控制模式设置
 *
 * 设置下行接收链路增益控制模式：自动控制、APP控制
 *
 * @param mode [in] The AGC working mode.
 *
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t  SetDownlinkAGCMode(int mode);


/**
 * @brief Set Down link AFC Mode
 *        mode = 0 : the FPGA do the AFC/ 1: the Driver do the AFC
 *        freq_offset :  (Unit: HZ)
 *                      f VALID RANGE :  8X rate : -15Khz   ~ +15Khz
 *                                       4X rate : -7.5Khzs ~ 7.5Khz
 *                                       2X rate : -3.75Khz ~ 3.75Khz
 *                      f = F - Fref     (F current frequency, Fref : expected frequency)                         
 *                      DONOT use the f not in the above range 
 * 
 * 
 * @param mode [in] The AFC working mode.
 *
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t SetDownlinkAFCMode( unsigned int  mode, short  freq_offset, unsigned int sample_rate );

/**
 * @brief  上行射频接收增益设置
 *
 * 当采用APP控制增益模式时，由APP设置上行接收通路的射频增益
 *
 * @param gain [in] The gain value in 1/4 dB Unit.
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t  SetUplinkGain(int gain);

/**
 * @brief  下行射频接收增益设置
 *
 * 当采用APP控制增益模式时，由APP设置下行接收通路的射频增益
 *
 * @param gain [in] The gain value in 1/4 dB unit.
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t  SetDownlinkGain(int gain);

/**
 * @brief  设置系统时钟源
 *
 * 设置采样时钟的同步时钟源，可采用外部同步，自同步和GPS等方式
 *              clk_mode 0 :  use the on board reference clock
 *                       1 :  use the external reference clock
 *  
 * @param clk_mode[in] The  reference clock source 
 * @sa RefClock_E
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t  SetReferenceClock(u32_t clk_mode);


/**
 * @brief 设置系统外部时钟源频率
 *
 * 当使用外部时钟源同步采样时钟时，设定外部时钟源频率 (Unit: KHz)
 *
 * @param freq [in] The frequency point in KHz unit.
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */

bool_t  SetExtRefClockFrequency(u32_t freq);


/**
 * @brief PLL时钟锁相环状态查询
 *
 * 查询采样时钟的锁相环状态
 *
 * @param stage [in] Which PLL to be checked.
 * @sa PLLStage_E
 *
 * @return This stage is locked or not.
 * @sa PLLState_E
 */
int_t GetPLLState(int stage);



/**
 * @brief 告警处理
 *
 * 缓冲区告警、失步告警、输入信号能量过大等告警信息的处理
 *
 * @return The bitmask of alarm status.
 * @sa Alarm_E
 */
u32_t GetAlarmStatus(void);


/**
 * @brief Set parameters for long time frequency offset adjustment.
 *
 * The DAC value is cacluated according following fomula,
 * DAC = deltaF * y/fRF + Previous DAC Value
 *
 */

void SetAFCParam(double y, double fRF);

/**
 * @brief 系统频偏调整
 *
 * 设置VCXO电平（待定）或由应用程序通知板卡同步偏差，以便纠正采样时钟的采样频率 (Unit: HZ)
 * deltaF = F - Fref
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 * Affect both downlink and uplink, because it applys on the sys clock.
 */

bool_t AdjustFrequencyOffset(int_t delta);

/**
 * @brief 系统频偏调整 (uplink only)
 *
 * 设置VCXO电平（待定）或由应用程序通知板卡同步偏差，以便纠正采样时钟的采样频率 (Unit: HZ)
 * deltaF = F - Fref
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t AdjustUplinkFrequencyOffset(int_t delta, int sample_rate);

/**
 * @brief 系统定时调整
 *
 * Adjust system timing offset. (Unit: sample duration)
 * deltaT = T - Tref  (unit is converted to sample)
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */

bool_t AdjustTimingOffset(int_t delta);



/**
 * @brief Start cell search
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t StartCellSearch(void);


/**
 * @brief Set I/Q sampling rate
 *
 * Set system sampling rate. (Unit: samples/s)
 *   Valid Value :  8 - >  8X sample rate
 *               :  4 - >  4X sample rate
 *               :  2 - >  2X sample rate
 * 
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t SetSampleRate(u32_t sample_rate);

/**
 * @brief Get I/Q sampling rate
 *
 * Get system sampling rate. (Unit: samples/s)
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
u32_t GetSampleRate(void);


/**
 * @brief Get channel status information.
 *
 * Get channel status information, such as RSSI, RSRP, etc.
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */

bool_t GetChannelStatusInfo(ChannelStatus_T *status);

/**
 * @brief Get the pointer to frame buffer.
 *
 * After MapDmaChannels, caller can get a frame buffer through this API.
 * The frame buffer is continous memory region in designed format.
 *
 * @ch  [in]  Specify the DMA channel.
 * @block [in] Specify the block number, i.e the corresonding block number for just received frame.
 *
 * @retrun NULL If the DMA buffer is not available or error occured.
 *         Otherwise if success.
 */

FrameBuffer_T* GetDmaFrameBuffer(int ch, int block);

/**
 * @brief Get the pointer to a buffer of specified frame and slot
 *
 * After received a interrupt, caller can get a slot buffer through this API.
 * The slot buffer is continous memory in designed format. After used the slot
 * buffer, caller should call \sa ReleaseSlot to tell kernel side the slot is
 * finished processing by user space.
 *
 * @ch  [in]  Specify the DMA channel.
 * @frame [in] Specify the frame number, i.e the frame number has corresonding block.
 * @slot [in] Specify the slot number.
 *
 * @retrun NULL If the DMA buffer is not available or error occured.
 *         Otherwise if success.
 */

SlotBuffer_T* GetDmaSlotBuffer(int ch, int frame, int slot);

/**
 * @brief Get AGC gain value for specified frame.
 *
 * The AGC value can change frame by frame. Using this API to get the gain value
 * for specified frame.
 *
 * @ch  [in]  Specify the DMA channel.
 * @frame [in] Specify the frame number, i.e the frame number has corresonding block.
 *
 * @return
 * The gain value.
 */
int_t GetAGCGainForFrame(int ch, int frame);

/**
 * @brief 其他WCDMA系统相关配置 setter
 *
 * set其他与系统及板卡相关的配置功能；
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t SetSystemConfig(SystemCfg_T *config);

/**
 * @brief 其他WCDMA系统相关配置 getter
 *
 * get其他与系统及板卡相关的配置功能；
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t GetSystemConfig(SystemCfg_T *config);

/**
 * @brief Initialize the DMA driver.
 *
 * Initialize all facilities to be used by user space program:
 *  - ring buffer management data structures
 *  - kernel/userspace communication sockets
 *  - etc
 *
 *  This function should be called after 'insmod yadma.ko'
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
extern int DriverInit(void);

/**
 * @brief Free the DMA driver allocated resources.
 *
 * @note The function not remove the kernel module.
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
extern int DriverRemove(void);


/**
 * @brief Mmap the kernel space DMA buffer to userspace.
 *
 * @return
 * A pointer of userspace the pointed to the DMA buffer in kernel space.
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t MapDmaBuffer(int ch);


/**
 * @brief Mmap the kernel space DMA buffer to userspace.
 *
 * @return
 * A pointer of userspace the pointed to the DMA buffer in kernel space.
 *
 * @retval RET_SUCCESS  The operation is succeed.
 * @retval RET_FAILED THe operation is failed.
 */
bool_t UnmapDmaBuffer( int ch );




u32_t BoardRegRead(u32_t reg);

bool_t BoardRegWrite(u32_t reg, u32_t val);

/**
 * @brief caller block here to wait for interrupt.
 *
 * This function is used for waiting interrupt. If a interrupt from FPGA occured,
 * the kernel side will inform user space program through this API.
 *
 * @fn [out] The pointer to output frame number at the time of interrupt occur.
 * @sn [out] The pointer to output slot number at the time of interrupt occur.
 * @bl [out] The pointer to output block number at the time of interrupt occur.
 *
 * @return
 * If wait for a interrupt sucessfully, return a value > 0; Otherwise < 0.
 *
 * @retval 0 TBD
 */
extern int WaitForInterrupt(int *fn, int *sn, int *bl);


/**
 * @brief The slots is released by user space.
 *
 * @return
 */
extern void ReleaseSlots(int ch, int frame, int slot);





#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* YADMA_API_H */
