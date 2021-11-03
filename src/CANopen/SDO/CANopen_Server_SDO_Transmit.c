/*
 * CANopen_Server_SDO_Transmit.c
 *
 *  Created on: 24 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Server_SDO_Transmit_Response(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_SDO_TRANSMIT << 7 | node_ID;

	/* Send the message to client */
	Hardware_CAN_Send_Message(COB_ID, data);
}
