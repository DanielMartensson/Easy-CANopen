/*
 * CANopen_Server_GUARD_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_Internal.h"

/* Layers */
#include "GUARD_Protocol/GUARD_Protocol.h"

void CANopen_Server_GUARD_Transmit_Response(CANopen *canopen, uint8_t node_ID){
	CANopen_GUARD_Protocol_Transmit_Response_Status(canopen, node_ID);
}
