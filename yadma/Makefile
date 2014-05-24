#obj-m := xdma_base.c
#obj-m += xdma.o
#obj-m += xdma_bdring.o
#obj-m += xdma_user.o
#obj-m := xdma_k7.o
#xdma_k7-objs :=  xdma_base.o xdma.o xdma_bdring.o xdma_user.o

obj-m := yadma.o
yadma-objs := yadma_knl.o yadma_proc.o yadma_sysfs.o adi_config.o adi_common.o
yadma-objs += ad9361/ad9361_api.o \
		ad9361/ad9361.o \
		ad9361/adc_core.o \
		ad9361/dac_core.o \
		ad9361/platform.o \
		ad9361/util.o

EXTRA_CFLAGS += -g -Os -DDEBUG_YADMA -DZynq_PCIeTRD -DX86_PC -DNWLDMA -DXENV_LINUX -DUSE_IO_MACROS -DXLITTLE_ENDIAN -DPM_SUPPORT -DPCI_LINUX -I $(YADMA_PATH) -I $(ADI_PATH) -fno-tree-scev-cprop

# Add the following to EXTRA_CFLAGS to enable interrupt mode
#-DTH_BH_ISR

all:
	$(MAKE) $(CFLAGS) -C $(KDIR) SUBDIRS=$(PWD)/yadma 
	#gcc -g -O0 -shared -fPIC -Wl,-soname,libyadma.so -o libyadma.so yadma_user.c
	gcc -g -c yadma_user.c
	gcc -g -c yadma_api.c
	gcc -g -c hexdump_user.c
	gcc -g -c yadma_demo.c
	gcc -g -c yadma_api_demo.c
	gcc  yadma_demo.o yadma_user.o hexdump_user.o yadma_api.o -o demo -lrt
	gcc  yadma_api_demo.o yadma_user.o hexdump_user.o yadma_api.o -o capture -lrt
	
clean: 
	   rm -rf *.o *.ko *.mod.* .c* .t* .xdma* .*.cmd *.o .tmp* *.symvers modules.order *.so demo

# LOGGING: ---------------------------------------------------------------
# Add to EXTRA_CFLAGS, based on the logging level desired:
# -DDEBUG_NORMAL: To enable normal logging levels 
# -DDEBUG_VERBOSE: To enable verbose logging levels 
