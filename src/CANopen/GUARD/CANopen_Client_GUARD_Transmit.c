/*
 * CANopen_Client_GUARD_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT.h"

/* Layers */
#include "../../Hardware/CAN_Network_Layer/CAN_Network_Layer.h"

STATUS_CODE CANopen_Client_GUARD_Transmit_Response_Guard(CANopen *canopen, uint8_t node_ID){
	/* Check if guard is enabled */
	if(!canopen->client.guard.is_enabled)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_GUARD << 7 | node_ID;

	/* Get toggle */
	canopen->client.guard.toggle = canopen->client.guard.toggle == TOGGLE_HEARTBEAT_0 ? TOGGLE_HEARTBEAT_1 : TOGGLE_HEARTBEAT_0;

	/* Send the heartbeat message */
	uint8_t data[8] = {0};
	data[0] = (canopen->client.guard.toggle << 7) | canopen->client.guard.status_operational;
	return CAN_Send_Message(COB_ID, data);
}

