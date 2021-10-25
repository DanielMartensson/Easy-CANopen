/*
 * CANopen_Server_SDO_Transmit.c
 *
 *  Created on: 24 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Server_SDO_Transmit_Download(CANopen *canopen, uint8_t node_ID, uint16_t index, uint8_t sub_index, uint32_t data){
	/* Check if SDO service is enabled */
	if(canopen->master.nmt.status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. SDO service is disabled */

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_SDO_TRANSMIT << 7 | node_ID;

	/* What size is our data */
	uint8_t size;
	if(data > 0xFFFFFF)
		size = 0;								/* 4 bytes */
	else if(data > 0xFFFF && data <= 0xFFFFFF)
		size = 1;								/* 3 bytes */
	else if(data > 0xFF && data <= 0xFFFF)
		size = 2;								/* 2 bytes */
	else
		size = 3;								/* 1 byte */

	/* Send the message to client */
	uint8_t message[8] = {0};
	message[0] = 0x43 | (size << 2);			/* 0x43 = Download, Expedited transfer, Data set size is indicated */
	message[1] = index;							/* LSB */
	message[2] = index >> 8;					/* MSB */
	message[3] = sub_index;
	message[4] = data;							/* LSB */
	message[5] = data >> 8;
	message[6] = data >> 16;
	message[7] = data >> 24;					/* MSB */
	Hardware_CAN_Send_Message(COB_ID, message);
}
