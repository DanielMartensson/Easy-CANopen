/*
 * CANopen_Server_GUARD_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Server_GUARD_Transmit_Response(CANopen *canopen, uint8_t node_ID){
	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 7 | node_ID;

	/* Get toggle */
	canopen->slave.nmt.toggle = canopen->slave.heartbeat.toggle == TOGGLE_HEARTBEAT_0 ? TOGGLE_HEARTBEAT_1 : TOGGLE_HEARTBEAT_0;

	/* Send the heartbeat message */
	uint8_t data[8] = {0};
	data[0] = (canopen->slave.nmt.toggle << 7) | canopen->slave.nmt.status_operational;
	Hardware_CAN_Send_Message(COB_ID, data);
}

