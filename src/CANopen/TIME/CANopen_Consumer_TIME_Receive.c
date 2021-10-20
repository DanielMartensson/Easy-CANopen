/*
 * CANopen_Consumer_TIME_Receive.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "TIME.h"

/* Layers */
#include "../OD/OD.h"

void CANopen_Consumer_TIME_Receive_Clock(CANopen *canopen, uint8_t data[]){
	/* Check if this is allowed to consume */
	uint32_t COB_ID_stamp_object = 0;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_COB_ID_TIME_STAMP_OBJECT, OD_SUB_INDEX_0, &COB_ID_stamp_object);
	uint8_t canopen_device_consumes_TIME_message = COB_ID_stamp_object >> 31;
	if(!canopen_device_consumes_TIME_message)
		return; /* Nope. Not enabled as consumer */

	uint32_t milliseconds_since_midnight = (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
	uint16_t days_since_1_januari_1984 = (data[5] << 8) | data[4];
	CANopen_OD_set_force_dictionary_object_value(canopen, OD_INDEX_VERIFY_CONFIGURATION, OD_SUB_INDEX_0, 2);
	CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_VERIFY_CONFIGURATION, OD_SUB_INDEX_1, days_since_1_januari_1984);
	CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_VERIFY_CONFIGURATION, OD_SUB_INDEX_2, milliseconds_since_midnight);
}
