/*
 * CANopen_Slave_HEARTBEAT_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT.h"

/* Layers */
#include "../../Hardware/CAN_Network_Layer/CAN_Network_Layer.h"

STATUS_CODE CANopen_Producer_HEARTBEAT_Transmit_Status_Operation(CANopen *canopen){
	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_HEARTBEAT << 7 | canopen->producer.heartbeat.from_node_ID;

	/* Get toggle */
	canopen->producer.heartbeat.toggle_heartbeat = canopen->producer.heartbeat.toggle_heartbeat == TOGGLE_HEARTBEAT_0 ? TOGGLE_HEARTBEAT_1 : TOGGLE_HEARTBEAT_0;

	/* Send the heartbeat message */
	uint8_t data[8] = {0};
	data[0] = (canopen->producer.heartbeat.toggle_heartbeat << 7) | canopen->producer.heartbeat.status_operational;
	return CAN_Send_Message(COB_ID, data);
}

