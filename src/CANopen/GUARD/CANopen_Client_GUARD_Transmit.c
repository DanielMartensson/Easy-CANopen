/*
 * CANopen_Client_GUARD_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Client_GUARD_Transmit_Request(CANopen *canopen, uint8_t node_ID){
	/* Check if guard is enabled */
	if(canopen->od_communication.producer_heartbeat_time > 0)
		return;

	uint8_t data[8] = {0};												/* Guard request have zero data */
	uint8_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 7 | node_ID;
	canopen->slave.guard.count_tick = Hardware_Time_Get_Tick();			/* Set time clock to count how long time it would take to get the response from the slave */
	Hardware_CAN_Send_Message(COB_ID, data);
}

