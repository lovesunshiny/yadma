
export KDIR= /lib/modules/$(shell uname -r)/build
#export KDIR=/opt/work/linux-3.5.0-17 
export YADMA_PATH=$(ROOTDIR)/yadma
export ADI_PATH=$(ROOTDIR)/yadma/ad9361
export INSMOD=/sbin/insmod
export RMMOD=/sbin/rmmod
export RM=/bin/rm
export MKNOD_CMD=/bin/mknod
export DMA_STATS_FILE=yadma_stat
export RAW0_FILE_NAME=yadma0
export RAW1_FILE_NAME=yadma1
export DMA_DRIVER_NAME=yadma.ko
export SLEEP_TIME=1

MKNOD = `awk '/$(DMA_STATS_FILE)/ {print $$1}' /proc/devices`
MKNOD0 =`awk '/$(RAW0_FILE_NAME)/ {print $$1}' /proc/devices`
MKNOD1 =`awk '/$(RAW1_FILE_NAME)/ {print $$1}' /proc/devices`

define compile_performance_driver
	echo Compiling Performance Driver
	$(MAKE) -C $(YADMA_PATH)
endef

define clean_performance_driver
	echo Cleaning Performance Driver
	$(MAKE) -C $(YADMA_PATH) clean
	$(MAKE) -C $(ADI_PATH) clean
endef

define insert_performance_driver
	echo Inserting Performance Driver
	$(INSMOD) $(YADMA_PATH)/$(DMA_DRIVER_NAME); sleep $(SLEEP_TIME)
	echo $(MKNOD_CMD)
	echo $(DMA_STATS_FILE)
	echo $(MKNOD)
	$(MKNOD_CMD) /dev/$(DMA_STATS_FILE) c $(MKNOD) 0
endef

define remove_performance_driver
	echo Removing Performance Driver
	$(RMMOD) $(DMA_DRIVER_NAME)
endef
