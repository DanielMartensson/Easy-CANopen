/*
 * CANopen_Slave_NMT_Receive.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "NMT_Internal.h"

/* Layers */
#include "NMT_Protocol/NMT_Protocol.h"

void CANopen_Slave_NMT_Receive(CANopen *canopen, uint8_t data[]){

	/* Get the command specifier and node ID */
	uint8_t cs = data[0];
	uint8_t node_ID = data[1];

	/* Check if it's correct node address we are sending to */
	if(node_ID == canopen->slave.this_node_ID){
		if(cs == CS_NETWORK_MANAGMENT_SERVICE_START_REMOTE_NODE)
			CANopen_NMT_Protocol_Receive_Request_Enter_Status(canopen, STATUS_OPERATIONAL_OPERATIONAL);		/* Activate the following services: PDO, SDO, SYNC, TIME, EMCY */
		else if(cs == CS_NETWORK_MANAGMENT_SERVICE_STOP_REMOTE_NODE)
			CANopen_NMT_Protocol_Receive_Request_Enter_Status(canopen, STATUS_OPERATIONAL_STOPPED);			/* Deactivate the following services: PDO, SDO, SYNC, TIME, EMCY */
		else if(cs == CS_NETWORK_MANAGMENT_SERVICE_ENTER_PRE_OPERATIONAL)
			CANopen_NMT_Protocol_Receive_Request_Enter_Status(canopen, STATUS_OPERATIONAL_PRE_OPERATIONAL);	/* Deactivate the following services: PDO */
		else if(cs == CS_NETWORK_MANAGMENT_SERVICE_RESET_COMMUNICATION)
			CANopen_NMT_Protocol_Receive_Request_Restore_Communication_Parameters(canopen);					/* Restore the communication objects to default */
		else if(cs == CS_NETWORK_MANAGMENT_SERVICE_RESET_NODE)
			CANopen_NMT_Protocol_Receive_Request_Node_Reset(canopen);										/* Reset node struct and re-initilize it to default parameters */
	}
}
