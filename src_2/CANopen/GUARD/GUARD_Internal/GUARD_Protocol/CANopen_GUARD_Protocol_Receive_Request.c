/*
 * CANopen_GUARD_Protocol_Receive_Request.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_Protocol.h"

/* Layers */
#include "../GUARD_Internal.h"

void CANopen_GUARD_Protocol_Receive_Request_Status(CANopen *canopen, uint8_t node_ID){
	CANopen_Server_GUARD_Transmit_Response(canopen, node_ID);
}
