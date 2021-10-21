/*
 * CANopen_Server_GUARD_Receive.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "GUARD.h"

/* Layers */
#include "../OD/OD.h"
#include "../EMCY/EMCY.h"
#include "../../Hardware/Hardware.h"

void CANopen_Server_GUARD_Receive_Response_Guard(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Check if guard is enabled */
	if(canopen->od_communication.producer_heartbeat_time > 0)
		return;

	/* Get guard time in milliseconds and life factor */
	uint32_t guard_time_ms = canopen->od_communication.guard_time;
	uint32_t life_factor = canopen->od_communication.life_time_factor;

	/* Save the response */
	canopen->nmt_master.from_node_ID = node_ID;
	canopen->nmt_master.node_status_operation = data[0] & 0x7F;
	canopen->nmt_master.toggle_heartbeat = data[0] >> 7;
	canopen->nmt_master.count_tick = Hardware_Time_Get_Tick() - canopen->nmt_master.count_tick;	/* Time difference from request to response */

	/* If the time difference is too large, send out an EMCY */
	uint8_t vendor_specific_data[5] = {0};
	if(life_factor * guard_time_ms < canopen->nmt_master.count_tick)
		CANopen_Producer_EMCY_Transmit_Error_Message(canopen, ERROR_CODE_GUARD_HARTBEAT, ERROR_REGISTER_COMMUNICATION_ERROR, vendor_specific_data);
}
