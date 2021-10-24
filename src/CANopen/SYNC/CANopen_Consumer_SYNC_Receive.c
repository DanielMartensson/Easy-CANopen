/*
 * CANopen_Consumer_SYNC_Receive.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SYNC.h"

void CANopen_Consumer_SYNC_Receive_Synchronization(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Check if the correct consumer we are talking to */
	if(node_ID == canopen->slave.lss.this_node_ID){
		/* Get the counting value */
		uint8_t counter = data[0];

	}
}
