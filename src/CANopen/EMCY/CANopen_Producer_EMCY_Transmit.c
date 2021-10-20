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

void CANopen_Producer_EMCY_Transmit_Error_Message(CANopen *canopen, uint16_t new_error_code, uint8_t new_error_register, uint8_t vendor_specific_data[]){
	/* Check if EMCY is enabled */
	uint32_t COB_ID_MERCY;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_COB_ID_EMCY, OD_SUB_INDEX_0, &COB_ID_MERCY);
	uint8_t EMCY_does_not_exist = COB_ID_MERCY >> 31;
	if(EMCY_does_not_exist)
		return; /* MECY producer is not enabled */

	/* Get the node ID from this node */
	uint32_t node_ID = 0;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_NODE_ID, OD_SUB_INDEX_0, &node_ID);

	/* Get the error register and add new new error register to it */
	uint32_t error_register = 0;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_ERROR_REGISTER, OD_SUB_INDEX_0, &error_register);
	error_register |= new_error_register;

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
	uint32_t old_error = 0;
	for(uint8_t sub_index = OD_SUB_INDEX_14; sub_index >= OD_SUB_INDEX_1; sub_index--){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, sub_index, &old_error);
		CANopen_OD_set_force_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, sub_index + 1, old_error);
	}

	/* Save the latest error code on top and save error register as well */
	CANopen_OD_set_force_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, OD_SUB_INDEX_1, new_error_code);
	CANopen_OD_set_force_dictionary_object_value(canopen, OD_INDEX_ERROR_REGISTER, OD_SUB_INDEX_0, error_register);

	/* Count how many error codes we had implemented so far */
	uint32_t errors_available = 0;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, OD_SUB_INDEX_0, &errors_available);
	if(errors_available < OD_SUB_INDEX_15){
		errors_available++;
		CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, OD_SUB_INDEX_0, errors_available);
	}
}
