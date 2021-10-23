/*
 * CANopen_Consumer_HEARTBEAT_Receive.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Consumer_HEARTBEAT_Receive_Heartbeat(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Save the heartbeat message from the producer node */
	uint16_t heartbeat_time_difference = 0x7F & canopen->od_communication.consumer_heartbeat_time[node_ID];
	canopen->od_communication.consumer_heartbeat_time[node_ID] = (node_ID << 16) | (Hardware_Time_Get_Tick() - heartbeat_time_difference);

	/* Save for the user: TODO: Hur ska jag spara dessa? */
	canopen->nmt_master.from_node_ID = node_ID;
	canopen->nmt_master.node_status_operation = data[0] & 0x7F;
	canopen->nmt_master.toggle_heartbeat = data[0] >> 7;
}


