/*
 * CANopen_HEATBEAT_Protocol_Status.c
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT_Protocol.h"

void CANopen_HEARTBEAT_Protocol_Status_Create(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Get toggle */
	canopen->slave.heartbeat.toggle = canopen->slave.heartbeat.toggle == TOGGLE_NMT_0 ? TOGGLE_NMT_1 : TOGGLE_NMT_0;
	data[0] = (canopen->slave.heartbeat.toggle << 7) | canopen->slave.nmt.status_operational;
}
