/*
 * CANopen_Producer_SYNC_Transmit.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SYNC.h"

void CANopen_Producer_SYNC_Transmit_Synchronization(CANopen *canopen){
	/* Check if SYNC service is enabled */
	if(canopen->slave.nmt.status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. SYNC service is disabled */


}

