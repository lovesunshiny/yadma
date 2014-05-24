#ifndef ADI_COMMON_H
#define ADI_COMMON_H

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

#include "yadma.h"
#include "yadma_reg.h"
#include "yadma_knl.h"
#include "adi_common.h"
#include "ad9361.h"
#include "util.h"

//TODO: replace with correct value
#define BBPLL 1
#define RXCP  2
#define TXCP  3
#define RXFILTER 4
#define TXFILTER 5
#define BBDC 6
#define RFDC 7
#define TXQUAD 8

#define MAX_POLL       10

#define ADI_TX_CH   0
#define ADI_RX_CH   1

#define ADI_FDD_MODE 0
#define ADI_TDD_MODE 1
#define ADI_TDD_USE_FDD 2
#define DEFAULT_DUPLEX_MODE ADI_FDD_MODE

#define ADI_VCO_LOW_FREQ        3e9
#define ADI_VCO_HIGH_FREQ       12e9

struct paraRlt{
	uint8_t reg_231;
	uint8_t reg_232;
	uint8_t reg_233;
	uint8_t reg_234;
	uint8_t reg_235;
	uint8_t reg_005;

	uint8_t reg_271;
	uint8_t reg_272;
	uint8_t reg_273;
	uint8_t reg_274;
	uint8_t reg_275;

	uint8_t reg_23a;
	uint8_t reg_239;
	uint8_t reg_242;
	uint8_t reg_238;
	uint8_t reg_245;
	uint8_t reg_251;
	uint8_t reg_250;
	uint8_t reg_23b;
	uint8_t reg_23e;
	uint8_t reg_23f;
	uint8_t reg_240;

	uint8_t reg_27a;
	uint8_t reg_279;
	uint8_t reg_282;
	uint8_t reg_278;
	uint8_t reg_285;
	uint8_t reg_291;
	uint8_t reg_290;
	uint8_t reg_27b;
	uint8_t reg_27e;
	uint8_t reg_27f;
	uint8_t reg_280;
};

void paraCal(int _duplexMode, uint64_t _rx_f, uint64_t _tx_f, uint64_t _ref_f, uint64_t _vco_f_l, uint64_t _vco_f_h, struct paraRlt* par);

void AD9362_Config(void);
void RESET_FPGA(void);
void RESET_DUT(void);
// Set ADI FPGA SPI to 20Mhz
// BlockWrite(2,6);
// SPIWrite(0x3DF,0x01);
void BlockWrite(u32 reg, u32 freq);
void SPIWrite(u32 reg, u32 val);
u32 SPIRead(u32 reg);
int ReadPartNumber(void);
void REFCLK_Scale(double freq, double a, double b);
void WAIT(int ms);
void WAIT_CALDONE(int lock,int ms);
int32_t set_rfpll_rate(int source, uint32_t rate,	uint32_t parent_rate);
int32_t config_rfpll_vco(int mode, int ch, uint64_t vco_freq, uint32_t ref_clk);

void ad9362_tx_att(int att1, int att2);
void ad9362_rx_gain(int gain1, int gain2);

void ad9362_rx_freq(const struct paraRlt* par);
void ad9362_tx_freq(const struct paraRlt* par);
#endif
