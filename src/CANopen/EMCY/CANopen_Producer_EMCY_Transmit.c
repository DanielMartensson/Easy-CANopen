/*
 * CANopen_Producer_EMCY_Transmit.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY.h"

/* Layers */
#include "../../Hardware/Hardware.h"

/*
 * Transmit and save the new error code and new error register.
 * The error code and error register belongs to this node device.
 * NMT must be in operational mode or pre operational mode.
 */
void CANopen_Producer_EMCY_Transmit(CANopen *canopen, uint16_t new_error_code, uint8_t new_error_register, uint8_t vendor_specific_data[]){
	/* Check if EMCY service is enabled */
	if(canopen->slave.nmt.status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. ECMY service is disabled */

	/* Get the node ID from this producer */
	uint8_t node_ID = canopen->slave.this_node_ID;

	/* Get the error register and add new new error register to it */
	canopen->od_communication.error_register |= new_error_register;

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_SYNC_EMCY << 7 | node_ID;

	/* Create the data and send it */
	uint8_t data[8];
	data[0] = new_error_code;						/* LSB */
	data[1] = new_error_code >> 8;					/* MSB */
	data[2] = canopen->od_communication.error_register;
	data[3] = vendor_specific_data[0];
	data[4] = vendor_specific_data[1];
	data[5] = vendor_specific_data[2];
	data[6] = vendor_specific_data[3];
	data[7] = vendor_specific_data[4];
	Hardware_CAN_Send_Message(COB_ID, data);

	/* Shift the error codes down one step and save the latest on top */
	uint8_t pre_defined_error_field_length = sizeof(canopen->od_communication.pre_defined_error_field)/sizeof(canopen->od_communication.pre_defined_error_field[0]);
	for(uint8_t i = pre_defined_error_field_length-2; i >= 1; i--)
		canopen->od_communication.pre_defined_error_field[i + 1] = canopen->od_communication.pre_defined_error_field[i];
	canopen->od_communication.pre_defined_error_field[1] = new_error_code; /* Latest on top */

	/* Count how many error codes we had implemented so far */
	if(canopen->od_communication.pre_defined_error_field[0] < pre_defined_error_field_length)
		canopen->od_communication.pre_defined_error_field[0]++;
}
