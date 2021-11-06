/*
 * Enum_Mode_Codes.h
 *
 *  Created on: 10 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_GLOBAL_ENUMS_ENUM_MODE_CODES_H_
#define CANOPEN_GLOBAL_ENUMS_ENUM_MODE_CODES_H_

enum{
	MODE_WAITING = 0x0,
	MODE_CONFIGURATION = 0x1,
	MODE_READ = 0x40,
	MODE_WRITE = 0x0
};

#endif /* CANOPEN_GLOBAL_ENUMS_ENUM_MODE_CODES_H_ */
