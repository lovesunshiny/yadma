
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

void RESET_FPGA(void)
{

}
void RESET_DUT(void)
{

}

// Set ADI FPGA SPI to 20Mhz
// BlockWrite(2,6);
// SPIWrite(0x3DF,0x01);
void BlockWrite(u32 reg, u32 freq)
{
    SPIWrite(reg, freq);
}

void SPIWrite(u32 reg, u32 val)
{
    if(reg > REG_ADI_END_OFFSET-REG_ADI_START_OFFSET) {
        log_verbose("Over the ADI reigster's range %x!\n", reg);
        return -1;
    }
    
    int offset = reg + REG_ADI_START_OFFSET;

    if(yadmaPrivData && offset < yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_len &&
        yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_virt_addr != NULL) {
        yadmaWriteReg(yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_virt_addr, offset, val);
    } else {
        return;
    }

    u32 status, i = 0;
    do {
        i++;
        status = yadmaReadReg(yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_virt_addr, REG_SPI_R_STATUS);
        if(!(status & BIT_SPI_W_BUSY))
            break;

        udelay(100);
    } while (i < MAX_POLL);

    if(i == MAX_POLL) {
        log_verbose("Write: over the ADI poll count.\n");
    }
}

int SPIReadMultileBytes(u32 reg, u32 num)
{
    if(reg > REG_ADI_END_OFFSET-REG_ADI_START_OFFSET) {
        log_verbose("Over the ADI reigster's range %x!\n", reg);
        return -1;
    }

	int start = reg - num;
    if(start < -1 || start > REG_ADI_END_OFFSET -REG_ADI_START_OFFSET) {
        log_verbose("Over the ADI reigster's range (reg = %x, num = %d)!\n", reg, num);
        return -1;
    }

    int offset = reg + REG_ADI_START_OFFSET;

    if(yadmaPrivData && offset < yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_len &&
        yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_virt_addr != NULL) {
        yadmaWriteReg(yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_virt_addr , REG_SPI_R_END_ADDR, reg+1);
        yadmaWriteReg(yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_virt_addr , REG_SPI_R_LENGTH, num);
        yadmaWriteReg(yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_virt_addr , REG_SPI_R_CONTROL, BIT_SPI_REFRESH);
    } else {
        return -1;
    }

    u32 status, i = 0;
    do {
        i++;
        status = yadmaReadReg(yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_virt_addr, REG_SPI_R_STATUS);
        if(!(status & BIT_SPI_R_BUSY))
            break;
        udelay(100);
    } while (i < MAX_POLL);

    int value;
    if(i == MAX_POLL) {
        log_verbose("Read: over the ADI polling count.\n");
        value = -1;
    } else {
        value = 0;
    }
    return value;
}

u32 SPIRead(u32 reg)
{
    u32 value = 0;
    int offset = reg + REG_ADI_START_OFFSET;
    
    if(SPIReadMultileBytes(reg, 2) == 0)
        value = yadmaReadReg(yadmaPrivData->bar_info[BAR_FPGA_CTRL].bar_virt_addr, offset);

    return value;
}

void SPIMaskWrite(u32 reg, u32 mask, u32 val)
{
    u32 cur, offset;
    
    /* Find first 1 */
    offset = ffs(mask);
    cur = SPIRead(reg);
	cur &= ~mask;
	cur |= ((val << offset) & mask);
    SPIWrite(reg, cur);
}

int ReadPartNumber(void)
{

}

void REFCLK_Scale(double freq, double a, double b)
{

}


void WAIT(int ms)
{
	udelay(ms*5000);
}

void WAIT_CALDONE(int lock,int ms)
{
	udelay(ms*5000);
}


/**
 * Initialize the RFPLL VCO.
 * @param mode system working mode
 * @param ch  which chanel to config.
 * @param vco_freq The VCO frequency [Hz].
 * @param ref_clk The reference clock frequency [Hz].
 * @return 0 in case of success
 */
