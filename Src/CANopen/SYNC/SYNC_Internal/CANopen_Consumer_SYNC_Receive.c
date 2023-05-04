/*
 * CANopen_Consumer_SYNC_Receive.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SYNC_Internal.h"

/* Layers */
#include "SYNC_Protocol/SYNC_Protocol.h"

void CANopen_Consumer_SYNC_Receive_Synchronization(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Only master can send out the SYNC to the other nodes */
	if(node_ID == 0x0)
		CANopen_SYNC_Protocol_Consume_Synchronization(canopen, data);
}
