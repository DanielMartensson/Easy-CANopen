/*
 * CANopen_NMT_Protocol_Transmit_Request.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "NMT_Protocol.h"

/* Layers */
#include "../../../../Hardware/Hardware.h"

void CANopen_NMT_Protocol_Transmit_Request_State(CANopen *canopen, uint8_t cs, uint8_t node_ID){
	/* Create the COB ID */
	uint16_t COB_ID = FUNCTION_CODE_NMT << 7 | node_ID;

	/* Send the data */
	uint8_t data[8] = {0};
	data[0] = cs;
	data[1] = node_ID;
	Hardware_CAN_Send_Message(COB_ID, data);
}

