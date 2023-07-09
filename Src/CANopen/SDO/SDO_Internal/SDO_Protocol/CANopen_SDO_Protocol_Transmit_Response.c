/*
 * CANopen_SDO_Protocol_Transmit_Response.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO_Protocol.h"

/* Layers */
#include "../../../../Hardware/Hardware.h"

void CANopen_SDO_Protocol_Transmit_Response_Initiate(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]){
	/* Create the COB ID */
	uint16_t COB_ID = 0;
	switch(cs_response){
	case CS_SDO_INITIATE_DOWNLOAD_RESPONSE:
	case CS_SDO_INITIATE_UPLOAD_RESPONSE:
		COB_ID = FUNCTION_CODE_SDO_TRANSMIT << 7 | node_ID;
		break;
	}

	/* Send the message to the server */
	Hardware_CAN_Send_Message(COB_ID, data);
}

void CANopen_SDO_Protocol_Transmit_Response_Segment(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]){
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

	/* Create the COB ID */
	uint16_t COB_ID;
	switch(cs_response){
	case CS_SDO_SEGMENT_DOWNLOAD_RESPONSE:
	case CS_SDO_SEGMENT_UPLOAD_RESPONSE:
		COB_ID = FUNCTION_CODE_SDO_TRANSMIT << 7 | node_ID;
		break;
	}

	/* Send the message to the server */
	Hardware_CAN_Send_Message(COB_ID, data);
}
