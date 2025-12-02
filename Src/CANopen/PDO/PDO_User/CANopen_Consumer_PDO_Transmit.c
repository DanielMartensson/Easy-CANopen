/*
 * CANopen_Consumer_PDO_Transmit.c
 *
 *  Created on: 15 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "PDO_User.h"

/* Layers */
#include "../PDO_Internal/PDO_Protocol/PDO_Protocol.h"

void CANopen_Consumer_PDO_Transmit_Request(CANopen *canopen, uint8_t node_ID){
	/* Check if PDO service is enabled */
	if(canopen->slave.nmt.this_node_status_operational != STATUS_OPERATIONAL_OPERATIONAL)
		return; /* NMT is not in operational mode. PDO service is disabled */

	/* Get CAN_ID */
	uint16_t CAN_ID = 0;
	for(uint8_t i = 0; i < PDO_LENGTH; i++){
		if((canopen->od_communication.PDO_communication_receive[i].COB_ID & 0x7F) == node_ID){
			CAN_ID = canopen->od_communication.PDO_communication_receive[i].COB_ID;
			break;
		}
	}

	/* Transmit request */
	CANopen_PDO_Protocol_Produce_Request(CAN_ID);
}
