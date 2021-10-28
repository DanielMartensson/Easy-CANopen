/*
 * CANopen_Producer_SYNC_Transmit.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SYNC.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Producer_SYNC_Transmit_Synchronization(CANopen *canopen, uint8_t counter){
	/* Check if SYNC service is enabled */
	if(canopen->master.nmt.status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. SYNC service is disabled */

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_SYNC_EMCY << 7; /* Node ID is zero here */

	/* Send the data */
	uint8_t data[8] = {0};
	data[0] = counter; /* TODO: Hur ska vi tolka counter ? */
	Hardware_CAN_Send_Message(COB_ID, data);
}

