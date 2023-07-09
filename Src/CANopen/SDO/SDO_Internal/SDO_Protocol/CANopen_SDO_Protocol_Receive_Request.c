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
	/* Read data */
	uint8_t n = (data[0] >> 2) & 0x3; 	/* Size of d, if e = 0 and s = 1 */
	uint8_t e = (data[0] >> 1) & 0x1; 	/* Is expedited */
	uint8_t s = data[0] & 0x1;			/* Is size included */
	uint16_t index = *(uint16_t*)&data[1];
	uint8_t sub_index = data[3];
	uint32_t d =  *(uint32_t*)&data[4]; /* Can be value or byte size */

	bool set;
	uint32_t value;
	uint32_t byte_size;
	OD_DATA_TYPE data_type;
	uint8_t* byte_pointer = NULL;
	OD_ACCESS access;

	/* Save default information */
	canopen->slave.sdo.index = index;
	canopen->slave.sdo.sub_index = sub_index;
	canopen->slave.sdo.from_node_ID = node_ID;

	switch(cs_response){
	case CS_SDO_INITIATE_DOWNLOAD_RESPONSE:
		/* Make a choice (for download responce only)*/ 
		if(e == 1 && s == 1){
			/* Store expedited data */
			canopen->slave.sdo.expedited_byte = d;
			canopen->slave.sdo.expedited_byte_size = 4-n;	/* If n = 0, then expedited byte size is unsigned 32 bit */

			/* Set the expedited data value and get access from index and sub index */
			set = true; /*we need to write*/
			value = d;

			CANopen_OD_Bank(canopen, index, sub_index, set, &value, &byte_size, &data_type, byte_pointer, &access);

			/* Check if we had write permission */
			if((access & OD_ACCESS_WRITE) == 0){
				/* TODO: Skicka ut ett felmeddelande */
			}

		}else if(e == 0 && s == 1){
			/* Prepare for segment data */
			canopen->slave.sdo.transceive_segment_total_byte = d;
			canopen->slave.sdo.transceive_segment_bytes_counter = 0;
			canopen->slave.sdo.transceive_segment_byte_pointer = CANopen_OD_Get_Byte_Pointer(canopen, index, sub_index);
		}

		/* Create the response, but keep index and sub index at data[1], data[2] and data[3] */
		data[0] = cs_response << 5;
		data[4] = data[5] = data[6] = data[7] = 0;
	break;

	case CS_SDO_INITIATE_UPLOAD_RESPONSE:
		set = false; /*we need to read*/

		/* This is only here because we are interesting in access, data_type and byte_size */
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
		case OD_DATA_TYPE_U16:
		case OD_DATA_TYPE_U32:
			/* Send 1, 2 or 4 bytes of expedited data to client  */
			data[0] = (cs_response << 5) | ((4-byte_size) << 2) | (1 << 1) | 1; /* n = 4-byte_size, e = 1, s = 1 */
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
		*(uint32_t*)&data[4] = value;	
	break;
	}

	/* Transmit the response back */
	CANopen_SDO_Protocol_Transmit_Response_Initiate(canopen, cs_response, node_ID, data);
}

void CANopen_SDO_Protocol_Receive_Request_Segment(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]){
	CANopen_SDO_Protocol_Transmit_Response_Segment(canopen, cs_response, node_ID, data);
}
