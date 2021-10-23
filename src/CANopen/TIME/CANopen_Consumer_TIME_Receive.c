/*
 * CANopen_Consumer_TIME_Receive.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "TIME.h"

void CANopen_Consumer_TIME_Receive_Clock(CANopen *canopen, uint8_t data[]){
	/* Check if this is allowed to consume */
	uint8_t canopen_device_consumes_TIME_message = canopen->od_communication.COB_ID_time_stamp_object >> 31;
	if(!canopen_device_consumes_TIME_message)
		return; /* Nope. Not enabled as consumer */

	canopen->od_communication.verify_configuration[1] = (data[5] << 8) | data[4]; 										/* Days since 1 January 1984 */
	canopen->od_communication.verify_configuration[2] = (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0]; 	/* Milliseconds since 00:00 */
}
