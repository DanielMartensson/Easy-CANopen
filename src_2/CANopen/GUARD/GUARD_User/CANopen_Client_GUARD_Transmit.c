/*
 * CANopen_Client_GUARD_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_User.h"

/* Layers */
#include "../GUARD_Internal/GUARD_Protocol/GUARD_Protocol.h"

void CANopen_Client_GUARD_Transmit_Request(CANopen *canopen, uint8_t node_ID){
	/* Check if guard is enabled */
	if(canopen->od_communication.producer_heartbeat_time > 0)
		return;
	CANopen_GUARD_Protocol_Transmit_Request_Status(canopen, node_ID);
}
