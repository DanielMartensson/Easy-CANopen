/*
 * CANopen_Client_GUARD_Receive.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD.h"

/*
 * Receive the guard request and transmit the guard response back to the server with node ID
 */
void CANopen_Client_GUARD_Receive_Request_Guard(CANopen *canopen, uint8_t node_ID){
	CANopen_Client_GUARD_Transmit_Response_Guard(canopen, node_ID);
}


