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

#include <math.h>

#include "yadma.h"
#include "yadma_api.h"
#include "yadma_user.h"
#include "yadma_reg.h"


static KucMessage *yadmaTxKuc = NULL;

#define CHECK_TX_KUC_BOOL \
if(!yadmaTxKuc) return RET_FAILED

#define CHECK_TX_KUC_VOID \
if(!yadmaTxKuc) return

void ReadVersion( VersionInfo_T *version )
{
    CHECK_TX_KUC_VOID;

}

void GetBoardInfo( BoardInfo_T *info )
{
    CHECK_TX_KUC_VOID;
}

	/* REVISIT @ 2014/4/3 by bangxi move the initial from start_board to the DriverInit */
bool_t InitPcieKuc (void)

{

    yadmaTxKuc = malloc(MAX_PAYLOAD);
   
   
   printf("yadmaTxKuc = %x\n", yadmaTxKuc);
    CHECK_TX_KUC_BOOL;

    yadmaTxKuc->len = NLMSG_SPACE(sizeof(KucMessage) + sizeof(BarOpStru) + sizeof(RegPair));
    yadmaTxKuc->type = KUC_TYPE_BAR_OP;

    BarOpStru *bop = (BarOpStru *)yadmaTxKuc->data;
    bop->count = 1;
    bop->op = KUC_BAR_OP_WRITE;
    bop->bar = BAR_FPGA_CTRL;
    
	return RET_SUCCESS;
	
	}


/* All of the API can be called after the board is started */
bool_t StartBoard( void )
{
	
   // yadmaTxKuc = malloc(MAX_PAYLOAD);
   
    CHECK_TX_KUC_BOOL;

   // yadmaTxKuc->len = NLMSG_SPACE(sizeof(KucMessage) + sizeof(BarOpStru) + sizeof(RegPair));
   // yadmaTxKuc->type = KUC_TYPE_BAR_OP;

    BarOpStru *bop = (BarOpStru *)yadmaTxKuc->data;
    bop->count = 2;
    bop->op = KUC_BAR_OP_WRITE;
    bop->bar = BAR_FPGA_CTRL;

    RegPair *rp = (RegPair*)bop->data;
    rp->reg = REG_ROUTE_AND_CTRL;
    rp->value = 0x12001; //TODO: value to stop board

	rp++;
	rp->reg = REG_INT_MASK_AND_SLOTS;
	rp->value = FRAME_INT_ENABLE; //TODO: slots should be read back first

    Send2KernelByNetLink(yadmaTxKuc);

	return RET_SUCCESS;
}

/* No periodic interrupt reported after board is stopped */
bool_t StopBoard( void )
{
    CHECK_TX_KUC_BOOL;

    BarOpStru *bop = (BarOpStru *)yadmaTxKuc->data;
    bop->count = 2;
    bop->op = KUC_BAR_OP_WRITE;
    bop->bar = BAR_FPGA_CTRL;

    RegPair *rp = (RegPair*)bop->data;
    rp->reg = REG_ROUTE_AND_CTRL;
    rp->value = 0x12000; //TODO: value to stop board

	rp++;
	rp->reg = REG_INT_MASK_AND_SLOTS;
	rp->value = 0;

    Send2KernelByNetLink(yadmaTxKuc);

	return RET_SUCCESS;
}

bool_t SetUpLinkFreqPoint( u32_t freq )
{
	return RET_SUCCESS;
}

bool_t SetDownLinkFreqPoint( u32_t freq )
{
    CHECK_TX_KUC_BOOL;

	return RET_SUCCESS;
}

bool_t SetDownlinkBandWidth( u32_t bw )
{
    CHECK_TX_KUC_BOOL;

	return RET_SUCCESS;
}

bool_t SetUplinkBandWidth( u32_t bw )
{
    CHECK_TX_KUC_BOOL;

	return RET_SUCCESS;
}

bool_t SetUplinkAGCMode( int mode )
{
    CHECK_TX_KUC_BOOL;

	return RET_SUCCESS;
}

bool_t SetDownlinkAGCMode( int mode )
{
    CHECK_TX_KUC_BOOL;

	return RET_SUCCESS;
}

bool_t SetUplinkGain( int gain )
{
    CHECK_TX_KUC_BOOL;

	return RET_SUCCESS;
}

bool_t SetDownlinkGain( int gain )
{
    CHECK_TX_KUC_BOOL;

	return RET_SUCCESS;
}

