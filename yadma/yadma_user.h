/*****************************************************************************/
/**
*
* @file yadma_user.h
*
* This header file contains user space API and identifiers.
* MODIFICATION HISTORY:
*
* Ver   Date     Changes
* ----- -------- -------------------------------------------------------
* 1.0   5/15/12  First version
*
******************************************************************************/

#ifndef YADMA_USER_H   /* prevent circular inclusions */
#define YADMA_USER_H   /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

//TODO: remove the python debug code
//#define PYTHON_INTERFACE_DEBUG 1
#define RING_BUFFER_MANAGEMENT  1

/************************** Constant Definitions *****************************/
#define logMsg printf

#ifdef DEBUG_YADMA
#define log_verbose(args...)    printf(args)
#else
#define log_verbose(x...)
#endif

#define false 0
#define true 1

#define ASSERT(...)

/************************** Function Prototypes ******************************/
int DriverInit(void);
int DriverRemove(void);

void* MapDmaChannelByDevfs(int ch);
void* MapDmaChannelByProcfs(int ch);
void* MapDmaChannelBySysfs(int ch);
int MapTxRxDmaChannel(int ch);
int UnmapTxRxDmaChannel(int ch);

int Send2KernelByNetLink(KucMessage * kuc);
int RecvFromKernelFromNetLink(KucMessage * kuc);
int WaitForInterrupt(int *fn, int *sn, int *bl);

void* GetChannelPointer(int ch);
char* GetBlockPointer(int ch,int block);
void* GetSlotPointer(int ch, int block, int slot);

#ifdef RING_BUFFER_MANAGEMENT
void  InitializeRingBuffer(int ch, void* data, int len);

int GetNextNSlotNumber(int ch, int cur_block, int cur_slot, int nextn, int *pblock, int* pslot);
int GetPrevNSlot(int ch, int cur_block, int cur_slot, int prevn, int *pblock, int* pslot);

void* GetNextNBlockPointer(int ch, int nblock);
void* GetNextBlockPointer(int ch);
void* GetCurrentBlockPointer(int ch);

void* GetNextNSlotPointer(int ch, int nslot);
void* GetNextSlotPointer(int ch);
void* GetCurrentSlotPointer(int ch);

void SwitchToNextBlock(int ch);
void SwitchToNextSlot(int ch);
void SwitchToPrevBlock(int ch);
void SwitchToPrevSlot(int ch);
#endif


void ReleaseSlots(int ch, int block, int slot);
static void SaveKernelStatus(int ch, int block, int frame, int slot);

#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */

