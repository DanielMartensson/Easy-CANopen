/*
 * CANopen_Slave_NMT_Receive.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "NMT_Internal.h"

/* Layers */
#include "NMT_Protocol/NMT_Protocol.h"

void CANopen_Slave_NMT_Receive_Request(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Check if it's correct node */
	if(data[1] != canopen->slave.this_node_ID)
		return;

	/* Get the command specifier and node ID */
	uint8_t cs = data[0];
	if(cs == CS_NMT_SERVICE_START_REMOTE_NODE)
		CANopen_NMT_Protocol_Receive_Request_Enter_Status(canopen, STATUS_OPERATIONAL_OPERATIONAL);		/* Activate the following services: PDO, SDO, SYNC, TIME, EMCY */
	else if(cs == CS_NMT_SERVICE_STOP_REMOTE_NODE)
		CANopen_NMT_Protocol_Receive_Request_Enter_Status(canopen, STATUS_OPERATIONAL_STOPPED);			/* Deactivate the following services: PDO, SDO, SYNC, TIME, EMCY */
	else if(cs == CS_NMT_SERVICE_ENTER_PRE_OPERATIONAL)
		CANopen_NMT_Protocol_Receive_Request_Enter_Status(canopen, STATUS_OPERATIONAL_PRE_OPERATIONAL);	/* Deactivate the following services: PDO */
	else if(cs == CS_NMT_SERVICE_RESET_COMMUNICATION)
		CANopen_NMT_Protocol_Receive_Request_Restore_Communication_Parameters(canopen);					/* Restore the communication objects to default */
	else if(cs == CS_NMT_SERVICE_RESET_NODE)
		CANopen_NMT_Protocol_Receive_Request_Node_Reset(canopen);										/* Reset node struct and re-initilize it to default parameters */

}
