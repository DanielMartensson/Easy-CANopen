/*
 * CANopen_Client_GUARD_Receive.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD.h"

void CANopen_Client_GUARD_Receive_Request_Guard(CANopen *canopen, uint8_t node_ID){
	CANopen_Client_GUARD_Transmit_Response_Guard(canopen, node_ID);
}


