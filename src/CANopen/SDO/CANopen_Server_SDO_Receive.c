/*
 * CANopen_Server_SDO_Receive.c
 *
 *  Created on: 24 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO.h"

void CANopen_Server_SDO_Receive_Request(CANopen *canopen, uint8_t node_ID, uint8_t message[]){
	/* Get the information about the message we just received */
	uint8_t cs = message[0];
	uint16_t index = (message[2] << 8) | message[1];
	uint8_t sub_index = message[3];
	uint32_t data = (message[7] << 24) | (message[6] << 16) | (message[5] << 8) | message[4];

	/* Find the data type size */
	OD_DATA_TYPE data_type = CANopen_OD_Get_Size_Data_Type(canopen, index, sub_index);

	/* Perform to dig into the object dictionary system */
	switch(cs){
	case CS_SDO_DOWNLOAD_REQUEST_OBJECT_DICTIONARY:

		/* Get the data */
		CANopen_OD_Set_Get_Value(canopen, index, sub_index, false, &data, data_type);

		/* Change the response command specifier */
		switch(data_type){
		case OD_DATA_TYPE_U8:
			cs = CS_SDO_DOWNLOAD_RESPONSE_1_BYTE;
			break;
		case OD_DATA_TYPE_U16:
			cs = CS_SDO_DOWNLOAD_RESPONSE_2_BYTES;
			break;
		case OD_DATA_TYPE_U32:
			cs = CS_SDO_DOWNLOAD_RESPONSE_4_BYTES;
			break;
		}
		break;
	case CS_SDO_UPLOAD_REQUEST_4_BYTES:

		/* Set 4 bytes of data and change the response command specifier */
		CANopen_OD_Set_Get_Value(canopen, index, sub_index, true, &data, data_type);
		cs = CS_SDO_UPLOAD_RESPONSE_OBJECT_DICTIONARY;
		break;
	case CS_SDO_UPLOAD_REQUEST_2_BYTES:

		/* Set 2 bytes of data and change the response command specifier */
		CANopen_OD_Set_Get_Value(canopen, index, sub_index, true, &data, data_type);
		cs = CS_SDO_UPLOAD_RESPONSE_OBJECT_DICTIONARY;
		break;
	case CS_SDO_UPLOAD_REQUEST_1_BYTE:

		/* Set 1 byte of data and change the response command specifier */
		CANopen_OD_Set_Get_Value(canopen, index, sub_index, true, &data, data_type);
		cs = CS_SDO_UPLOAD_RESPONSE_OBJECT_DICTIONARY;
		break;
	default:
		break;	/* Send error code that the CS does not exist TODO: Fixa detta */
	}

	/* Transmit the response back to the client */
	CANopen_Server_SDO_Transmit_Response(canopen, cs, node_ID, index, sub_index, data);
}
