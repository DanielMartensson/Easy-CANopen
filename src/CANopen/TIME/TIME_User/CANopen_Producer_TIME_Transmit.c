/*
 * CANopen_Producer_TIME_Transmit.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */


#include "TIME.h"

/* Layers */
#include "../../Hardware/Hardware.h"
#include "../TIME_Internal/TIME_Internal.h"

void CANopen_Producer_TIME_Transmit_Clock(CANopen *canopen){
	/* Check if TIME service is enabled */
	if(canopen->master.nmt.status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. TIME service is disabled */

	/* Create stamp */
	uint8_t data[8] = {0};
	CANopen_TIME_Protocol_Stamp_Create(canopen, data);

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_TIME << 7;	/* Only the master node send out this message */

	/* Send the message to client */
	Hardware_CAN_Send_Message(COB_ID, data);
}
