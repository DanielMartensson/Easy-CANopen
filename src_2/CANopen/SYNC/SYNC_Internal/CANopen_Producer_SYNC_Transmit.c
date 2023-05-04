/*
 * CANopen_Producer_SYNC_Transmit.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SYNC_Internal.h"

/* Layers */
#include "SYNC_Protocol/SYNC_Protocol.h"

void CANopen_Producer_SYNC_Transmit_Synchronization(CANopen *canopen){
	/* Check if this is slave node */
	uint8_t node_ID = canopen->slave.this_node_ID;
	if(node_ID > 0)
		return; /* This is slave node - Cannot send */

	/* Check is valid */
	uint8_t valid = canopen->od_communication.COB_ID_sync_message >> 31;
	if(valid == 1)
		return; /* Not valid */

	/* Check if SYNC service is enabled */
	if(canopen->master.nmt.this_node_status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. SYNC service is disabled */
	CANopen_SYNC_Protocol_Produce_Synchronization(canopen);
}
