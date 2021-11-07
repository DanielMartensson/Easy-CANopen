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
	/* If we have bytes to send, this function will transmit a response of segment, else it will return back */
	CANopen_SDO_Protocol_Transmit_Response_Segment(canopen, cs_response, node_ID, data);
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
