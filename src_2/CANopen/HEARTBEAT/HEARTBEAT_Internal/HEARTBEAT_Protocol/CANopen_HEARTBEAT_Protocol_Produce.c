/*
 * CANopen_HEARTBEAT_Protocol_Produce.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT_Protocol.h"

/* Layers */
#include "../../../../Hardware/Hardware.h"

void CANopen_HEARTBEAT_Protocol_Produce_Status(CANopen *canopen, uint8_t node_ID){
	/* Get toggle */
	uint8_t data[8] = {0};
	canopen->slave.nmt.this_node_toggle = canopen->slave.nmt.this_node_toggle == TOGGLE_NMT_0 ? TOGGLE_NMT_1 : TOGGLE_NMT_0;
	data[0] = (canopen->slave.nmt.this_node_toggle << 7) | canopen->slave.nmt.this_node_status_operational;

	/* Create the COB ID and send heartbeat to the node */
	uint16_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 7 | node_ID;
	Hardware_CAN_Send_Message(COB_ID, data);
}

void CANopen_HEARTBEAT_Protocol_Produce_Bootup_Mesage(CANopen *canopen, uint8_t node_ID){
	/* Bootup message is zero bytes */
	uint8_t data[8] = {0};

	/* Create the COB ID and send heartbeat to the node */
	uint16_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 7 | node_ID;
	Hardware_CAN_Send_Message(COB_ID, data);
}
