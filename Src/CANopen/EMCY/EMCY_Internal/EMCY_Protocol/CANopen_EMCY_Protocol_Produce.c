/*
 * CANopen_EMCY_Protocol_Produce.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY_Protocol.h"

/* Layers */
#include "../../../../Hardware/Hardware.h"

void CANopen_EMCY_Protocol_Produce_Error(CANopen *canopen, uint16_t new_error_code, uint8_t new_error_register, uint8_t vendor_specific_data[]){
	/* Get the error register and add new new error register to it. Please, if you reset error_register field, then clear the pre_definited_error_field as well */
	canopen->od_communication.error_register |= new_error_register;

	/* Shift the error codes down one step and save the latest on top */
	uint8_t pre_defined_error_field_length = sizeof(canopen->od_communication.pre_defined_error_field)/sizeof(canopen->od_communication.pre_defined_error_field[0]);
	for(uint8_t i = pre_defined_error_field_length-2; i >= 1; i--)
		canopen->od_communication.pre_defined_error_field[i + 1] = canopen->od_communication.pre_defined_error_field[i];
	canopen->od_communication.pre_defined_error_field[1] = new_error_code; /* Latest on top */

	/* Count how many error codes we had implemented so far */
	if(canopen->od_communication.pre_defined_error_field[0] < pre_defined_error_field_length)
		canopen->od_communication.pre_defined_error_field[0]++;

	/* Set data */
	uint8_t data[8];
	data[0] = ((uint8_t*)&new_error_code)[0];						/* LSB */
	data[1] = ((uint8_t*)&new_error_code)[1];					/* MSB */
	data[2] = canopen->od_communication.error_register;
	data[3] = vendor_specific_data[0];
	data[4] = vendor_specific_data[1];
	data[5] = vendor_specific_data[2];
	data[6] = vendor_specific_data[3];
	data[7] = vendor_specific_data[4];

	/* Create the COB ID */
	uint16_t COB_ID = FUNCTION_CODE_SYNC_EMCY << 7 | canopen->slave.this_node_ID;

	/* Send the message to client */
	Hardware_CAN_Send_Message(COB_ID, data);

}