int32_t config_rfpll_vco(int mode, int ch, uint64_t vco_freq, uint32_t ref_clk)
{
	const struct SynthLUT *tab;
	int32_t i = 0;
	uint32_t range, offs = 0;

	range = ad9361_rfvco_tableindex(ref_clk);

	log_verbose("%s : vco_freq %llu : ref_clk %lu : range %d\n",
		"config_rfpll_vco", vco_freq, ref_clk, range);

	util_do_div((&vco_freq), 1000000UL); /* vco_freq in MHz */
	
	if (mode == ADI_FDD_MODE || mode == ADI_TDD_USE_FDD) {
		tab = &SynthLUT_FDD[range][0];
	}
	else {
		tab = &SynthLUT_TDD[range][0];
	}

	if (ch == ADI_TX_CH)
		offs = REG_TX_VCO_OUTPUT - REG_RX_VCO_OUTPUT;

	while ((i < 53) && (tab[i].VCO_MHz > vco_freq)) {
		i++;
		printk("i = %d, VCO_Mhz = %d\n", i, tab[i].VCO_MHz);
	}

	printk("my VCO freq %d Mhz, in table %d MHz : index %d \n", vco_freq, (tab[i].VCO_MHz), i);


	SPIWrite( REG_RX_VCO_OUTPUT + offs,
		VCO_OUTPUT_LEVEL(tab[i].VCO_Output_Level) |
		PORB_VCO_LOGIC);
		
	SPIMaskWrite( REG_RX_ALC_VARACTOR + offs,
		VCO_VARACTOR(~0), tab[i].VCO_Varactor);
		
	SPIWrite( REG_RX_VCO_BIAS_1 + offs,
		VCO_BIAS_REF(tab[i].VCO_Bias_Ref) |
		VCO_BIAS_TCF(tab[i].VCO_Bias_Tcf));

	SPIWrite( REG_RX_FORCE_VCO_TUNE_1 + offs,
		VCO_CAL_OFFSET(tab[i].VCO_Cal_Offset));
	SPIWrite( REG_RX_VCO_VARACTOR_CTRL_1 + offs,
		VCO_VARACTOR_REFERENCE(
		tab[i].VCO_Varactor_Reference));

	SPIWrite( REG_RX_VCO_CAL_REF + offs, VCO_CAL_REF_TCF(0));

	SPIWrite( REG_RX_VCO_VARACTOR_CTRL_0 + offs,
		VCO_VARACTOR_OFFSET(0) |
		VCO_VARACTOR_REFERENCE_TCF(7));

	SPIMaskWrite( REG_RX_CP_CURRENT + offs, CHARGE_PUMP_CURRENT(~0),
		tab[i].Charge_Pump_Current);
	SPIWrite( REG_RX_LOOP_FILTER_1 + offs,
		LOOP_FILTER_C2(tab[i].LF_C2) |
		LOOP_FILTER_C1(tab[i].LF_C1));
	SPIWrite( REG_RX_LOOP_FILTER_2 + offs,
		LOOP_FILTER_R1(tab[i].LF_R1) |
		LOOP_FILTER_C3(tab[i].LF_C3));
	SPIWrite( REG_RX_LOOP_FILTER_3 + offs,
		LOOP_FILTER_R3(tab[i].LF_R3));

	return 0;
}

/**
 * Set the clock rate.
 * @param refclk_scale The refclk_scale structure.
 * @param rate The clock rate.
 * @param parent_rate The parent clock rate.
 * @return vco in case of success, negative error code otherwise.
 */
