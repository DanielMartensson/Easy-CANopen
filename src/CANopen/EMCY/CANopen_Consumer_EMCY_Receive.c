/*
 * CANopen_Consumer_EMCY_Receive.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY.h"

/* Layers */
#include "../OD/OD.h"

STATUS_CODE CANopen_Consumer_EMCY_Receive_Error_Message(CANopen *canopen, uint8_t node_ID, uint8_t data[]) {

	/* Get the data */
	uint16_t error_code = (data[1] << 8) | data[0]; /* MSB LSB */
	uint8_t error_register = data[2];
	uint32_t COB_ID = FUNCTION_CODE_EMCY << 7 | node_ID;

	/* Set the vendor specific data if */
	if(error_register & ERROR_REGISTER_MANUFACTURER_SPECIFIC){
		;
	}

	/* Shift the error codes down */
	uint32_t old_error = 0;
	for(uint8_t sub_index = OD_SUB_INDEX_14; sub_index >= OD_SUB_INDEX_1; sub_index--){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, sub_index, &old_error);
		CANopen_OD_set_force_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, sub_index + 1, old_error);
	}

	/* Apply the latest error code on top, save error register and save COB ID emergency message */
	CANopen_OD_set_force_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, OD_SUB_INDEX_1, error_code);
	CANopen_OD_set_force_dictionary_object_value(canopen, OD_INDEX_ERROR_REGISTER, OD_SUB_INDEX_0, error_register);
	CANopen_OD_set_force_dictionary_object_value(canopen, OD_INDEX_COB_ID_EMERGENCY_MESSAGE, OD_SUB_INDEX_0, COB_ID);

	/* Count how many error codes we had implemented so far */
	uint32_t errors_available = 0;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, OD_SUB_INDEX_0, &errors_available);
	if(errors_available < OD_SUB_INDEX_15){
		errors_available++;
		CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, OD_SUB_INDEX_0, errors_available);
	}

	return STATUS_CODE_SUCCESSFUL;
}
