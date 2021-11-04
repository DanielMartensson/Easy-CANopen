/*
 * CANopen_Client_GUARD_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_Internal.h"

/* Layers */
#include "../../../Hardware/Hardware.h"
#include "../GUARD_Internal/GUARD_Protocol/GUARD_Protocol.h"

void CANopen_Client_GUARD_Transmit_Request(CANopen *canopen, uint8_t node_ID){
	/* Check if guard is enabled */
	if(canopen->od_communication.producer_heartbeat_time > 0)
		return;

	/* Create request */
	uint8_t data[8] = {0};
	CANopen_GUARD_Protocol_Status_Request_Create(canopen, node_ID, data);

	/* Set time clock to count how long time it would take to get the response from the slave */
	canopen->slave.guard.count_tick = Hardware_Time_Get_Tick();

	/* Create COB ID and send request to the server */
	uint8_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 7 | node_ID;
	Hardware_CAN_Send_Message(COB_ID, data);
}
