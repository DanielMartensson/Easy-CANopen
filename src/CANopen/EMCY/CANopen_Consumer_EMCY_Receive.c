/*
 * CANopen_Consumer_EMCY_Receive.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY.h"

void CANopen_Consumer_EMCY_Receive_Error_Message(CANopen *canopen, uint8_t node_ID, uint8_t data[]) {
	canopen->consumer.emcy.error_code_is_new = true;
	canopen->consumer.emcy.error_code = (data[1] << 8) | data[0]; /* MSB LSB */
	canopen->consumer.emcy.error_register = data[2];
	canopen->consumer.emcy.from_node_ID = node_ID;
}
