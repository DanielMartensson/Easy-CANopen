/*
 * CANopen_Server_GUARD_Receive.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_Internal.h"

/* Layers */
#include "GUARD_Protocol/GUARD_Protocol.h"

void CANopen_Server_GUARD_Receive_Request_Status(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Check if guard is enabled */
	if(canopen->od_communication.producer_heartbeat_time > 0)
		return;

	/* A guard request have zero data */
	uint16_t total_bytes = 0;
	for(uint8_t i = 0; i < 8; i++)
		total_bytes += data[i];
	if(total_bytes > 0)
		return;

	/* Only this node can receive the guard request */
	if(node_ID == canopen->slave.this_node_ID)
		CANopen_GUARD_Protocol_Receive_Request_Status(canopen, node_ID);
}