int32_t set_rfpll_rate(int source, uint32_t rate,	uint32_t parent_rate)
{
	uint64_t vco;
	uint8_t buf[5];
	uint32_t reg, div_mask, lock_reg, fract, integer;
	int32_t vco_div, ret;

	log_verbose("Rate %lu Hz Parent Rate %lu Hz \n", rate, parent_rate);

	ret = ad9361_calc_rfpll_divder(ad9361_from_clk(rate), parent_rate,
		&integer, &fract, &vco_div, &vco);
	if (ret < 0)
		return ret;

	switch (source) {
	case RX_RFPLL:
		reg = REG_RX_FRACT_BYTE_2;
		lock_reg = REG_RX_CP_OVERRANGE_VCO_LOCK;
		div_mask = RX_VCO_DIVIDER(~0);
		break;
	case TX_RFPLL:
		reg = REG_TX_FRACT_BYTE_2;
		lock_reg = REG_TX_CP_OVERRANGE_VCO_LOCK;
		div_mask = TX_VCO_DIVIDER(~0);
		break;
	default:
		return -EINVAL;

	}

	buf[0] = fract >> 16;
	buf[1] = fract >> 8;
	buf[2] = fract & 0xFF;
	buf[3] = integer >> 8;
	buf[4] = integer & 0xFF;
	
	int i;
	for(i = 0; i < 5; i++) {
		SPIWrite(reg+i, buf[i]);
	}
	SPIMaskWrite(REG_RFPLL_DIVIDERS, div_mask, vco_div);
	

	/* check all is done */
	int status; 
	i = 0;
    do {
        i++;
        status = SPIRead(lock_reg);
        if(!(status & VCO_LOCK))
            break;
        udelay(100);
    } while (i < MAX_POLL);

    int value;
    if(i == MAX_POLL) {
        log_verbose("Read: over the ADI polling count.\n");
        value = -1;
    } else {
        value = vco;
    }
    
	return vco;
}

void paraCal(int _duplexMode, uint64_t _rx_f, uint64_t _tx_f, uint64_t _ref_f, uint64_t _vco_f_l, uint64_t _vco_f_h, struct paraRlt* par)
{

	const struct SynthLUT *table = 0;
	int _fInd;

	if(ADI_FDD_MODE == _duplexMode){
	    if ((_ref_f >= 35e6) && (_ref_f < 50e6))		_fInd = 0;
	    else if ((_ref_f >= 50e6) && (_ref_f < 70e6))	_fInd = 1;
	    else if	((_ref_f >= 70e6) && (_ref_f < 80e6))	_fInd = 2;

	    table = &(SynthLUT_FDD[_fInd][0]);
	}
	else{
	    if ((_ref_f >= 35e6) && (_ref_f < 50e6))		_fInd = 0;
	    else if ((_ref_f >= 50e6) && (_ref_f < 70e6))	_fInd = 1;
	    else if ((_ref_f >= 70e6) && (_ref_f < 80e6))	_fInd = 2;

	    table = &(SynthLUT_TDD[_fInd][0]);
	}

	//double rx_vco_div = pow(2.0,floor(log2(_vco_f_h/_rx_f)));
	//double rx_vco_div_reg = floor(log2(_vco_f_h/_rx_f))-1;
	//double rxpll_freq = _rx_f*rx_vco_div;
	//int rx_n_int = (int)floor(rxpll_freq/_ref_f);
	//rx_n_int_hex = dec2hex(rx_n_int);
	uint64_t  rx_vco_div = 1<<(ilog2(_vco_f_h/_rx_f));
	uint64_t rx_vco_div_reg = ilog2(_vco_f_h/_rx_f) - 1;
	uint64_t rxpll_freq = _rx_f*rx_vco_div;
	uint64_t rx_n_int = rxpll_freq/_ref_f;

	par->reg_231 = rx_n_int&0xff;
	par->reg_232 = rx_n_int>>8;
	//long long rx_n_frac = (long long)round(8388593*(rxpll_freq/_ref_f-rx_n_int));
	//uint64_t rx_n_frac = 0x7FFFF1*rxpll_freq/_ref_f-0x7FFFF1*rx_n_int + 0.5;
	uint64_t rx_n_frac = DIV_ROUND_UP( (rxpll_freq*0x7FFFF1*0x80)/_ref_f - (rx_n_int*0x7FFFF1*0x80), 0x80 );
	//rx_n_frac_hex = dec2hex(rx_n_frac);
	par->reg_233 = rx_n_frac&0xff;
	par->reg_234 = (rx_n_frac>>8)&0xff;
	par->reg_235 = (rx_n_frac>>16)&0xff;

	//double tx_vco_div = pow(2.0, floor(log2(_vco_f_h/_tx_f)));
	//int tx_vco_div_reg = (int)floor(log2(_vco_f_h/_tx_f))-1;
	uint64_t tx_vco_div = 1<<(ilog2(_vco_f_h/_tx_f));
	uint64_t tx_vco_div_reg = ilog2(_vco_f_h/_tx_f) - 1;
	par->reg_005 = (tx_vco_div_reg<<4) + rx_vco_div_reg;
	uint64_t txpll_freq = _tx_f*tx_vco_div;
	uint64_t tx_n_int = txpll_freq/_ref_f;
	//tx_n_int_hex = dec2hex(tx_n_int);
	par->reg_271 = tx_n_int&0xff;
	par->reg_272 = tx_n_int>>8;
	//uint64_t tx_n_frac = 0x7FFFF1*(txpll_freq/_ref_f-tx_n_int) + 0.5;
	uint64_t tx_n_frac = DIV_ROUND_UP( (txpll_freq*0x7FFFF1*0x80)/_ref_f - (tx_n_int*0x7FFFF1*0x80), 0x80 );

	//tx_n_frac_hex = dec2hex(tx_n_frac);
	par->reg_273 = tx_n_frac&0xff;
	par->reg_274 = (tx_n_frac>>8)&0xff;
	par->reg_275 = (tx_n_frac>>16)&0xff;

	// Setup RX Synthesizer
	int rx_index=0;
	{
		struct SynthLUT *tab = /*const_cast<SynthLUT *>*/(table);
		//ALERT: We use the property of descent order of table
		for(rx_index=0;rx_index<SYNTH_LUT_SIZE;rx_index++){
			double _delt = rxpll_freq - tab->VCO_MHz*1.0e6;
			if(_delt >= 0 )	break;
			tab += 1;
		}
	}

	uint8_t vco_output_level = table[rx_index].VCO_Output_Level;
	uint8_t vco_varator = table[rx_index].VCO_Varactor;
	uint8_t vco_bias_ref = table[rx_index].VCO_Bias_Ref;
	uint8_t vco_bias_tcf = table[rx_index].VCO_Bias_Tcf;
	uint8_t vco_cal_offset = table[rx_index].VCO_Cal_Offset;
	uint8_t vco_varator_reference = table[rx_index].VCO_Varactor_Reference;
	uint8_t charge_pump_current = table[rx_index].Charge_Pump_Current;
	uint8_t loop_filter_c2 = table[rx_index].LF_C2;
	uint8_t loop_filter_c1 = table[rx_index].LF_C1;
	uint8_t loop_filer_r1 = table[rx_index].LF_R1;
	uint8_t loop_filter_c3 = table[rx_index].LF_C3;
	uint8_t loop_filter_r3 = table[rx_index].LF_R3;

	par->reg_23a = 0x40 + vco_output_level;
	par->reg_239 = 0xC0 + vco_varator;
	par->reg_242 = (vco_bias_tcf<<3)+vco_bias_ref;
	par->reg_238 = vco_cal_offset<<3;
	par->reg_245 = 0x0;
	par->reg_251 = vco_varator_reference;
	par->reg_250 = 0x70;
	par->reg_23b = 0x80+charge_pump_current;
	par->reg_23e = (loop_filter_c2<<4)+loop_filter_c1;
	par->reg_23f = (loop_filer_r1<<4)+loop_filter_c3;
	par->reg_240 = loop_filter_r3;

	// Setup TX Synthesizer
	int tx_index=0;
	{
		struct SynthLUT *tab = /*const_cast<SynthLUT *>*/(table);
		//ALERT: We use the property of descent order of table
		for(tx_index=0;tx_index<SYNTH_LUT_SIZE;tx_index++){
			double _delt = rxpll_freq - tab->VCO_MHz*1.0e6;
			if(_delt >= 0 )	break;
			tab += 1;
		}
	}

	vco_output_level = table[tx_index].VCO_Output_Level;
	vco_varator = table[tx_index].VCO_Varactor;
	vco_bias_ref = table[tx_index].VCO_Bias_Ref;
	vco_bias_tcf = table[tx_index].VCO_Bias_Tcf;
	vco_cal_offset = table[tx_index].VCO_Cal_Offset;
	vco_varator_reference = table[tx_index].VCO_Varactor_Reference;
	charge_pump_current = table[tx_index].Charge_Pump_Current;
	loop_filter_c2 = table[tx_index].LF_C2;
	loop_filter_c1 = table[tx_index].LF_C1;
	loop_filer_r1 = table[tx_index].LF_R1;
	loop_filter_c3 = table[tx_index].LF_C3;
	loop_filter_r3 = table[tx_index].LF_R3;

	par->reg_27a = 0x40+vco_output_level;
	par->reg_279 = 0xC0+vco_varator;
	par->reg_282 = (vco_bias_tcf<<3)+vco_bias_ref;
	par->reg_278 = (vco_cal_offset<<3);
	par->reg_285 = 0x0;
	par->reg_291 = vco_varator_reference;
	par->reg_290 = 0x70;
	par->reg_27b = 0x80 + charge_pump_current;
	par->reg_27e = (loop_filter_c2<<4)+loop_filter_c1;
	par->reg_27f = (loop_filer_r1<<4)+loop_filter_c3;
	par->reg_280 = loop_filter_r3;
}


void ad9362_rx_freq(const struct paraRlt* par)	// frequency in KHz
{
    //************************************************************
    // Setup Synthesizer
    //************************************************************
    SPIWrite(0x23A, par->reg_23a);	// Set VCO Output level[3:0]
    SPIWrite(0x239, par->reg_239);	// Set Init ALC Value[3:0] and VCO Varactor[3:0]
    SPIWrite(0x242, par->reg_242);	// Set VCO Bias Tcf[1:0] and VCO Bias Ref[2:0]
    SPIWrite(0x238, par->reg_238);	// Set VCO Cal Offset[3:0]
    SPIWrite(0x245, par->reg_245);	// Set VCO Cal Ref Tcf[2:0]
    SPIWrite(0x251, par->reg_251);	// Set VCO Varactor Reference[3:0]
    SPIWrite(0x250, par->reg_250);	// Set VCO Varactor Ref Tcf[2:0] and VCO Varactor Offset[3:0]
    SPIWrite(0x23B, par->reg_23b);	// Set Synth Loop Filter charge pump current (Icp)
    SPIWrite(0x23E, par->reg_23e);	// Set Synth Loop Filter C2 and C1
    SPIWrite(0x23F, par->reg_23f);	// Set Synth Loop Filter  R1 and C3
    SPIWrite(0x240, par->reg_240);	// Set Synth Loop Filter R3

    SPIWrite(0x233, par->reg_233);	// Write Rx Synth Fractional Freq Word[7:0]
    SPIWrite(0x234, par->reg_234);	// Write Rx Synth Fractional Freq Word[15:8]
    SPIWrite(0x235, par->reg_235);	// Write Rx Synth Fractional Freq Word[22:16]
    SPIWrite(0x232, par->reg_232);	// Write Rx Synth Integer Freq Word[10:8]
    SPIWrite(0x231, par->reg_231);	// Write Rx Synth Integer Freq Word[7:0]
    SPIWrite(0x005, par->reg_005);	// Set LO divider setting


	/* check all is done */
	int status; 
	int i = 0;
    do {
        i++;
        status = SPIRead(0x247);	// Check RX RF PLL lock status (0x247[1]==1 is locked)
        if(!(status & 0x2))
            break;
        udelay(100);
    } while (i < MAX_POLL);

    if(i == MAX_POLL) {
        log_verbose("Read: over the ADI polling count.\n");
    } else {
        log_verbose("RX RF PLL Locked.\n");
    }
}

void ad9362_tx_freq(const struct paraRlt* par)	//frequency in KHz
{
    //************************************************************
    // Setup Synthesizer
    //************************************************************
    SPIWrite(0x27A,par->reg_27a);	// Set VCO Output level[3:0]
    SPIWrite(0x279,par->reg_279);	// Set Init ALC Value[3:0] and VCO Varactor[3:0]
    SPIWrite(0x282,par->reg_282);	// Set VCO Bias Tcf[1:0] and VCO Bias Ref[2:0]
    SPIWrite(0x278,par->reg_278);	// Set VCO Cal Offset[3:0]
    SPIWrite(0x285,par->reg_285);	// Set VCO Cal Ref Tcf[2:0]
    SPIWrite(0x291,par->reg_291);	// Set VCO Varactor Reference[3:0]
    SPIWrite(0x290,par->reg_290);	// Set VCO Varactor Ref Tcf[2:0] and VCO Varactor Offset[3:0]
    SPIWrite(0x27B,par->reg_27b);	// Set Synth Loop Filter charge pump current (Icp)
    SPIWrite(0x27E,par->reg_27e);	// Set Synth Loop Filter C2 and C1
    SPIWrite(0x27F,par->reg_27f);	// Set Synth Loop Filter  R1 and C3
    SPIWrite(0x280,par->reg_280);	// Set Synth Loop Filter R3

    SPIWrite(0x273,par->reg_273);	// Write Tx Synth Fractional Freq Word[7:0]
    SPIWrite(0x274,par->reg_274);	// Write Tx Synth Fractional Freq Word[15:8]
    SPIWrite(0x275,par->reg_275);	// Write Tx Synth Fractional Freq Word[22:16]
    SPIWrite(0x272,par->reg_272);	// Write Tx Synth Integer Freq Word[10:8]
    SPIWrite(0x271,par->reg_271);	// Write Tx Synth Integer Freq Word[7:0] (starts VCO cal)
    SPIWrite(0x005,par->reg_005);	// Set LO divider setting

	/* check all is done */
	int status; 
	int i = 0;
    do {
        i++;
        status = SPIRead(0x287);	// Check TX RF PLL lock status (0x287[1]==1 is locked)
        if(!(status & 0x2))
            break;
        udelay(100);
    } while (i < MAX_POLL);

    if(i == MAX_POLL) {
        log_verbose("Read: over the ADI polling count.\n");
    } else {
        log_verbose("TX RF PLL Locked.\n");
    }

}

void ad9362_rx_gain(int gain1, int gain2)	//RX Gain in dB, Min = 0, Max = 76; gain1 for Channel 1; gain2 for Channel 2; SPI gain mode
{
	//************************************************************
    // Setup Rx Manual Gain Registers
    //************************************************************

    SPIWrite(0x109,gain1);	// Rx1 Full/LMT Gain Index 76dB

    SPIWrite(0x10C,gain2);	// Rx2 Full/LMT Gain 76dB

}
void ad9362_trx_channel(int rx_channel, int tx_channel)
{
	
	if (tx_channel == 1 && rx_channel == 1)
	{
		SPIWrite(0x004,0x03);
	}
	else if (tx_channel == 1 && rx_channel == 2)
	{
		SPIWrite(0x004,0x0C);
	}
	else if (tx_channel == 1 && rx_channel == 3)
	{
		SPIWrite(0x004,0x30);
	}
	else if (tx_channel == 2 && rx_channel == 1)
	{
		SPIWrite(0x004,0x43);
	}
	else if (tx_channel == 2 && rx_channel == 2)
	{
		SPIWrite(0x004,0x4C);
	}
	else if (tx_channel == 2 && rx_channel == 3)
	{
		SPIWrite(0x004,0x70);
	}
	return;
}


void ad9362_tx_att(int att1, int att2)	//TX Attenuation in 0.25dB, Min = 0, Max = 359; att1 for channel 1; att2 for channel 2; SPI gain mode
{
	unsigned char buf1[2]={0};
	unsigned char buf2[2]={0};	

	buf1[1] = (att1 & 0xFF00) >> 8;
	buf1[0] = (att1 & 0xFF);
	buf2[1] = (att2 & 0xFF00) >> 8;
	buf2[0] = (att2 & 0xFF);

//	SPIWrite(0x07C,0x40);	//chenzhiwei	FDD Manuual Immediately Update TPC Atten

	SPIWrite(0x073,buf1[0]);
	SPIWrite(0x074,buf1[1]);
	SPIWrite(0x075,buf2[0]);
	SPIWrite(0x076,buf2[1]);

	SPIWrite(0x07C,0x40);	//chenzhiwei	FDD Manuual Immediately Update TPC Atten
}
