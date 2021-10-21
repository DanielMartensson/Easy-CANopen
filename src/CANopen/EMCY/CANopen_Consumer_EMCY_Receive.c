/*
 * CANopen_Consumer_EMCY_Receive.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Consumer_EMCY_Receive_Error_Message(CANopen *canopen, uint8_t node_ID, uint8_t data[]) {
	uint16_t error_code = (data[1] << 8) | data[0]; /* MSB LSB */
	uint32_t value = (1 << 31) | (CAN_ID_BITS_LENGTH << 29) | (FUNCTION_CODE_SYNC_EMCY << 7) | node_ID;
	if(error_code == ERROR_CODE_NO_ERROR)
		value |= 0 << 31; /* EMCY consumer does not exist */

	/* The Sub-index shall refer to the related node-ID according to CiA301 V4.2.0 */
	canopen->od_communication.emergency_consumer_object[node_ID] = value;
}
