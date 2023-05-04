/*
 * CANopen_NMT_Protocol_Receive_Request.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "NMT_Protocol.h"

/* Layers */
#include "../../../HEARTBEAT/HEARTBEAT_Internal/HEARTBEAT_Internal.h"

void CANopen_NMT_Protocol_Receive_Request_Enter_Status(CANopen *canopen, uint8_t status){
	canopen->slave.nmt.this_node_status_operational = status;
}

void CANopen_NMT_Protocol_Receive_Request_Node_Reset(CANopen *canopen){
	/* Reset the whole canopen struct */
	memset(canopen, 0, sizeof(CANopen));
	canopen->slave.nmt.this_node_status_operational = STATUS_OPERATIONAL_STOPPED;

	/* Restore the communication struct */
	CANopen_NMT_Protocol_Receive_Request_Restore_Communication_Parameters(canopen);

	/* Send out a boot up message via HEARTBEAT service */
	CANopen_Producer_HEARTBEAT_Transmit_Bootup_Message(canopen);

	/* Activate the following services: PDO, SDO, SYNC, TIME, EMCY */
	canopen->slave.nmt.this_node_status_operational = STATUS_OPERATIONAL_OPERATIONAL;
}

void CANopen_NMT_Protocol_Receive_Request_Restore_Communication_Parameters(CANopen *canopen){
	/* Clear the OD communication parameters */
	memset(&canopen->od_communication, 0, sizeof(struct OD_Communication));
	canopen->od_communication.store_parameters[0] = 0x3;
	canopen->od_communication.restore_default_parameters[0] = 0x3;
	canopen->od_communication.error_behavior_object[0] = 0x1;
	canopen->od_communication.consumer_heartbeat_time[0] = 0x7F;
	canopen->od_communication.emergency_consumer_object[0] = 0x7F;
}
