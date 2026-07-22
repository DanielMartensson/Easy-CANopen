/*
 * CANopen_TIME_Protocol_Consume.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "TIME_Protocol.h"

void CANopen_TIME_Protocol_Consume_Clock(CANopen *canopen, uint8_t data[]){
	canopen->slave.time.milliseconds = (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
	canopen->slave.time.days = (data[5] << 8) | data[4];
}
