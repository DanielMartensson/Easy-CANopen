/*
 * CANopen_Client_SDO_Receive.c
 *
 *  Created on: 24 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO_Internal.h"

/* Layers */
#include "SDO_Protocol/SDO_Protocol.h"

void CANopen_Client_SDO_Receive_Response(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Check if it's right node */
	if(node_ID != canopen->slave.this_node_ID)
		return;

	/* Read command specifier */
	uint8_t cs = data[0] >> 5;

	switch(cs){
	case CS_SDO_INITIATE_DOWNLOAD_RESPONSE:
		CANopen_SDO_Protocol_Receive_Response_Initiate(canopen, CS_SDO_SEGMENT_DOWNLOAD_REQUEST, node_ID, data);
		break;
	case CS_SDO_SEGMENT_DOWNLOAD_RESPONSE:
		CANopen_SDO_Protocol_Receive_Response_Segment(canopen, CS_SDO_SEGMENT_DOWNLOAD_REQUEST, node_ID, data);
		break;
	case CS_SDO_INITIATE_UPLOAD_RESPONSE:
		CANopen_SDO_Protocol_Receive_Response_Initiate(canopen, CS_SDO_SEGMENT_UPLOAD_REQUEST, node_ID, data);
		break;
	case CS_SDO_SEGMENT_UPLOAD_RESPONSE:
		CANopen_SDO_Protocol_Transmit_Response_Segment(canopen, CS_SDO_SEGMENT_UPLOAD_REQUEST, node_ID, data);
		break;
	}
}
