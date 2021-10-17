/*
 * Enum_Baudrate_Codes.h
 *
 *  Created on: 9 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_ENUMS_ENUM_BAUDRATE_CODES_H_
#define CANOPEN_ENUMS_ENUM_BAUDRATE_CODES_H_

/* Each baudrate is definied with unit kB/s */
enum{
	/* Table selectors */
	TABLE_SELECTOR_0 = 0x0,

	/* Baud rates table index */
	TABLE_INDEX_0_BAUD_RATE_1000 = 0x0,
	TABLE_INDEX_1_BAUD_RATE_800 = 0x1,
	TABLE_INDEX_2_BAUD_RATE_500 = 0x2,
	TABLE_INDEX_3_BAUD_RATE_250 = 0x3,
	TABLE_INDEX_4_BAUD_RATE_125 = 0x4,
	TABLE_INDEX_5_BAUD_RATE_100 = 0x5,
	TABLE_INDEX_6_BAUD_RATE_50 = 0x6,
	TABLE_INDEX_7_BAUD_RATE_20 = 0x7,
	TABLE_INDEX_8_BAUD_RATE_10 = 0x8,
};

#endif /* CANOPEN_ENUMS_ENUM_BAUDRATE_CODES_H_ */
