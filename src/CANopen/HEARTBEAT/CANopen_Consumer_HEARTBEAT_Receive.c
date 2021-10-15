/*
 * CANopen_Consumer_HEARTBEAT_Receive.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT.h"

void CANopen_Consumer_HEARTBEAT_Receive_Status_Operation(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	canopen->consumer.heartbeat.from_node_ID = node_ID;
	canopen->consumer.heartbeat.status_operational = data[0] & 0x7F;
	canopen->consumer.heartbeat.toggle_heartbeat = data[0] >> 7;
}


