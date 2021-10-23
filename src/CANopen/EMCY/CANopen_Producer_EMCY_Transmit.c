/*
 * CANopen_Producer_EMCY_Transmit.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Producer_EMCY_Transmit_Error_Message(CANopen *canopen, uint16_t new_error_code, uint8_t new_error_register, uint8_t vendor_specific_data[]){
	/* Check if EMCY is enabled */
	uint8_t EMCY_does_not_exist = canopen->od_communication.COB_ID_emcy >> 31;
	if(EMCY_does_not_exist)
		return; /* MECY producer is not enabled */

	/* Get the node ID from this producer */
	uint32_t node_ID = canopen->od_manufacturer.node_ID;

	/* Get the error register and add new new error register to it */
	uint32_t error_register = canopen->od_communication.error_register | new_error_register;

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_SYNC_EMCY << 7 | node_ID;

	/* Create the data and send it */
	uint8_t data[8];
	data[0] = new_error_code;						/* LSB */
	data[1] = new_error_code >> 8;					/* MSB */
	data[2] = error_register;
	data[3] = vendor_specific_data[0];
	data[4] = vendor_specific_data[1];
	data[5] = vendor_specific_data[2];
	data[6] = vendor_specific_data[3];
	data[7] = vendor_specific_data[4];
	Hardware_CAN_Send_Message(COB_ID, data);

	/* Shift the error codes down one step */
	for(uint8_t sub_index = 8; sub_index >= 1; sub_index--)
		canopen->od_communication.pre_defined_error_field[sub_index + 1] = canopen->od_communication.pre_defined_error_field[sub_index];

	/* Save the latest error code on top and save error register as well */
	canopen->od_communication.pre_defined_error_field[1] = new_error_code;
	canopen->od_communication.error_register = error_register;

	/* Count how many error codes we had implemented so far */
	if(canopen->od_communication.pre_defined_error_field[0] < 0xA)
		canopen->od_communication.pre_defined_error_field[0]++;
}
