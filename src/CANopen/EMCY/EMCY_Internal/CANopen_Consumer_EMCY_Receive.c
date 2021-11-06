/*
 * CANopen_Consumer_EMCY_Receive.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY_Internal.h"

/* Layers */
#include "EMCY_Protocol/EMCY_Protocol.h"

void CANopen_Consumer_EMCY_Receive_Error(CANopen *canopen, uint8_t node_ID, uint8_t data[]) {
	CANopen_EMCY_Protocol_Consume_Error(canopen, node_ID, data);
}
