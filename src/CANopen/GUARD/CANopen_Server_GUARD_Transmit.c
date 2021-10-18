/*
 * CANopen_Server_GUARD_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD.h"

/* Layers */
#include "../../Hardware/Hardware.h"

STATUS_CODE CANopen_Server_GUARD_Transmit_Request_Guard(CANopen *canopen, uint8_t node_ID){
	/* Check if guard is enabled */
	if(!canopen->server.guard.is_enabled)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	uint8_t data[8] = {0};												/* Guard request have zero data */
	uint8_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 8 | node_ID;
	canopen->server.guard.count_tick = Hardware_Get_Time_Tick();		/* Set time clock to count how long time it would take to get the response from the slave */
	return CAN_Send_Message(COB_ID, data);
}

