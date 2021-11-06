/*
 * CANopen_GUARD_Protocol_Receive_Request.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_Protocol.h"

void CANopen_GUARD_Protocol_Receive_Request(CANopen *canopen, uint8_t node_ID){
	/* Only this node can receive the guard request */
	if(node_ID == canopen->slave.this_node_ID)
		CANopen_Server_GUARD_Transmit_Response(canopen, node_ID);
}
