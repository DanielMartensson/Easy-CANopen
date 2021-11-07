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

void CANopen_Client_SDO_Transmit_Request(CANopen *canopen, uint8_t cs, uint8_t node_ID, uint16_t index, uint8_t sub_index, uint32_t value){
	/* Check if SDO service is enabled */
	if(canopen->slave.nmt.status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. SDO service is disabled */

	/* Define the index and sub index position in a data array. We don't need to specify data[0] here */
	uint8_t data[8] = {0};
	data[1] = index;									/* LSB */
	data[2] = index >> 8;								/* MSB */
	data[3] = sub_index;
	data[4] = value;									/* LSB */
	data[5] = value >> 8;
	data[6] = value >> 16;
	data[7] = value >> 24;								/* MSB */

	/* Make a choice */
	switch(cs){
	case CS_SDO_INITIATE_DOWNLOAD_REQUEST:
		CANopen_SDO_Protocol_Transmit_Request_Initiate(canopen, CS_SDO_INITIATE_DOWNLOAD_REQUEST, node_ID, data);
		break;
	case CS_SDO_INITIATE_UPLOAD_REQUEST:
		CANopen_SDO_Protocol_Transmit_Request_Initiate(canopen, CS_SDO_INITIATE_UPLOAD_REQUEST, node_ID, data);
		break;
	}
}
