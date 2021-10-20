/*
 * CANopen_Producer_HEARTBEAT_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT.h"

/* Layers */
#include "../../Hardware/Hardware.h"
#include "../OD/OD.h"

void CANopen_Producer_HEARTBEAT_Transmit_Heartbeat(CANopen *canopen){
	/* Check if heartbeat is enabled */
	if(!canopen->producer.heartbeat.is_enabled)
		return;

	/* Get the heartbeat interval in milliseconds */
	uint32_t heartbeat_interval_ms = 0;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_PRODUCER_HEARTBEAT_TIME, OD_SUB_INDEX_0, &heartbeat_interval_ms);

	/* Send out a message if it has pass the threshold, then reset, or else count */
	if(canopen->producer.heartbeat.count_tick < heartbeat_interval_ms){
		canopen->producer.heartbeat.count_tick++;
		return;
	}
	canopen->producer.heartbeat.count_tick = 0;

	/* Get node ID from this producer */
	uint32_t node_ID = 0;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_NODE_ID, OD_SUB_INDEX_0, &node_ID);

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_HEARTBEAT_GUARD << 7 | node_ID;

	/* Get toggle */
	canopen->producer.heartbeat.toggle = canopen->producer.heartbeat.toggle == TOGGLE_HEARTBEAT_0 ? TOGGLE_HEARTBEAT_1 : TOGGLE_HEARTBEAT_0;

	/* Send the heartbeat message */
	canopen->producer.heartbeat.status_operational = canopen->slave.nmt.status_operational;
	uint8_t data[8] = {0};
	data[0] = (canopen->producer.heartbeat.toggle << 7) | canopen->producer.heartbeat.status_operational;
	Hardware_CAN_Send_Message(COB_ID, data);
}

