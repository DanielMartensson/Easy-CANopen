/*
 * CANopen_Producer_HEARTBEAT_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT_Internal.h"

/* Layers */
#include "HEARTBEAT_Protocol/HEARTBEAT_Protocol.h"

void CANopen_Producer_HEARTBEAT_Transmit_Status(CANopen *canopen){
	/* Check if this is master node */
	uint8_t node_ID = canopen->slave.this_node_ID;
	if(node_ID == 0)
		return; /* This is master node - Cannot send */

	/* Check if heartbeat is enabled */
	if(canopen->od_communication.producer_heartbeat_time == 0)
		return;

	/* Create the heartbeat */
	CANopen_HEARTBEAT_Protocol_Produce_Status(canopen, node_ID);
}

void CANopen_Producer_HEARTBEAT_Transmit_Bootup_Message(CANopen *canopen){
	/* Check if this is master node */
	uint8_t node_ID = canopen->slave.this_node_ID;
	if(node_ID == 0)
		return; /* This is master node - Cannot send */

	/* Create the heartbeat bootup message */
	CANopen_HEARTBEAT_Protocol_Produce_Bootup_Mesage(canopen, node_ID);
}

