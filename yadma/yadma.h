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


#ifndef YADMA_H
#define YADMA_H

#define DEBUG_YADMA
//#define DEBUG_YADMA_REG

#define YADMA_UNINITIALIZED       0           /**< State at system start */
#define YADMA_INITIALIZED         1           /**< After probe */

#define YADMA_MAGIC		'Y'
#define YADMA_MAX_CMD	2

#define YADMA_MAJOR		0   /* dynamic major by default */
#define YADMA_MINOR		0

#define YADMA_SUCCESS	0
#define YADMA_FAILURE	1

/* Support two kinds of channels */
#define BLOCK_BASED_CHANNEL	1
#define SLOT_BASED_CHANNEL	2
#define CHANNEL_TYPE	BLOCK_BASED_CHANNEL

/* Keep in order */
#define MAX_CHANS 2 /* Must be 1, 2 or 4 */

/* Block based channels */
#define RX_CHAN   1 /* CPIT:  The tx/rx interlaved channel, TDD */
#define TX_CHAN   0 /* RIGOL: TX channel only for signal generation */

#define DEFAULT_TX_FREQ 2000000000
#define DEFAULT_RX_FREQ 2000000000
#define DEFAULT_REF_CLK 61440000

/* Slot Based channels */
#define TX_CHAN_1 0 /* Tx channel 1 */
#define RX_CHAN_1 1 /* Rx channel 1 */
#define TX_CHAN_2 2 /* Tx channel 2 */
#define RX_CHAN_2 3 /* Rx channel 2 */

/* Keep in order */
//TODO: Only one frequency file and two gain files are need.
#define MAX_FILES	16
#define SYS_INFO            (MAX_CHANS+0)
#define TX_FREQ_CHAN_1		(MAX_CHANS+1)
#define RX_FREQ_CHAN_1		(MAX_CHANS+2)
#define TX_FREQ_CHAN_2		(MAX_CHANS+3)
#define RX_FREQ_CHAN_2		(MAX_CHANS+4)

#define TX_GAIN_CHAN_1		(MAX_CHANS+5)
#define RX_GAIN_CHAN_1		(MAX_CHANS+6)
#define TX_GAIN_CHAN_2		(MAX_CHANS+7)
#define RX_GAIN_CHAN_2		(MAX_CHANS+8)

#define RSSI_CHAN_1			(MAX_CHANS+9)
#define RSSI_CHAN_2			(MAX_CHANS+10)

#define RF_STATE_CHAN_1		(MAX_CHANS+11)
#define RF_STATE_CHAN_2		(MAX_CHANS+12)

#define SYS_TIMING			(MAX_CHANS+13)
#define FPGA_RESET			(MAX_CHANS+14)
#define IRQ_INTERVAL        (MAX_CHANS+15)


/* Bars of FPGA's pcie peer endpoint */
#define MAX_BARS  1
#define BAR_FPGA_CTRL  0
#define BAR_NOT_DEFINED_YET 1

#define YADMA_BLOCK_COUNT   32

/* CPIT: block or frame size in bytes */
#define YADMA_BLOCK_SIZE    2457600
#define YADMA_ADDTION_SIZE  128
#define YADMA_SAMPLE_RATE   4

/* use the place at 2457600 + 0 to store gain value for this frame */
#define YADMA_GAIN_OFFSET   0

// slot size = 2880 smaples X 4 bytes per sample
#define YADMA_SLOT_SIZE  (2880*4)

// 2BYTES per sample for I or Q individually
#define YADMA_I_BYTES_PER_SAMPLE 2
#define YADMA_Q_BYTES_PER_SAMPLE 2

#define YADMA_SLOT_COUNT 40

// How many slots to trigger a interrupt
#define YADMA_INTERUPT_SLOTS 10

#define YADMA_MEM_SIZE (YADMA_BLOCK_COUNT*YADMA_BLOCK_SIZE)

// new define for frame/slot/sample structure that binding I-Q samples together in 4 BYTES
#define YADMA_SAMPLES_PER_SLOT	2880
#define YADMA_BYTES_PER_SAMPLE  4
#define YADMA_SLOT_DURATION_IN_US 1500
#define YADMA_SLOT_COUNT_PER_FRAME 40
#define YADMA_FRAME_DURATION_IN_US 60000
#define YADMA_FRAME_SIZE (YADMA_BLOCK_COUNT*YADMA_SAMPLES_PER_SLOT*YADMA_BYTES_PER_SAMPLE*YADMA_SLOT_COUNT_PER_FRAME)
#define YADMA_SAMPLE_FILE_SIZE (10*YADMA_FRAME_SIZE)

/* Type of pcie BAR */
#define BAR_TYPE_MEM 1
#define BAR_TYPE_IO  2

/* IOCTL commands for dev interface */
#define IOCTL_GET_TX1_GAIN _IOR(YADMA_MAGIC, 1, GainStru)
#define IOCTL_SET_TX1_GAIN _IOW(YADMA_MAGIC, 2, GainStru)



#define NETLINK_USER 31
#define MAX_PAYLOAD 256 /* maximum payload size*/

#define YADMA_PROC_ACESS_RIGHTS 0666
#define YADMA_PROC_DIR		"/proc/yadma"
#define YADMA_SYSFS_DIR 	"/sys/module/yadma"
#define YADMA_DEVFS_DIR		"/dev/yadma"

