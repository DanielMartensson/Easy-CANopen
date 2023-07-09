/*
 * CANopen_SDO_Protocol_Transmit_Request.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO_Protocol.h"

/* Layers */
#include "../../../../Hardware/Hardware.h"
#include "../../../OD/OD.h"

void CANopen_SDO_Protocol_Transmit_Request_Initiate(CANopen *canopen, uint8_t cs, uint8_t node_ID, uint16_t index, uint8_t sub_index, uint32_t value){

	/* Default values */
	uint8_t data[8] = {0};
	data[1] = ((uint8_t*)&index)[0];    /* LSB */
	data[2] = ((uint8_t*)&index)[1];	/* MSB */
	data[3] = sub_index;

	/* For the download request */
	bool set = false;
	uint32_t data_value;
	uint32_t byte_size;
	OD_DATA_TYPE data_type;
	uint8_t *byte_pointer = NULL;
	OD_ACCESS access;

	/* Specific values */
	switch(cs){
	case CS_SDO_INITIATE_UPLOAD_REQUEST:
		data[0] = cs << 5;
		break;
	case CS_SDO_INITIATE_DOWNLOAD_REQUEST:

		/* This is only here because we are interesting in access, data_type and byte_size */
		CANopen_OD_Bank(canopen, index, sub_index, set, &data_value, &byte_size, &data_type, byte_pointer, &access);

		/* Check if we are allowed to read */
		if((access & OD_ACCESS_READ) == 0){
			/* TODO : Skicka ett SDO felmeddelande */
			return;
		}

		/* Choose the command specifier response */
		canopen->slave.sdo.transceive_segment_total_byte = 0; /* Important to set this to 0 so we know that we are not sending segments after the response */
		switch(data_type){
		case OD_DATA_TYPE_U8:
		case OD_DATA_TYPE_U16:
		case OD_DATA_TYPE_U32:
			/* Send 1, 2 or 4 bytes of expedited data to client  */
			data[0] = (cs << 5) | ((4-byte_size) << 2) | (1 << 1) | 1; /* n = 4-byte_size, e = 1, s = 1 */
			break;
		case OD_DATA_TYPE_ARRAY:
			/* Send byte size to client instead of value */
			data[0] = (cs << 5) | (0 << 2) | (0 << 1) | 1; /* n = 0, e = 0, s = 1 */
			value = byte_size;
			canopen->slave.sdo.transceive_segment_total_byte = byte_size;
			canopen->slave.sdo.transceive_segment_bytes_counter = 0;
			canopen->slave.sdo.transceive_segment_byte_pointer = byte_pointer;
			break;
		}

		/* Value can either be value or byte size of that value */
		*(uint32_t*)&data[4] = value;
	}

	/* Create the COB ID */
	uint16_t COB_ID = 0;
	switch(cs){
	case CS_SDO_INITIATE_DOWNLOAD_REQUEST:
	case CS_SDO_INITIATE_UPLOAD_REQUEST:
		COB_ID = FUNCTION_CODE_SDO_RECEIVE << 7 | node_ID;
		break;
	}

	/* Send the message to the server */
	Hardware_CAN_Send_Message(COB_ID, data);
}

void CANopen_SDO_Protocol_Transmit_Request_Segment(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]){
	/* Toggle value. If t == 0, then t should be 1 */
	uint8_t t = ((data[0] >> 4) & 0x1) == 0 ? 1 : 0;

	/* Clear data because we need to have an empty data array with only byte value at index 0 */
	memset(data, 0, 8);
	data[0] = (cs_response << 5) | (t << 4);			/* Toggle value << 4 */

	/* Create the COB ID */
	uint16_t COB_ID;
	switch(cs_response){
	case CS_SDO_SEGMENT_DOWNLOAD_REQUEST:
	case CS_SDO_SEGMENT_UPLOAD_REQUEST:
		COB_ID = FUNCTION_CODE_SDO_RECEIVE << 7 | node_ID;
		break;
	}

	/* Send the message to the server */
	Hardware_CAN_Send_Message(COB_ID, data);
}
