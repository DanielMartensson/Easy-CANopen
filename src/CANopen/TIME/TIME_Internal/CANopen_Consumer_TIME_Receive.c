/*
 * CANopen_Consumer_TIME_Receive.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "TIME_Internal.h"

/* Layers */
#include "TIME_Protocol/TIME_Protocol.h"

void CANopen_Consumer_TIME_Receive_Clock(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Only master can send out the TIME to the other nodes */
	if(node_ID == 0x0)
		CANopen_TIME_Protocol_Consume_Clock(canopen, data);
}
