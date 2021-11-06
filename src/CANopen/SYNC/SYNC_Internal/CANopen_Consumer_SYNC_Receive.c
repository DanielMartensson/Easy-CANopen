/*
 * CANopen_Consumer_SYNC_Receive.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SYNC_Internal.h"

/* Layers */
#include "SYNC_Protocol/SYNC_Protocol.h"

void CANopen_Consumer_SYNC_Receive_Synchronization(CANopen *canopen, uint8_t data[]){
	CANopen_SYNC_Protocol_Consume_Synchronization(canopen, data);
}
