/*
 * Easy_CANopen_This_Node.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "Easy_CANopen.h"

/* Layers */
#include "../CANopen/OD/OD.h"

void Easy_CANopen_This_Node_Configure_Heartbeat_Interval(CANopen *canopen, uint16_t interval_ms){
	canopen->od_communication.producer_heartbeat_time = interval_ms; /* If this is zero, then heartbeat will be disabled */
}

void Easy_CANopen_This_Node_Configure_Guard_Time_And_Life_Factor(CANopen *canopen, uint16_t time_ms, uint8_t life_factor){
	canopen->od_communication.guard_time = time_ms;
	canopen->od_communication.life_time_factor = life_factor;
}

void Easy_CANopen_This_Node_Empty_Error_Messages(CANopen *canopen){
	/* TODO: Töm felmeddelanden för EMCY */
}
