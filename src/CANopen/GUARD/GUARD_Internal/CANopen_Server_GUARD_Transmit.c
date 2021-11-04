/*
 * CANopen_Server_GUARD_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_Internal.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Server_GUARD_Transmit_Response(CANopen *canopen, uint8_t node_ID){
	/* Create the response */
	uint8_t data[8] = {0};
	CANopen_GUARD_Protocol_Status_Response_Create(canopen, node_ID, data);

	/* Create the COB ID and send the response to the client */
	uint32_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 7 | node_ID;
	Hardware_CAN_Send_Message(COB_ID, data);
}
