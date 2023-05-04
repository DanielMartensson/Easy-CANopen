/*
 * CANopen_GUARD_Protocol_Receive_Response.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD_Protocol.h"

/* Layers */
#include "../../../EMCY/EMCY_Internal/EMCY_Internal.h"
#include "../../../../Hardware/Hardware.h"

void CANopen_GUARD_Protocol_Receive_Response_Status(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Save the response */
	canopen->slave.nmt.from_node_status_operational = data[0] & 0x7F;
	canopen->slave.nmt.from_node_toggle = data[0] >> 7;
	canopen->slave.nmt.from_node_count_tick = Hardware_Time_Get_Tick() - canopen->slave.nmt.from_node_count_tick;	/* Time difference from request to response */
	canopen->slave.nmt.from_node_ID = node_ID;

	/* If the time difference is too large, send out an EMCY */
	uint32_t guard_time_ms = canopen->od_communication.guard_time;
	uint32_t life_factor = canopen->od_communication.life_time_factor;
	uint8_t vendor_specific_data[5] = {0};
	if(life_factor * guard_time_ms < canopen->slave.nmt.from_node_count_tick)
		CANopen_Producer_EMCY_Transmit_Error(canopen, ERROR_CODE_GUARD_HARTBEAT, ERROR_REGISTER_COMMUNICATION_ERROR, vendor_specific_data);
}
