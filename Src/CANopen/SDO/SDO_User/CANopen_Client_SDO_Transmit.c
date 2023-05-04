/*
 * CANopen_Client_SDO_Transmit.c
 *
 *  Created on: 24 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO_User.h"

/* Layers */
#include "../SDO_Internal/SDO_Protocol/SDO_Protocol.h"

void CANopen_Client_SDO_Transmit_Request(CANopen *canopen, uint8_t cs, uint8_t node_ID, uint16_t index, uint8_t sub_index, uint32_t value){
	/* Check if SDO service is enabled */
	if(canopen->slave.nmt.this_node_status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. SDO service is disabled */
	CANopen_SDO_Protocol_Transmit_Request_Initiate(canopen, cs, node_ID, index, sub_index, value);
}
