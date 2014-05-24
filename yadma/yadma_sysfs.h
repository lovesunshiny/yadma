/*****************************************************************************/
/**
*
* @file yadma_sysfs.h
*
* This header file contains user space API and identifiers for procfs.
* MODIFICATION HISTORY:
*
* Ver   Date     Changes
* ----- -------- -------------------------------------------------------
* 1.0   5/15/12  First version
*
******************************************************************************/

#ifndef YADMA_SYSFS_H   /* prevent circular inclusions */
#define YADMA_SYSFS_H   /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/



/************************** Constant Definitions *****************************/



/************************** Function Prototypes ******************************/
void register_sysfs_files(struct kobject *kobj);
void unregister_sysfs_files(struct kobject *kobj);



#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */

