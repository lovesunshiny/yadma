/*
 * paraCal.c
 *
 *  Created on: 2014-3-25
 *      Author: zgt
 */

//#include "stdlib.h"
//#include "math.h"
//#include "ad9361.h"
//#include "util.h"
#include "paraComm.h"
#include "paraCal.h"

#define TEMP_FDD_MODE 1
#define TEMP_TDD_MODE 0

struct paraRlt paraCal(int _duplexMode, uint64_t _rx_f, uint64_t _tx_f, uint64_t _ref_f, uint64_t _vco_f_l, uint64_t _vco_f_h)
{
	struct paraRlt r;

	const struct SynthLUT *table = 0;
	int _fInd;

	if(TEMP_FDD_MODE == _duplexMode){
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

	r.reg_231 = rx_n_int&0xff;
	r.reg_232 = rx_n_int>>8;
	//long long rx_n_frac = (long long)round(8388593*(rxpll_freq/_ref_f-rx_n_int));
	//uint64_t rx_n_frac = 0x7FFFF1*rxpll_freq/_ref_f-0x7FFFF1*rx_n_int + 0.5;
	uint64_t rx_n_frac = DIV_ROUND_UP( (rxpll_freq*0x7FFFF1*0x80)/_ref_f - (rx_n_int*0x7FFFF1*0x80), 0x80 );
	//rx_n_frac_hex = dec2hex(rx_n_frac);
	r.reg_233 = rx_n_frac&0xff;
	r.reg_234 = (rx_n_frac>>8)&0xff;
	r.reg_235 = (rx_n_frac>>16)&0xff;

	//double tx_vco_div = pow(2.0, floor(log2(_vco_f_h/_tx_f)));
	//int tx_vco_div_reg = (int)floor(log2(_vco_f_h/_tx_f))-1;
	uint64_t tx_vco_div = 1<<(ilog2(_vco_f_h/_tx_f));
	uint64_t tx_vco_div_reg = ilog2(_vco_f_h/_tx_f) - 1;
	r.reg_005 = (tx_vco_div_reg<<4) + rx_vco_div_reg;
	uint64_t txpll_freq = _tx_f*tx_vco_div;
	uint64_t tx_n_int = txpll_freq/_ref_f;
	//tx_n_int_hex = dec2hex(tx_n_int);
	r.reg_271 = tx_n_int&0xff;
	r.reg_272 = tx_n_int>>8;
	//uint64_t tx_n_frac = 0x7FFFF1*(txpll_freq/_ref_f-tx_n_int) + 0.5;
	uint64_t tx_n_frac = DIV_ROUND_UP( (txpll_freq*0x7FFFF1*0x80)/_ref_f - (tx_n_int*0x7FFFF1*0x80), 0x80 );

	//tx_n_frac_hex = dec2hex(tx_n_frac);
	r.reg_273 = tx_n_frac&0xff;
	r.reg_274 = (tx_n_frac>>8)&0xff;
	r.reg_275 = (tx_n_frac>>16)&0xff;

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

	r.reg_23a = 0x40 + vco_output_level;
	r.reg_239 = 0xC0 + vco_varator;
	r.reg_242 = (vco_bias_tcf<<3)+vco_bias_ref;
	r.reg_238 = vco_cal_offset<<3;
	r.reg_245 = 0x0;
	r.reg_251 = vco_varator_reference;
	r.reg_250 = 0x70;
	r.reg_23b = 0x80+charge_pump_current;
	r.reg_23e = (loop_filter_c2<<4)+loop_filter_c1;
	r.reg_23f = (loop_filer_r1<<4)+loop_filter_c3;
	r.reg_240 = loop_filter_r3;

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
	vco_bias_ref = table[tx_index].VCO_Bias_R
	ef;
	vco_bias_tcf = table[tx_index].VCO_Bias_Tcf;
	vco_cal_offset = table[tx_index].VCO_Cal_Offset;
	vco_varator_reference = table[tx_index].VCO_Varactor_Reference;
	charge_pump_current = table[tx_index].Charge_Pump_Current;
	loop_filter_c2 = table[tx_index].LF_C2;
	loop_filter_c1 = table[tx_index].LF_C1;
	loop_filer_r1 = table[tx_index].LF_R1;
	loop_filter_c3 = table[tx_index].LF_C3;
	loop_filter_r3 = table[tx_index].LF_R3;

	r.reg_27a = 0x40+vco_output_level;
	r.reg_279 = 0xC0+vco_varator;
	r.reg_282 = (vco_bias_tcf<<3)+vco_bias_ref;
	r.reg_278 = (vco_cal_offset<<3);
	r.reg_285 = 0x0;
	r.reg_291 = vco_varator_reference;
	r.reg_290 = 0x70;
	r.reg_27b = 0x80 + charge_pump_current;
	r.reg_27e = (loop_filter_c2<<4)+loop_filter_c1;
	r.reg_27f = (loop_filer_r1<<4)+loop_filter_c3;
	r.reg_280 = loop_filter_r3;

	return r;
}

/***************************************************************************//**
 * @brief ilog2
*******************************************************************************/
int32_t ilog2(int32_t x)
{
	int32_t A = !(!(x >> 16));
	int32_t count = 0;
	int32_t x_copy = x;

	count = count + (A << 4);

	x_copy = (((~A + 1) & (x >> 16)) + (~(~A + 1) & x));

	A = !(!(x_copy >> 8));
	count = count + (A << 3);
	x_copy = (((~A + 1) & (x_copy >> 8)) + (~(~A + 1) & x_copy));

	A = !(!(x_copy >> 4));
	count = count + (A << 2);
	x_copy = (((~A + 1) & (x_copy >> 4)) + (~(~A + 1) & x_copy));

	A = !(!(x_copy >> 2));
	count = count + (A << 1);
	x_copy = (((~A + 1) & (x_copy >> 2)) + (~(~A + 1) & x_copy));

	A = !(!(x_copy >> 1));
	count = count + A;

	return count;
}
