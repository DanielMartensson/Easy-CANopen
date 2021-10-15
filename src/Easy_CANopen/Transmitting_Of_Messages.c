/*
 * Transmitting_Messages.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "Easy_CANopen.h"

static void produce_a_heartbeat(CANopen *canopen);

void Easy_CANopen_Transmitting_Of_Messages(CANopen *canopen){
	produce_a_heartbeat(canopen);
}

static void produce_a_heartbeat(CANopen *canopen){
	/* Get the heartbreat interval in milliseconds */
	uint32_t heartbeat_interval_ms = 0;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_HEARTBEAT_INTERVAL_MS, OD_SUB_INDEX_0, &heartbeat_interval_ms);

	/* If we have zero interval - don't send any heartbeat */
	if(heartbeat_interval_ms == 0 || !canopen->producer.heartbeat.heartbeat_is_enabled)
		return;

	/* Send out a message if it has pass threshold, then reset, or else count */
	if(canopen->producer.heartbeat.time_count_threshold >= heartbeat_interval_ms){
		CANopen_Producer_HEARTBEAT_Transmit_Status_Operation(canopen);
		canopen->producer.heartbeat.time_count_threshold = 0;
	}else{
		canopen->producer.heartbeat.time_count_threshold++;
	}
}
