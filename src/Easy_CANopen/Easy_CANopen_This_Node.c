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
	CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_PRODUCER_HEARTBEAT_TIME, OD_SUB_INDEX_0, interval_ms);

	/* If the interval is zero milliseconds, then heartbeat will be disabled and guard will be enabled */
	canopen->producer.heartbeat.is_enabled = interval_ms > 0 ? true : false;
	canopen->server.guard.is_enabled = !canopen->producer.heartbeat.is_enabled;
}

void Easy_CANopen_This_Node_Configure_Guard_Time_And_Life_Factor(CANopen *canopen, uint16_t time_ms, uint8_t life_factor){
	CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_GUARD_TIME_MS, OD_SUB_INDEX_0, time_ms);
	CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_LIFE_FACTOR, OD_SUB_INDEX_0, life_factor);
}

void Easy_CANopen_This_Node_Empty_Error_Messages(CANopen *canopen){
	/* TODO: Töm felmeddelanden för EMCY */
}
