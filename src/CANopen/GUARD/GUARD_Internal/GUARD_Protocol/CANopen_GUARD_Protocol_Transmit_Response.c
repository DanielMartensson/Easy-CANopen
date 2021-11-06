/*
 * CANopen_GUARD_Protocol_Transmit_Response.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_Protocol.h"

/* Layers */
#include "../../../../Hardware/Hardware.h"

void CANopen_GUARD_Protocol_Transmit_Response_Status(CANopen *canopen, uint8_t node_ID){
	/* Get toggle */
	canopen->slave.guard.toggle = canopen->slave.guard.toggle == TOGGLE_NMT_0 ? TOGGLE_NMT_1 : TOGGLE_NMT_0;
	uint8_t data[8] = {0};
	data[0] = (canopen->slave.guard.toggle << 7) | canopen->slave.nmt.status_operational;

	/* Create the COB ID and send the response to the client */
	uint32_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 7 | node_ID;
	Hardware_CAN_Send_Message(COB_ID, data);
}
