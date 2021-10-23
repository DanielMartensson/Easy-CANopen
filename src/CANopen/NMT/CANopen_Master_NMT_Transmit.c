/*
 * CANopen_Master_NMT_Transmit.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "NMT.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Master_NMT_Transmit_Operation_State(CANopen *canopen, uint8_t cs, uint8_t node_ID){
	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_NMT << 7 | node_ID;

	/* Send the data */
	uint8_t data[8] = {0};
	data[0] = cs;
	data[1] = node_ID;
	Hardware_CAN_Send_Message(COB_ID, data);
}
