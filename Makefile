#
#	Makefile for Xilinx Zynq-7 PCIe Targeted Reference Design
#

export ROOTDIR=$(shell pwd)
include $(ROOTDIR)/include.mk

all::
	    @$(call compile_performance_driver)
	    @echo "***** Driver Compiled *****"

clean::
	    @$(call clean_performance_driver)
	    @echo "***** Driver Cleaned *****"

insert:: 
	    @$(call insert_performance_driver)
	    @echo "***** Driver Loaded *****"

remove::
	    @$(call remove_performance_driver)
	    @echo "***** Driver Unloaded *****"