bool_t SetReferenceClock( u32_t clk_mode )
{
    CHECK_TX_KUC_BOOL;
    
    

    BarOpStru *bop = (BarOpStru *)yadmaTxKuc->data;
    bop->count = 2;
    bop->op = KUC_BAR_OP_WRITE;
    bop->bar = BAR_FPGA_CTRL;

    RegPair *rp = (RegPair*)bop->data;
    rp->reg = REG_PLL1_REF_SEL;
    
    if (clk_mode == 1) {
       rp->value = 0x08; // use the external reference clock
   }
    else if (clk_mode == 0) {
       rp->value = 0x0C; // use the on board reference clock
   } 
       

	rp++;
	rp->reg = REG_PLL1_UPDATA;
	rp->value = 0x00001; //

    
    Send2KernelByNetLink(yadmaTxKuc);



	return RET_SUCCESS;
}

bool_t SetExtRefClockFrequency( u32_t freq )
{
    CHECK_TX_KUC_BOOL;

	return RET_SUCCESS;
}

int_t GetPLLState( int stage )
{
	return RET_SUCCESS;
}

u32_t GetAlarmStatus( void )
{
	return RET_SUCCESS;
}

static double afc_param_y = 1;
static double afc_prev_dac = 2048.; //0x800;
static double afc_param_fRF = 2600000000.0; //2.6G

void SetAFCParam(double y, double fRF)
{
	printf("Into the SetAFCParam\n");
    afc_param_y = y;
    afc_param_fRF = fRF;
}

bool_t AdjustFrequencyOffset( int_t delta )
{
    CHECK_TX_KUC_BOOL;
    
    printf("Into the AdjustFrequencyOffset\n");

    BarOpStru *bop = (BarOpStru *)yadmaTxKuc->data;
    bop->count = 1;
    bop->op = KUC_BAR_OP_WRITE;
    RegPair *rp = (RegPair*)bop->data;
    rp->reg = REG_AFC_DAC_VALUE;
    rp->value = afc_param_y * delta/afc_param_fRF + afc_prev_dac;


    log_verbose("DAC = %d\n", rp->value);
    printf("DAC = %x/n", rp->value);
    Send2KernelByNetLink(yadmaTxKuc);
    afc_prev_dac = rp->value;

    Send2KernelByNetLink(yadmaTxKuc);

	return RET_SUCCESS;
}

bool_t AdjustUplinkFrequencyOffset(int_t delta, int sample_rate)
{
    CHECK_TX_KUC_BOOL;

    delta = - delta;
    BarOpStru *bop = (BarOpStru *)yadmaTxKuc->data;
    bop->count = 1;
    bop->op = KUC_BAR_OP_WRITE;
    RegPair *rp = (RegPair*)bop->data;
    rp->reg = REG_UPLINK_FREQ_OFFSET;
    rp->value = (delta *pow(2,26))/(8 * 3840000) - 1;
    
    log_verbose("Uplink (f) = %d\n", rp->value);
    
    Send2KernelByNetLink(yadmaTxKuc);

	return RET_SUCCESS;
}

bool_t StartCellSearch(void)
{
    CHECK_TX_KUC_BOOL;

    BarOpStru *bop = (BarOpStru *)yadmaTxKuc->data;
    bop->count = 1;
    bop->op = KUC_BAR_OP_WRITE;
    RegPair *rp = (RegPair*)bop->data;
    rp->reg = REG_START_CELL_SEARCH;
    rp->value = 1;

    Send2KernelByNetLink(yadmaTxKuc);

	return RET_SUCCESS;
}

bool_t AdjustTimingOffset( int_t delta )
{
    CHECK_TX_KUC_BOOL;

	return RET_SUCCESS;
}

bool_t SetSampleRate( u32_t sample_rate )
{
    CHECK_TX_KUC_BOOL;
    
    

    if ((sample_rate != 2)  && (sample_rate != 4)  && (sample_rate != 8)) {
		
		printf("Parameter ERROR : Sample should be 2, 4 , 8/n");
		return     RET_FAILED;
		
		}
    
    BarOpStru *bop = (BarOpStru *)yadmaTxKuc->data;
    bop->count = 1;
    bop->op = KUC_BAR_OP_WRITE;
    RegPair *rp = (RegPair*)bop->data;
    rp->reg = REG_SMAPLE_RATE_IF;
    if(sample_rate == 2)
		rp->value = 0X03;                 // IF input mode
	else if(sample_rate == 4)
		rp->value = 0X01;
    else if(sample_rate == 8)
		rp->value = 0X00;
    else
		rp->value = 0X03;
		
		
    printf("Set sample rate to %d\n", sample_rate);
    Send2KernelByNetLink(yadmaTxKuc);

	return RET_SUCCESS;
}

