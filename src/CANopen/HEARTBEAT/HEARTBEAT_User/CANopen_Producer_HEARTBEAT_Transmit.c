/*
 * CANopen_Producer_HEARTBEAT_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT_User.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Producer_HEARTBEAT_Transmit_Status(CANopen *canopen){
	/* Check if heartbeat is enabled */
	if(canopen->od_communication.producer_heartbeat_time == 0)
		return;

	/* Create the heartbeat */
	uint8_t data[8] = {0};
	uint8_t node_ID = canopen->slave.this_node_ID;
	CANopen_HEARTBEAT_Protocol_Status_Create(canopen, node_ID, data);

	/* Create the COB ID and send heartbeat */
	uint32_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 7 | node_ID;
	Hardware_CAN_Send_Message(COB_ID, data);
}
