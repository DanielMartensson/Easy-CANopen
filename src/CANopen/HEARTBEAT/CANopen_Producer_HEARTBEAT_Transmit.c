/*
 * CANopen_Producer_HEARTBEAT_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Producer_HEARTBEAT_Transmit(CANopen *canopen){
	/* Check if heartbeat is enabled */
	if(canopen->od_communication.producer_heartbeat_time == 0)
		return;

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 7 | canopen->slave.this_node_ID;

	/* Get toggle */
	canopen->slave.nmt.toggle = canopen->slave.nmt.toggle == TOGGLE_NMT_0 ? TOGGLE_NMT_1 : TOGGLE_NMT_0;

	/* Send the heartbeat message */
	uint8_t data[8] = {0};
	data[0] = (canopen->slave.nmt.toggle << 7) | canopen->slave.nmt.status_operational;
	Hardware_CAN_Send_Message(COB_ID, data);
}

