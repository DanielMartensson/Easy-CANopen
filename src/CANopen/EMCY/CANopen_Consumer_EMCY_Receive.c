/*
 * CANopen_Consumer_EMCY_Receive.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY.h"

/* Layers */
#include "../OD/OD.h"

void CANopen_Consumer_EMCY_Receive_Error_Message(CANopen *canopen, uint8_t node_ID, uint8_t data[]) {

	/*
	 *  The error code are of type UNSIGNED32 (see Figure 53: Structure of the pre-defined error field in CiA301 V4.2.0.pdf)
	 *  and are composed of a 16-bit error code and a 16-bit additional error information field, which is manufacturer-specific.
	 *  The error code shall be contained in the lower 2 bytes (LSB) and the additional information shall be
	 *	included in the upper 2 bytes (MSB). If this object is supported it shall consist of two object
	 *	entries at least. The length entry on sub-index 00h and at least one error entry at sub-index 01h.
	 */
	uint32_t error_code = (node_ID << 16) | (data[1] << 8) | data[0]; /* MSB LSB */
	uint8_t error_register = data[2];

	/* Shift the error codes down one step */
	uint32_t old_error = 0;
	for(uint8_t sub_index = OD_SUB_INDEX_14; sub_index >= OD_SUB_INDEX_1; sub_index--){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, sub_index, &old_error);
		CANopen_OD_set_force_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, sub_index + 1, old_error);
	}

	/* Apply the latest error code on top, save error register and save COB ID emergency message */
	CANopen_OD_set_force_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, OD_SUB_INDEX_1, error_code);
	CANopen_OD_set_force_dictionary_object_value(canopen, OD_INDEX_ERROR_REGISTER, OD_SUB_INDEX_0, error_register);

	/* Count how many error codes we had implemented so far */
	uint32_t errors_available = 0;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, OD_SUB_INDEX_0, &errors_available);
	if(errors_available < OD_SUB_INDEX_15){
		errors_available++;
		CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_PRE_DEFINED_ERROR_FIELD, OD_SUB_INDEX_0, errors_available);
	}
}
