/*
 * CANopen_Client_SDO_Transmit.c
 *
 *  Created on: 24 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO_User.h"

/* Layers */
#include "../../../Hardware/Hardware.h"
#include "../SDO_Internal/SDO_Internal.h"

void CANopen_Client_SDO_Transmit_Request(CANopen *canopen, uint8_t cs, uint8_t node_ID, uint16_t index, uint8_t sub_index){
	/* Check if SDO service is enabled */
	if(canopen->slave.nmt.status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. SDO service is disabled */

	/* Define the index and sub index position in a data array. We don't need to specify data[0] here */
	uint8_t data[8] = {0};
	data[1] = index;												/* LSB */
	data[2] = index >> 8;											/* MSB */
	data[3] = sub_index;

	/* Make a choice */
	switch(cs){
	case CS_SDO_INITIATE_DOWNLOAD_REQUEST:
		CANopen_SDO_Protocol_Initiate_Request_Create(canopen, CS_SDO_INITIATE_DOWNLOAD_REQUEST, node_ID, data);		/* This modify our request */
		break;
	case CS_SDO_INITIATE_UPLOAD_REQUEST:
		CANopen_SDO_Protocol_Initiate_Response_Create(canopen, CS_SDO_INITIATE_UPLOAD_REQUEST, node_ID, data);		/* This response function is used as a request function because e = s = 0 */
		break;
	}

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_SDO_RECEIVE << 7 | node_ID;

	/* Send the message to the server */
	Hardware_CAN_Send_Message(COB_ID, data);
}
