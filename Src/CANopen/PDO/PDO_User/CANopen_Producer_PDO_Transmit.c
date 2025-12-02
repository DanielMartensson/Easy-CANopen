/*
 * CANopen_Producer_PDO_Transmit.c
 *
 *  Created on: 02 Dec. 2025
 *      Author: Daniel Mårtensson
 */

#include "PDO_User.h"

/* Layers */
#include "../PDO_Internal/PDO_Internal.h"

void CANopen_Producer_PDO_Transmit_Event(CANopen *canopen){
	/* Check if PDO service is enabled */
	if(canopen->slave.nmt.this_node_status_operational != STATUS_OPERATIONAL_OPERATIONAL)
		return; /* NMT is not in operational mode. PDO service is disabled */

	/* Transmit the preset data inside the struct */
	CANopen_Producer_PDO_Transmit_Data(canopen);
}
