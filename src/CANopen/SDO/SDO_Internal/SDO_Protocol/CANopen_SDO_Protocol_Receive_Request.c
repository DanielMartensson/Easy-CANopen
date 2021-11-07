/*
 * CANopen_SDO_Protocol_Receive_Request.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO_Protocol.h"

/* Layers */
#include "../../../OD/OD.h"

void CANopen_SDO_Protocol_Receive_Request_Initiate(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]){
	/* Get index and sub index */
	uint16_t index = (data[2] << 8) | data[1];
	uint8_t sub_index = data[3];

	/* Get the expedited data value and data type from index and sub index */
	bool set = false;
	uint32_t value;										/* This is the expedited value */
	uint32_t byte_size;
	OD_DATA_TYPE data_type;
	uint8_t *byte_pointer;
	OD_ACCESS access;
	CANopen_OD_Bank(canopen, index, sub_index, set, &value, &byte_size, &data_type, byte_pointer, &access);

	/* Check if we are allowed to read */
	if((access & OD_ACCESS_READ) == 0){
		/* TODO : Skicka ett SDO felmeddelande */
		return;
	}

	/* Choose the command specifier response */
	canopen->slave.sdo.transceive_segment_total_byte = 0; /* Important to set this to 0 so we know that we are not sending segments after the response */
	switch(data_type){
	case OD_DATA_TYPE_U8:
		/* Send 1 byte of expedited data to client  */
		data[0] = (cs_response << 5) | (3 << 2) | (1 << 1) | 1; /* n = 3, e = 1, s = 1 */
		break;
	case OD_DATA_TYPE_U16:
		/* Send 2 bytes of expedited data to client  */
		data[0] = (cs_response << 5) | (2 << 2) | (1 << 1) | 1; /* n = 2, e = 1, s = 1 */
		break;
	case OD_DATA_TYPE_U32:
		/* Send 4 bytes of expedited data to client  */
		data[0] = (cs_response << 5) | (0 << 2) | (1 << 1) | 1; /* n = 0, e = 1, s = 1 */
		break;
	case OD_DATA_TYPE_ARRAY:
		/* Send byte size to client instead of value */
		data[0] = (cs_response << 5) | (0 << 2) | (0 << 1) | 1; /* n = 0, e = 0, s = 1 */
		value = byte_size;
		canopen->slave.sdo.transceive_segment_total_byte = byte_size;
		canopen->slave.sdo.transceive_segment_bytes_counter = 0;
		canopen->slave.sdo.transceive_segment_byte_pointer = byte_pointer;
		break;
	}

	/* Value can either be value or byte size of that value */
	data[4] = value;									/* LSB */
	data[5] = value >> 8;
	data[6] = value >> 16;
	data[7] = value >> 24;								/* MSB */

	/* Send a request */
	CANopen_SDO_Protocol_Transmit_Response_Initiate(canopen, cs_response, node_ID, data);
}

void CANopen_SDO_Protocol_Receive_Request_Segment(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]){
	CANopen_SDO_Protocol_Transmit_Response_Segment(canopen, cs_response, node_ID, data);
}
