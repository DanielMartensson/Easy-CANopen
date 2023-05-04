/*
 * CANopen_GUARD_Protocol_Transmit_Request.c
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_Protocol.h"

/* Layer */
#include "../../../../Hardware/Hardware.h"

void CANopen_GUARD_Protocol_Transmit_Request_Status(CANopen *canopen, uint8_t node_ID){
	/* Guard request have zero data */
	uint8_t data[8] = {0};

	/* Set time clock to count how long time it would take to get the response from the slave */
	canopen->slave.nmt.this_node_count_tick = Hardware_Time_Get_Tick();

	/* Create COB ID and send request to the node */
	uint16_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 7 | node_ID;
	Hardware_CAN_Send_Message(COB_ID, data);
}

