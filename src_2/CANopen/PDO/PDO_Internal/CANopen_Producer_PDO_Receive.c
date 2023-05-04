/*
 * CANopen_Producer_PDO_Receive.c
 *
 *  Created on: 14 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "PDO_Internal.h"

/* Layers */
#include "PDO_Protocol/PDO_Protocol.h"

void CANopen_Producer_PDO_Receive_Request(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Check if PDO service is enabled */
	if(canopen->slave.nmt.this_node_status_operational != STATUS_OPERATIONAL_OPERATIONAL)
		return; /* NMT is not in operational mode. PDO service is disabled */

	/* Check if it's correct node ID */
	if(node_ID != canopen->slave.this_node_ID)
		return; /* Nope */

	/* A PDO request has zero bytes */
	uint16_t total_bytes = 0;
	for(uint8_t i = 0; i < 8; i++)
		total_bytes += data[i];
	if(total_bytes != 0)
		return; /* Nope */

	/* Bring the index number */
	uint8_t index;
	for(index = 0; index < PDO_LENGTH; index++)
		if((canopen->od_communication.PDO_communication_receive[index].COB_ID & 0x7F) == node_ID)
			break; /* Now we got the index number */

	/* Check if we have the RTR transmission type - RTR event driven */
	if(canopen->od_communication.PDO_communication_receive[index].transmission_type != 0xFD)
		return; /* Nope */

	/* Transmit */
	uint16_t CAN_ID = canopen->od_communication.PDO_communication_transmit[index].COB_ID & 0x7FF;
	CANopen_PDO_Protocol_Produce_Data(canopen, CAN_ID, &canopen->od_communication.PDO_mapping_transmit[index]);
}
