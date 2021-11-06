/*
 * CANopen_Consumer_HEARTBEAT_Receive.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT_Internal.h"

/* Layers */
#include "HEARTBEAT_Protocol/HEARTBEAT_Protocol.h"

void CANopen_Consumer_HEARTBEAT_Receive_Status(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	CANopen_HEARTBEAT_Protocol_Consume_Status(canopen, node_ID, data);
}
