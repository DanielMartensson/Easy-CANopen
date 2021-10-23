/*
 * CANopen_Client_GUARD_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD.h"

/* Layers */
#include "../../Hardware/Hardware.h"

/*
 * Transmit the guard response to the server node ID.
 * Notice that if heartbeat time is greater than 0, then guard service will be disabled.
 */
void CANopen_Client_GUARD_Transmit_Response_Guard(CANopen *canopen, uint8_t node_ID){
	/* Check if guard is enabled */
	if(canopen->od_communication.producer_heartbeat_time > 0)
		return;

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 7 | node_ID;

	/* Get toggle */
	canopen->slave.nmt.toggle_heartbeat = canopen->slave.nmt.toggle_heartbeat == TOGGLE_HEARTBEAT_0 ? TOGGLE_HEARTBEAT_1 : TOGGLE_HEARTBEAT_0;

	/* Send the heartbeat message */
	uint8_t data[8] = {0};
	data[0] = (canopen->slave.nmt.toggle_heartbeat << 7) | canopen->slave.nmt.status_operational;
	Hardware_CAN_Send_Message(COB_ID, data);
}

