/*
 * CANopen_Producer_PDO_Transmit.c
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "PDO_Internal.h"

/* Layers */
#include "PDO_Protocol/PDO_Protocol.h"

void CANopen_Producer_PDO_Transmit_Data(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Check if PDO service is enabled */
	if(canopen->slave.nmt.status_operational != STATUS_OPERATIONAL_OPERATIONAL)
		return; /* NMT is not in operational mode. PDO service is disabled */


}
