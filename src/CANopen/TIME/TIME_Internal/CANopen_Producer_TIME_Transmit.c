/*
 * CANopen_Producer_TIME_Transmit.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "TIME_Internal.h"

/* Layers */
#include "TIME_Protocol/TIME_Protocol.h"

void CANopen_Producer_TIME_Transmit_Clock(CANopen *canopen){
	/* Check if TIME service is enabled */
	if(canopen->master.nmt.status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. TIME service is disabled */
	CANopen_TIME_Protocol_Produce_Clock(canopen);
}
