/*
 * CANopen_Producer_SYNC_Transmit.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SYNC.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Producer_SYNC_Transmit_Synchronization(CANopen *canopen, uint8_t node_ID, uint8_t counter){
	/* Check if SYNC service is enabled */
	if(canopen->slave.nmt.status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. SYNC service is disabled */

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_SYNC_EMCY << 7 | node_ID;

	/* Send the data */
	uint8_t data[8] = {0};
	data[0] = counter;
	Hardware_CAN_Send_Message(COB_ID, data);
}

