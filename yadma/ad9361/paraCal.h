/*
 * paraCal.h
 *
 *  Created on: 2014-3-25
 *      Author: zgt
 */

#ifndef PARACAL_H_
#define PARACAL_H_

//#include "stdint.h"

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

struct paraRlt paraCal(int _duplexMode, uint64_t _rx_f, uint64_t _tx_f, uint64_t _ref_f, uint64_t _vco_f_l, uint64_t _vco_f_h);
int32_t ilog2(int32_t x);

#endif /* PARACAL_H_ */
