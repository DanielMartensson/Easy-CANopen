/*
 * CANopen_Slave_HEARTBEAT_Transmit.c
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "HEARTBEAT.h"

/* Layers */
#include "../../Hardware/CAN_Network_Layer/CAN_Network_Layer.h"

STATUS_CODE CANopen_Slave_HEARTBEAT_Transmit_Status_Operation(CANopen *canopen, uint8_t status_heartbeat){
	/* Get the node ID */
	uint8_t node_ID;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_5, &node_ID);

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_HEARTBEAT << 7 | node_ID;

	/* Get toggle */
	canopen->toggle_heartbeat = canopen->toggle_heartbeat == TOGGLE_HEARTBEAT_0 ? TOGGLE_HEARTBEAT_1 : TOGGLE_HEARTBEAT_0;

	/* Send the heartbeat message */
	uint8_t data[8] = {0};
	data[0] = (canopen->toggle_heartbeat << 7) | status_heartbeat;
	return CAN_Send_Message(COB_ID, data);
}

