/***************************************************************************//**
 *   @file   util.h
 *   @brief  Header file of Util driver.
 *   @author DBogdan (dragos.bogdan@analog.com)
********************************************************************************
 * Copyright 2013(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/
#ifndef __NO_OS_PORT_H__
#define __NO_OS_PORT_H__

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include <linux/pci.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/version.h>
#include <linux/ethtool.h>
#include <linux/netlink.h>
#include <net/sock.h>

#include <linux/mm.h>
#include <linux/spinlock.h>
#include <linux/pagemap.h>
#include <asm/scatterlist.h>
#include <linux/time.h>

#include <linux/delay.h>
#include <linux/list.h>
#include <linux/device.h>
#include <asm/div64.h>

#include "common.h"
#include "ad9361.h"

struct spi_device {
    struct device dev;
};

struct axiadc_state {
};

struct axiadc_chip_info {
	char		*name;
	int32_t		num_channels;
	uint32_t	max_rate;
};

struct axiadc_converter {
	struct axiadc_chip_info	*chip_info;
};

/******************************************************************************/
/************************ Functions Declarations ******************************/
/******************************************************************************/
int32_t clk_prepare_enable(struct clk *clk);
uint32_t clk_get_rate(struct ad9361_rf_phy *phy,
					  struct refclk_scale *clk_priv);
int32_t clk_set_rate(struct ad9361_rf_phy *phy,
					 struct refclk_scale *clk_priv,
					 uint32_t rate);
uint64_t util_do_div(uint64_t* n,
				uint64_t base);

#define CLK_IGNORE_UNUSED						(1 << 3)
#define CLK_GET_RATE_NOCACHE					(1 << 6)

#endif
