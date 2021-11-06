/*
 * CANopen_SDO_Protocol_Transmit_Request.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO_Protocol.h"

/* Layers */
#include "../../../../Hardware/Hardware.h"

void CANopen_SDO_Protocol_Transmit_Request_Initiate(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]){
	/* Create the COB ID */
	uint32_t COB_ID;
	switch(cs_response){
	case CS_SDO_INITIATE_DOWNLOAD_REQUEST:
		COB_ID = FUNCTION_CODE_SDO_RECEIVE << 7 | node_ID;
		break;
	case CS_SDO_INITIATE_UPLOAD_REQUEST:
		COB_ID = FUNCTION_CODE_SDO_TRANSMIT << 7 | node_ID;
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
	uint32_t COB_ID;
	switch(cs_response){
	case CS_SDO_SEGMENT_DOWNLOAD_REQUEST:
		COB_ID = FUNCTION_CODE_SDO_RECEIVE << 7 | node_ID;
		break;
	case CS_SDO_SEGMENT_UPLOAD_REQUEST:
		COB_ID = FUNCTION_CODE_SDO_TRANSMIT << 7 | node_ID;
		break;
	}

	/* Send the message to the server */
	Hardware_CAN_Send_Message(COB_ID, data);
}
