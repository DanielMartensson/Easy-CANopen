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

	/* Get CAN ID */
	uint8_t index;
	for(index = 0; index < PDO_LENGTH; index++)
		if((canopen->od_communication.PDO_communication_receive[index].COB_ID & 0x7F) == node_ID)
			break; /* Now we got the index number */

	/* Transmit request */
	uint16_t CAN_ID = canopen->od_communication.PDO_communication_receive[index].COB_ID & 0x7F;
	CANopen_PDO_Protocol_Produce_Request(CAN_ID);
}
