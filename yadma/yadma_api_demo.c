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
#include <signal.h>

#include <linux/genetlink.h>
#include <sys/mman.h>

#include "yadma.h"
#include "yadma_api.h"
#include "yadma_proc.h"
#include "hexdump_user.h"
#include "yadma_reg.h"
#include "adi_config.h"



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

    printf("Executes: %s, outputs: \n%s\n", cmd, result);
    return ret;
}


/**
 * This function executes a shell command, and output its result.
 * @param cmd, the command to be excuted.
 * @param result, a buffer, at least 256bytes, to save the shell outputs.
 */
int main(int argc, char **argv)
{
    FILE* fp = NULL;
    void* buff;
    int i;
    int frame_count = 1;
    int block_size = 614400; //YADMA_BLOCK_SIZE;
    
   // int block_size = 2457600; //YADMA_BLOCK_SIZE;  this should changed according to the 
    
    
    int log_addtional_data = 1;

    if(argc != 5) {
        printf("Usage: capture <file name> <frame count> <log addtional>\n");
		return 0;
	}

    if(atoi(argv[4]) == 8)
		block_size = 2457600;
	else if(atoi(argv[4]) == 4)
		block_size = 2457600/2;
	else if(atoi(argv[4]) == 2)
		block_size = 2457600/4;
	else
		block_size = 2457600;
	printf("block_size = %d\n",block_size);
	
	
	
	

    if(!is_ko_inserted && (exec_shell_cmd("insmod yadma.ko", cmd_out_buffer) == 0)) {
        printf("Kernel module 'yadma.ko' install ... OK \n");
        is_ko_inserted = 1;
    }


    if(is_ko_inserted) {
        if(!is_driver_initialized && (DriverInit() == RET_SUCCESS)) {
            is_driver_initialized = 1;
            printf("Call 'DriverInit()' ... OK \n");
        }
    }

    frame_count = atoi(argv[2]);
    log_addtional_data = atoi(argv[3]);

	if(log_addtional_data == 1) {
		printf("Capture data to file ...\n");
		fp = fopen(argv[1], "w+");
	} else if(log_addtional_data == 0) {
		printf("Send out data from file ... \n");
		fp = fopen(argv[1],"r+");
	} else {
		printf("Receiving without save file ...\n");
	}

    if(log_addtional_data == 1 || log_addtional_data  == 0) {
	if(NULL == fp)
    {
        printf("fopen() %s Error!!!\n", argv[1]);
        return -1;
    }
	}

	MapDmaBuffer(TX_CHAN);
	printf("Map Tx DMA buffer ... OK\n");


    MapDmaBuffer(RX_CHAN);
    printf("Map RX DMA buffer ... Ok\n");

    
    /* Adjust the on board 10Mhz reference clock  */
	SetAFCParam(1590290000 /*TODO: set per RF board */, 2142600000 /* downlink centeral freq */);
	AdjustFrequencyOffset(0);

    /* Set the sample rate  */
    SetSampleRate(atoi(argv[4]));

     /* config AFC mode 0: FPGA AFC  / 1:   DRIVER AFC*/
    SetDownlinkAFCMode(1, 00, atoi(argv[4]));
    
    /* use the external 10Mhz clock input */
    SetReferenceClock(0);
    
    /* Enable the board to receive data*/
    StartBoard();
    
    /* Start the cell search */
	StartCellSearch();

    /* Read Board Version */
    //BoardRegRead(0);
    
    
    
    

    printf("All preparation are ready, now start the board.\n");


    if(log_addtional_data == 1)
		//block_size += YADMA_ADDTION_SIZE;
		  block_size  = block_size;      /* REVISIT not add the 128 byte addition data */
		

	if(log_addtional_data == 0) {
		/* Send the data.bin */
		int total_size, read_size, bc;
		fseek(fp , 0 , SEEK_END);
		total_size = ftell (fp);
		rewind (fp);
		if(total_size < 4 * YADMA_BLOCK_SIZE) {
			printf("file is too small.\n");
			return;
		}

		char * good_buff = malloc(YADMA_BLOCK_SIZE);
		for(bc = 0; bc < CUR_TX_BD_COUNT; bc++) {
			buff = GetDmaFrameBuffer(TX_CHAN, bc);
			if(buff == NULL || buff== -1) {
				printf("Invalid DMA buffer.\n");
				break;
			}

			/* read the file into memory */
			read_size = fread(good_buff, 1, YADMA_BLOCK_SIZE, fp);

			printf("Read %d bytes file to DMA buffer %d, Got %d bytes \n", total_size, bc, read_size);
			printf("Copy from %p to %p\n", good_buff, buff);

			memcpy(buff, good_buff, read_size);
			if(read_size != YADMA_BLOCK_SIZE) {
				printf("check your file's size, please. Should be 2457600 x 4 bytes.\n");
			} else {
				print_hex_dump_bytes("@", DUMP_PREFIX_ADDRESS, GetDmaFrameBuffer(TX_CHAN, bc), 16);
			}
		}
		free(good_buff);
	} else {

		/* Receive into capture file */

		printf("Block size is %d bytes\n", block_size);

		i = 0;


        usleep(10000);

		int failed = 0, succeed = 0;
		int sample_valid = 0;
		
		while (i < frame_count) {
			long int offset;

			char *  prx;
			int fn, sn, bl; /* frame and slot number reported by interrupt */

            int ret;
            
			ret = WaitForInterrupt(&fn, &sn, &bl);
			
			 // REVISIT @ 2014/4/21
			 // ad the interrupt judge to remove the command pars \
			 // netlink packet first 10ms frame is not valid need to jump 
			if ( (ret == 1) && (sample_valid == 1 ))  { 
	        
		//	printf("Receive WaitInterrupt\n");
       //		printf("Current RX Pointer is %d,  Current Frame Num %d\n", bl, i);

	#if 0 // TODO: should use 64bit seek
			offset = (long long)i* block_size;
	        printf("offset = %d f\n", offset);
			if(0 != fseek64(fp, offset, SEEK_SET))
			{
				printf("fseek() failed %ld\n", offset);
				return -1;
			}
	#endif

			buff = GetDmaFrameBuffer(RX_CHAN, bl);

			if(buff ==NULL)
				printf("Get DMA block = %d failed\n", bl);
	#if 1
			if(buff != NULL) {
				int written;

			if(log_addtional_data == 1) {
				/* Write the Rx buffer to capture file */
				written = fwrite(buff, 1, block_size, fp);

				if(block_size != written)
				{
					failed++;
				}
				else
				{
					succeed++;
				}
			 } else { // == 2 Do not save file
				printf(".");
			}
			}
	#endif
			i++;
			
			
		    }  //			if ( ret = 1)  
			
			
			
			if ( ret == 1)
			{
		       sample_valid = 1;
		    }
			
			
		}
		if(log_addtional_data == 1) {
			printf("Write %d frames success, %d frames failed\n", succeed, failed);
		} else {
			printf("\n Finished.\n");
		}
	}


	StopBoard();
	UnmapDmaBuffer(TX_CHAN);
	UnmapDmaBuffer(RX_CHAN);
	printf("Unmap DMA buffer ... OK\n");

	if(log_addtional_data == 0 || log_addtional_data == 1) {
		fflush(fp);
    		fclose(fp);
    		printf("Close capture file ... OK\n");
	}

    if((exec_shell_cmd("rmmod yadma", cmd_out_buffer) == 0)) {
        is_ko_inserted = 0;
        printf("Remove kernel module ... %s", cmd_out_buffer);
    }

}



