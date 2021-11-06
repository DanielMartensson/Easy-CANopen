/*
 * CANopen_Consumer_TIME_Receive.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "TIME_Internal.h"

/* Layers */
#include "TIME_Protocol/TIME_Protocol.h"

void CANopen_Consumer_TIME_Receive_Clock(CANopen *canopen, uint8_t data[]){
	CANopen_TIME_Protocol_Consume_Clock(canopen, data);
}
