/*
 * CANopen_SDO_Protocol_Initiate_Segment.c
 *
 *  Created on: 3 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO_Protocol.h"

/* Layers */
#include "../SDO_Internal/SDO_Internal.h"

void CANopen_SDO_Protocol_Initiate_Response(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]){
	/* Read data */
	uint8_t cs = data[0] >> 5;			/* Command specifier */
	uint8_t n = (data[0] >> 2) & 0x3; 	/* Size of d, if e = 0 and s = 1 */
	uint8_t e = (data[0] >> 1) & 0x1; 	/* Is expedited */
	uint8_t s = data[0] & 0x1;			/* Is size included */
	uint8_t index = (data[2] << 8) | data[1];
	uint8_t sub_index = data[3];
	uint32_t d = (data[7] << 24) | (data[6] << 16) | (data[5] << 8) | data[4];	/* Can be value or byte size */

	/* Save default information */
	canopen->slave.sdo.index = index;
	canopen->slave.sdo.sub_index = sub_index;
	canopen->slave.sdo.from_node_ID = node_ID;

	/* Make a choice */
	if(e == 1 && s == 1){
		/* Store expedited data */
		canopen->slave.sdo.expedited_byte = d;
		canopen->slave.sdo.expedited_byte_size = 4-n;	/* If n = 0, then expedited byte size is unsigned 32 bit */

		/* Set the expedited data value and get access from index and sub index */
		bool set = true;
		uint32_t value = d;
		uint32_t byte_size;
		OD_DATA_TYPE data_type;
		uint8_t *byte_pointer;
		OD_ACCESS access;
		CANopen_OD_Bank(canopen, index, sub_index, set, &value, &byte_size, &data_type, byte_pointer, &access);

		/* Check if we had write permission */
		if(access & OD_ACCESS_WRITE == 0){
			/* TODO: Skicka ut ett felmeddelande */
		}

	}else if(e == 0 && s == 1){
		/* Prepare for segment data */
		canopen->slave.sdo.transceive_segment_total_byte = d;
		canopen->slave.sdo.transceive_segment_bytes_counter = 0;
		canopen->slave.sdo.transceive_segment_byte_pointer = CANopen_OD_Get_Byte_Pointer(index, sub_index);
	}

	/* Modify the response, but keep index and sub index in the data array */
	data[0] = cs_response << 5;
	data[4] = 0;
	data[5] = 0;
	data[6] = 0;
	data[7] = 0;

	/* Which one should we send to? */
	switch(cs_response){
	case CS_SDO_INITIATE_DOWNLOAD_RESPONSE:
		return CANopen_Server_SDO_Transmit_Response(canopen, node_ID, data);
	case CS_SDO_INITIATE_UPLOAD_REQUEST:
		return CANopen_Client_SDO_Transmit_Response(canopen, node_ID, data);
	case CS_SDO_INITIATE_UPLOAD_RESPONSE:
		return CANopen_Server_SDO_Transmit_Response(canopen, node_ID, data);
	}
}

void CANopen_SDO_Protocol_Segment_Response(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]){
	/* Read data */
	uint8_t cs = data[0] >> 5;
	uint8_t t = ((data[0] >> 4) & 0x1) == 0 ? 1 : 0; 	/* Toggle value. If t == 0, then t should be 1 */
	uint8_t n = (data[0] >> 1) & 0x7;					/* How many bytes is NOT segment data from byte 8-n to byte 7 */
	uint8_t c = data[0] & 0x1;							/* Is last segment response */

	/* Save data */
	canopen->slave.sdo.from_node_ID = node_ID;
	for(uint8_t i = 1; i < 8-n; i++)
		if(canopen->slave.sdo.transceive_segment_bytes_counter < canopen->slave.sdo.transceive_segment_total_byte)
			canopen->slave.sdo.transceive_segment_byte_pointer[canopen->slave.sdo.transceive_segment_bytes_counter++] = data[i];

	/* Should we do a request again ? */
	if(c == 0){
		/* Clear data because we need to have an empty data array with only byte value at index 0 */
		memset(data, 0, 8);
		data[0] = (cs_response << 5) | (t << 4);			/* Toggle value << 4 */

		/* Which one should we send to? */
		switch(cs_response){
		case CS_SDO_SEGMENT_DOWNLOAD_RESPONSE:
			return CANopen_Server_SDO_Transmit_Response(canopen, node_ID, data);
		}
	}
}

void CANopen_SDO_Protocol_Initiate_Request(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]){
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
	if(access & OD_ACCESS_READ == 0){
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

	/* Which one should we send to? */
	switch(cs_response){
	case CS_SDO_INITIATE_DOWNLOAD_REQUEST:
		return CANopen_Client_SDO_Transmit_Response(canopen, node_ID, data);
	case CS_SDO_INITIATE_UPLOAD_REQUEST:
		return CANopen_Server_SDO_Transmit_Response(canopen, node_ID, data);
	}

}

void CANopen_SDO_Protocol_Segment_Request(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]){
	/* Check if we are going to send segment bytes */
	if(canopen->slave.sdo.transceive_segment_total_byte == 0)
		return; /* Nope */

	/* Read byte 0 for toggle */
	uint8_t t = 0; 										/* First time toggle t must be 0 according to standard */
	if(canopen->slave.sdo.transceive_segment_bytes_counter > 0)
		t = ((data[0] >> 4) & 0x1) == 0 ? 1 : 0; 		/* Toggle value. If t == 0, then t should be 1 */

	/* Check if this is the last segment */
	uint8_t c = 0;
	if(canopen->slave.sdo.transceive_segment_bytes_counter + 7 < canopen->slave.sdo.transceive_segment_total_byte)
		c = 1;							/* No more segments uploaded */

	/* Fill the data at index 1 to index 7 if it's possible. Meanwhile count bytes n */
	uint8_t n = 0;
	for(uint8_t i = 1; i < 8; i++)
		if(canopen->slave.sdo.transceive_segment_bytes_counter < canopen->slave.sdo.transceive_segment_total_byte)
			data[i] = canopen->slave.sdo.transceive_segment_byte_pointer[canopen->slave.sdo.transceive_segment_bytes_counter++];
		else
			n++; /* This means that byte 8-n to 7 is NOT segment data. E.g if n = 2, then byte 6 to byte 7 are NOT segment data. If n = 0, then byte 1 to 7 are segment data */

	/* Create byte 0 */
	data[0] = (cs_response << 5) | (t << 4) | (n << 1) | c;

	/* Which one should we send to? */
	switch(cs_response){
	case CS_SDO_SEGMENT_DOWNLOAD_REQUEST:
		return CANopen_Client_SDO_Transmit_Response(canopen, node_ID, data);
	case CS_SDO_SEGMENT_UPLOAD_REQUEST:
		CANopen_Client_SDO_Transmit_Response(canopen, node_ID, data);
	}
}
