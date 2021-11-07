/*
 * CANopen_SDO_Protocol_Receive_Response.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO_Protocol.h"

/* Layers */
#include "../../../OD/OD.h"

void CANopen_SDO_Protocol_Receive_Response_Initiate(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]){
	/* Read data */
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
		if((access & OD_ACCESS_WRITE) == 0){
			/* TODO: Skicka ut ett felmeddelande */
		}

	}else if(e == 0 && s == 1){
		/* Prepare for segment data */
		canopen->slave.sdo.transceive_segment_total_byte = d;
		canopen->slave.sdo.transceive_segment_bytes_counter = 0;
		canopen->slave.sdo.transceive_segment_byte_pointer = CANopen_OD_Get_Byte_Pointer(index, sub_index);
	}

	/* Transmit the response back */
	CANopen_SDO_Protocol_Transmit_Response_Initiate(canopen, cs_response, node_ID, data);
}

void CANopen_SDO_Protocol_Receive_Response_Segment(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]){
	/* Read data */
	uint8_t n = (data[0] >> 1) & 0x7;					/* How many bytes is NOT segment data from byte 8-n to byte 7 */
	uint8_t c = data[0] & 0x1;							/* Is last segment response */

	/* Save data */
	canopen->slave.sdo.from_node_ID = node_ID;
	for(uint8_t i = 1; i < 8-n; i++)
		if(canopen->slave.sdo.transceive_segment_bytes_counter < canopen->slave.sdo.transceive_segment_total_byte)
			canopen->slave.sdo.transceive_segment_byte_pointer[canopen->slave.sdo.transceive_segment_bytes_counter++] = data[i];

	/* Should we do a request again ? */
	if(c == 0)
		CANopen_SDO_Protocol_Transmit_Request_Segment(canopen, cs_response, node_ID, data);
}
