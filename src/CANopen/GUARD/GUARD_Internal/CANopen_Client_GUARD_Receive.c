/*
 * CANopen_Client_GUARD_Receive.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_Internal.h"

/* Layers */
#include "GUARD_Protocol/GUARD_Protocol.h"

void CANopen_Client_GUARD_Receive_Response(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	CANopen_GUARD_Protocol_Receive_Response_Status(canopen, node_ID, data);
}
