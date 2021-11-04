/*
 * CANopen_Client_GUARD_Receive.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_Internal.h"

/* Layers */
#include "../../EMCY/EMCY_Internal/EMCY_Internal.h"

void CANopen_Client_GUARD_Receive_Response(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Save the response */
	canopen->slave.guard.status_operational = data[0] & 0x7F;
	canopen->slave.guard.toggle = data[0] >> 7;
	canopen->slave.guard.count_tick = Hardware_Time_Get_Tick() - canopen->slave.guard.count_tick;	/* Time difference from request to response */
	canopen->slave.guard.from_node_ID = node_ID;

	/* If the time difference is too large, send out an EMCY */
	uint32_t guard_time_ms = canopen->od_communication.guard_time;
	uint32_t life_factor = canopen->od_communication.life_time_factor;
	uint8_t vendor_specific_data[5] = {0};
	if(life_factor * guard_time_ms < canopen->slave.guard.count_tick)
		CANopen_Producer_EMCY_Transmit_Error(canopen, ERROR_CODE_GUARD_HARTBEAT, ERROR_REGISTER_COMMUNICATION_ERROR, vendor_specific_data);
}


