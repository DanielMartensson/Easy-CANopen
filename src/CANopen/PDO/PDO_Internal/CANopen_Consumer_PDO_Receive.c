/*
 * CANopen_Consumer_PDO_Receive.c
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "PDO_Internal.h"

/* Layers */
#include "PDO_Protocol/PDO_Protocol.h"

void CANopen_Consumer_PDO_Receive_Data(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Bring the index number */
	uint8_t index;
	for(index = 0; index < PDO_LENGTH; index++)
		if((canopen->od_communication.PDO_communication_receive[index].COB_ID & 0x7F) == node_ID)
			break; /* Now we got the index number */

	/* Load in the data */
	CANopen_PDO_Protocol_Consume_Data(canopen, &canopen->od_communication.PDO_mapping_receive[index], data);
}


