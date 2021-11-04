/*
 * CANopen_Server_GUARD_Receive.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_Internal.h"

void CANopen_Server_GUARD_Receive_Request(CANopen *canopen, uint8_t node_ID){
	/* Only this node can receive the guard request */
	if(node_ID == canopen->slave.this_node_ID)
		CANopen_Server_GUARD_Transmit_Response(canopen, node_ID);
}