#define DRIVER_NAME			"yadma"
#define DRIVER_FILE_NAME	"yadma.ko"

#define YADMA_FILE_COUNT  (MAX_CHANS + MAX_FILES)

/* File names to be used for read/write/parameters of yadma driver */
/* Same order as MACRO defination of  CHANs and FILEs */
static const char* yadmaFileNames[YADMA_FILE_COUNT] =
{
#if (CHANNEL_TYPE == BLOCK_BASED_CHANNEL)
#if (MAX_CHANS == 2)
    "TxMemCh1",
    "RxMemCh1",
#endif
#endif

#if (CHANNEL_TYPE == SLOT_BASED_CHANNEL)
#if (MAX_CHANS >= 2 )
	"TxMemCh1",
	"RxMemCh1",
#if (MAX_CHANS == 4)
	"TxMemCh2",
	"RxMemCh2",
#endif
#endif
#endif

    "SysInfo",
	"TxFreqCh1",
	"RxFreqCh1",
	"TxFreqCh2",
	"RxFreqCh2",

	"TxGainCh1",
	"RxGainCh1",
	"TxGainCh2",
	"RxGainCh2",

	"RSSICh1",
	"RSSICh2",
	"RFStateCh1",
	"RFStateCh2",

	"SysTiming",
	"FPGAReset",
	"IrqInterval",
};

/* Kernel user space communication types.
 * Each type corrsponding to a structure.
 */

typedef enum _kuc_enum
{
	KUC_TYPE_DEMO = 0,
	KUC_TYPE_GAIN = 1,
	KUC_TYPE_FINISH = 2,
	KUC_TYPE_INTERRUPT = 3,
	KUC_TYPE_BAR_OP = 4,
	KUC_TYPE_REGISTER = 5,
    KUC_TYPE_BOARD_INFO = 6,
    KUC_TYPE_VERSION_INFO = 7,
}KucType;

enum
{
	KUC_BAR_OP_READ = 1,
	KUC_BAR_OP_WRITE = 2,
};

/* Corresponding to KUC_TYPE_BAR_READ/WRITE */
typedef struct
{
	unsigned int reg;		/* reg offset in DWORD unit */
	unsigned int value;		/* the read/write value */
} RegPair;

typedef struct
{
	int op;			/* read or write */
	int bar;		/* bar number */
	int count;		/* how many reg/value pairs followed */
	unsigned char data[0];	/* placeholder for reg pairs */
} BarOpStru;

/* Correspondign to KUC_TYPE_DEMO */
typedef struct
{
	int channel;
	int fs;          /*1- procfs or 2- sysfs */
	int times;		 /* how many times interrupt trigger user space */
	int interval;	 /*interrupt interval */
	char pattern[MAX_PAYLOAD/2];    /*A data pattern to be used by kernel */
} DemoStruct;

typedef struct
{
	char name[32];
	int  id;
} RegsiterStruct;

/* Corresponding to KUC_TYPE_GAIN */
typedef struct
{
	int path; /* The path the gain apply for */
	int gain; /* Gain in dB */
} GainStru;

/* Corresponding to KUC_TYPE_FINISH */
typedef struct
{
	int ch;
	int block;
	int slot;
} FinishStru;

/* Corresponding to KUC_TYPE_INTERRUPT */
typedef struct
{
	struct timespec time;	/* time of the interrupt occurred at */
	int mask; 		/* bit mask for pending interrupts */
	int multi;		/* If INT_MULTIPLE_SLOT_END occur, what is the multiplicy */
	int ch;
	int block;
	int	frame;
	int	slot;
	int sync_status;
	int coars_freq_est;     /*REVISIT duanchenyi*/
	int fine_freq_est;       /*REVISIT duanchenyi*/
	int timing_est;           /*REVISIT duanchenyi*/
    int freq_est;            /*REVISIT duanchenyi*/
}InterruptStru;

/* Bit masks for pending interrupts defination */
/* Two working modes:
 * 1. dynamic buffer, i.e async mode
 * 2. ring buffer, i.e sync mode
 */
 #define DMA_ASYNC_MODE		1
 #define DMA_SYNC_MODE		2

/* reports tx buffer is empty.
 * if working in dynamic buffer mode, it will stop to send data.
 * if working in ring buffer mode, it will sent staled data from now on. */
#define INT_TX_BUFFER_EMPTY				1

/* reports no tx buffer slots available
 * if working in dynamic buffer mode, no new data will be commited to fpga.
 * if working in ring buffer mode,  it overwirte unsent slots */
#define INT_TX_BUFFER_FULL				(1 << 1)

/* report rx buffer is empty */
#define INT_RX_BUFFER_EMPTY				(1 << 2)

/* report rx buffer is full */
#define INT_RX_BUFFER_FULL				(1 << 3)

/* interrupt at mutiple slots interval */
#define INT_MULTIPLE_SLOT_END			(1 << 4)


#define KUC_COMMAND_FIELD_LENGTH		8 //if has 'len'

/* Kernel Userspace communiction Message */
typedef struct
{
	struct nlmsghdr nlh; /* Net link message header */
	int len;	 /* lenght of the following fields,
					include itself */
	int type;    /* KucType */
	int data[0]; /* Contains the real communication
					structure according to the KUC type */
} KucMessage;

/* A function pointer type that can point to any */
typedef void (*void_func_ptr) ();
#endif
