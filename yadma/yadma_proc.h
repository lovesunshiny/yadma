/*****************************************************************************/
/**
*
* @file yadma_proc.h
*
* This header file contains user space API and identifiers for procfs.
* MODIFICATION HISTORY:
*
* Ver   Date     Changes
* ----- -------- -------------------------------------------------------
* 1.0   5/15/12  First version
*
******************************************************************************/

#ifndef YADMA_PROC_H   /* prevent circular inclusions */
#define YADMA_PROC_H   /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/



/************************** Constant Definitions *****************************/



/************************** Function Prototypes ******************************/
void register_proc_files(void);
void unregister_proc_files(void);



#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */

