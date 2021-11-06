/*
 * CANopen_EMCY_Protocol_Consume.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY_Protocol.h"

void CANopen_EMCY_Protocol_Consume_Error(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	canopen->slave.emcy.error_code = (data[1] << 8) | data[0];
	canopen->slave.emcy.error_register = data[2];
	canopen->slave.emcy.from_node_ID = node_ID;
}
