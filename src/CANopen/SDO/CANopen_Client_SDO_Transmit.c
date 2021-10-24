/*
 * CANopen_Client_SDO_Transmit.c
 *
 *  Created on: 24 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Client_SDO_Transmit_Response(CANopen *canopen, uint8_t cs, uint8_t node_ID, uint16_t index, uint8_t sub_index, uint32_t data){
	/* Check if SDO service is enabled */
	if(canopen->slave.nmt.status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. SDO service is disabled */

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_SDO_RECEIVE << 7 | node_ID;

	/* Send the message to server */
	uint8_t message[8] = {0};
	message[0] = cs;
	message[1] = index;							/* LSB */
	message[2] = index >> 8;					/* MSB */
	message[3] = sub_index;
	message[4] = data;							/* LSB */
	message[5] = data >> 8;
	message[6] = data >> 16;
	message[7] = data >> 24;					/* MSB */
	Hardware_CAN_Send_Message(COB_ID, message);
}

