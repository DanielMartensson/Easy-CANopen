/*
 * CANopen_Consumer_HEARTBEAT_Receive.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT.h"

/* Enums */
#include "../Global_Enums/Enum_Status_Codes.h"

void CANopen_Consumer_HEARTBEAT_Receive_Heartbeat(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Check if heartbeat is enabled */
	if(!canopen->consumer.heartbeat.is_enabled)
		return;

	/* Save the heartbeat message from the producer node */
	canopen->consumer.heartbeat.from_node_ID = node_ID;
	canopen->consumer.heartbeat.status_operational = data[0] & 0x7F;
	canopen->consumer.heartbeat.toggle = data[0] >> 7;
}