bool_t SetDownlinkAFCMode( unsigned int  mode, short  freq_offset , unsigned int sample_rate)
{
	CHECK_TX_KUC_BOOL;

    unsigned short freq;     /* signed 16 bit frequency offset.  */
    

    if ((sample_rate == 2) && ((freq_offset > 3750) || (freq_offset < -3750))) {
		printf("Parameter ERROR : freq_offset execed RANG in 2X rate  (-3.75Khz ~ +3.75Khz/n");
		return     RET_FAILED;
	}
	
    if ((sample_rate == 4) && ((freq_offset > 7500) || (freq_offset < -7500))) {
		printf("Parameter ERROR : freq_offset execed RANG in 4X rate  (-7.5Khz ~ +7.5Khz/n");
		return     RET_FAILED;
	}	
		
    if ((sample_rate == 8) && ((freq_offset > 15000) || (freq_offset < -15000))) {
		printf("Parameter ERROR : freq_offset execed RANG in 8X rate  (-15Khz ~ +15Khz/n");
		return     RET_FAILED;
	}	
    

	BarOpStru *bop = (BarOpStru *)yadmaTxKuc->data;
    bop->count = 1;
    bop->op = KUC_BAR_OP_WRITE;
    RegPair *rp = (RegPair*)bop->data;
    rp->reg = REG_AFC_CFG;
    
    
    freq = (freq_offset * pow(2,26)) /(8 *3840000)-1;
     
    rp->value = (mode<<16)  + freq;
    printf("SetDownlinkAFCMode Signal Frequency %u  rp-value = %u, sample_rate = %d \n", freq, rp->value , sample_rate);

	Send2KernelByNetLink(yadmaTxKuc);

	return RET_SUCCESS;
}
u32_t GetSampleRate( void )
{
	return RET_SUCCESS;
}

bool_t GetChannelStatusInfo( ChannelStatus_T *status )
{
	return RET_SUCCESS;
}

FrameBuffer_T* GetDmaFrameBuffer( int ch, int block )
{
   FrameBuffer_T*temp;
    temp = (FrameBuffer_T*)GetBlockPointer(ch, block);
    //printf("inside getDmaFrameBuffer = %p\n", temp);
    return temp;
}

SlotBuffer_T* GetDmaSlotBuffer( int ch, int frame, int slot )
{
	return NULL;
}

int_t GetAGCGainForFrame( int ch, int frame )
{
	return RET_SUCCESS;
}

bool_t SetSystemConfig( SystemCfg_T *config )
{
    CHECK_TX_KUC_BOOL;

	return RET_SUCCESS;
}

bool_t GetSystemConfig( SystemCfg_T *config )
{
	return RET_SUCCESS;
}

bool_t MapDmaBuffer( int ch )
{
	if(ch < MAX_CHANS) {
		MapTxRxDmaChannel(ch);
		return RET_SUCCESS;
	} else {
		return RET_FAILED;
	}
}

bool_t UnmapDmaBuffer( int ch )
{
	if(ch < MAX_CHANS) {
		UnmapTxRxDmaChannel(ch);
		return RET_SUCCESS;
	} else {
		return RET_FAILED;
	}
}

u32_t BoardRegRead(u32_t reg)
{
    CHECK_TX_KUC_BOOL;
    
    u32_t ret;
    int ret_val;
    
    int fn, sn, bl;

    BarOpStru *bop = (BarOpStru *)yadmaTxKuc->data;
    bop->count = 1;
    bop->op = KUC_BAR_OP_READ;
    RegPair *rp = (RegPair*)bop->data;
    rp->reg = reg;
    
    Send2KernelByNetLink(yadmaTxKuc);
    
    // REVESIT @ 2014/5/4 by bangxi 
    // Wait until the read socket packet back
    while (ret_val != 2) {
       ret_val = WaitForInterrupt(&fn, &sn, &bl);
    }
  // ??????????  how to send the struct out ?
    printf("Read Reg from Board  =  %d , rp = %x \n", rp->value , yadmaTxKuc);

	return ret;
}



bool_t BoardRegWrite(u32_t reg, u32_t val)
{
    CHECK_TX_KUC_BOOL;

    BarOpStru *bop = (BarOpStru *)yadmaTxKuc->data;
    bop->count = 1;
    bop->op = KUC_BAR_OP_WRITE;
    RegPair *rp = (RegPair*)bop->data;
    rp->reg = reg;
    rp->value = val;
    
    Send2KernelByNetLink(yadmaTxKuc);

	return RET_SUCCESS;
}




#ifdef ALL_IMPLEMENTED_IN_API
int DriverInit( void )
{

	return RET_SUCCESS;
}

int DriverRemove( void )
{
	return RET_SUCCESS;
}

int WaitForInterrupt( int *fn, int *sn, int *bl )
{
	return RET_SUCCESS;
}

void ReleaseSlots( int ch, int frame, int slot )
{

}


#endif
