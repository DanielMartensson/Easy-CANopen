/*
 * CANopen_Consumer_TIME_Receive.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "TIME_Internal.h"

void CANopen_Consumer_TIME_Receive_Clock(CANopen *canopen, uint8_t data[]){
	canopen->slave.time.milliseconds_since_midnight = (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
	canopen->slave.time.days_since_1_janunary_1984 = (data[5] << 8) | data[4];
}
