/*
 * CANopen_Consumer_SYNC_Receive.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SYNC.h"

void CANopen_Consumer_SYNC_Receive_Synchronization(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	canopen->from_other_node.consumer.sync.counter = data[0];
	canopen->from_other_node.consumer.sync.from_node_ID = node_ID;
}
