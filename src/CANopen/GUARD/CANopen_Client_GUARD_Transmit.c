/*
 * CANopen_Client_GUARD_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Client_GUARD_Transmit_Response_Guard(CANopen *canopen, uint8_t node_ID){
	/* Check if guard is enabled */
	if(!canopen->client.guard.is_enabled)
		return;

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 7 | node_ID;

	/* Get toggle */
	canopen->client.guard.toggle = canopen->client.guard.toggle == TOGGLE_HEARTBEAT_0 ? TOGGLE_HEARTBEAT_1 : TOGGLE_HEARTBEAT_0;

	/* Send the guard message */
	canopen->client.guard.status_operational = canopen->slave.nmt.status_operational;
	uint8_t data[8] = {0};
	data[0] = (canopen->client.guard.toggle << 7) | canopen->client.guard.status_operational;
	Hardware_CAN_Send_Message(COB_ID, data);
}

