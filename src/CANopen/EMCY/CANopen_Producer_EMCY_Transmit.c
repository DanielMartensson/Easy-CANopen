/*
 * CANopen_Producer_EMCY_Transmit.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY.h"

/* Layers */
#include "../../Hardware/Hardware.h"
#include "../OD/OD.h"

STATUS_CODE CANopen_Producer_EMCY_Transmit_Error_Message(CANopen *canopen, uint16_t error_code, uint8_t error_register, uint8_t vendor_specific_data[]){
	/* Get the node ID from this node */
	uint32_t node_ID = 0;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_5, &node_ID);

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_EMCY << 7 | node_ID;

	/* Create the data and send it */
	uint8_t data[8];
	data[0] = error_code;						/* LSB */
	data[1] = error_code >> 8;					/* MSB */
	data[2] = error_register;
	data[3] = vendor_specific_data[0];
	data[4] = vendor_specific_data[1];
	data[5] = vendor_specific_data[2];
	data[6] = vendor_specific_data[3];
	data[7] = vendor_specific_data[4];
	return CAN_Send_Message(COB_ID, data);
}



