/*
 * CANopen_Consumer_EMCY_Receive.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY_Internal.h"

void CANopen_Consumer_EMCY_Receive_Error(CANopen *canopen, uint8_t node_ID, uint8_t data[]) {
	canopen->slave.emcy.error_code = (data[1] << 8) | data[0];
	canopen->slave.emcy.error_register = data[2];
	canopen->slave.emcy.from_node_ID = node_ID;
}
