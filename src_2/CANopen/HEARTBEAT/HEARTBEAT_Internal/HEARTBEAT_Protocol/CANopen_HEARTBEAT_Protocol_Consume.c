/*
 * CANopen_HEARTBEAT_Protocol_Consume.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT_Protocol.h"

/* Layers */
#include "../../../../Hardware/Hardware.h"

void CANopen_HEARTBEAT_Protocol_Consume_Status(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Save the response */
	canopen->slave.nmt.from_node_status_operational = data[0] & 0x7F;
	canopen->slave.nmt.from_node_toggle = data[0] >> 7;
	canopen->slave.nmt.from_node_ID = node_ID;

	/* Save the heartbeat message from the producer node */
	uint16_t heartbeat_time_difference = 0x7F & canopen->od_communication.consumer_heartbeat_time[node_ID];
	canopen->od_communication.consumer_heartbeat_time[node_ID] = (node_ID << 16) | (Hardware_Time_Get_Tick() - heartbeat_time_difference);
}
