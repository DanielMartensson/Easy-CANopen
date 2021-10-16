/*
 * CANopen_Client_GUARD_Receive.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT.h"

STATUS_CODE CANopen_Client_GUARD_Receive_Request_Guard(CANopen *canopen, uint8_t node_ID){
	return CANopen_Client_GUARD_Transmit_Response_Guard(canopen, node_ID);
}


