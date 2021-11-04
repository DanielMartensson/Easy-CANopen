/*
 * CANopen_GUARD_Protocol_Status.c
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_Protocol.h"

void CANopen_GUARD_Protocol_Status_Request_Create(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	memset(data, 0, 8); 	/* Guard request have zero data */
}

void CANopen_GUARD_Protocol_Status_Response_Create(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Get toggle */
	canopen->slave.guard.toggle = canopen->slave.guard.toggle == TOGGLE_NMT_0 ? TOGGLE_NMT_1 : TOGGLE_NMT_0;
	data[0] = (canopen->slave.guard.toggle << 7) | canopen->slave.nmt.status_operational;
}
