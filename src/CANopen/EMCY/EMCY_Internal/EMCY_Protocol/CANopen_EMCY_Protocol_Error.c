/*
 * CANopen_EMCY_Protocol_Error.c
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY_Protocol.h"

void CANopen_EMCY_Protocol_Error_Create(CANopen *canopen, uint16_t new_error_code, uint8_t new_error_register, uint8_t vendor_specific_data[], uint8_t data[]){
	/* Get the node ID from this producer */
	uint8_t node_ID = canopen->slave.this_node_ID;

	/* Get the error register and add new new error register to it */
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
	data[0] = new_error_code;						/* LSB */
	data[1] = new_error_code >> 8;					/* MSB */
	data[2] = canopen->od_communication.error_register;
	data[3] = vendor_specific_data[0];
	data[4] = vendor_specific_data[1];
	data[5] = vendor_specific_data[2];
	data[6] = vendor_specific_data[3];
	data[7] = vendor_specific_data[4];
}