/*
 * CANopen_Slave_NMT_Receive.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "NMT.h"

/* Layers */
#include "../../Hardware/Hardware.h"

/*
 * NMT service disables, enables, initialize and restart parameters at a node
 */
void CANopen_Slave_NMT_Receive(CANopen *canopen, uint8_t data[]){

	/* Get the command specifier and node ID */
	uint8_t cs = data[0];
	uint8_t node_ID = data[1];

	/* Check if it's correct node address we are sending to */
	if(node_ID == canopen->slave.lss.this_node_ID){
		/* Enter the states */
		if(cs == CS_NETWORK_MANAGMENT_SERVICE_START_REMOTE_NODE){
			canopen->slave.nmt.status_operational = STATUS_OPERATIONAL_OPERATIONAL;			/* Activate the following services: PDO, SDO, SYNC, TIME, EMCY */
		}else if(cs == CS_NETWORK_MANAGMENT_SERVICE_STOP_REMOTE_NODE){
			canopen->slave.nmt.status_operational = STATUS_OPERATIONAL_STOPPED;				/* Deactivate the following services: PDO, SDO, SYNC, TIME, EMCY */
		}else if(cs == CS_NETWORK_MANAGMENT_SERVICE_ENTER_PRE_OPERATIONAL){
			canopen->slave.nmt.status_operational = STATUS_OPERATIONAL_PRE_OPERATIONAL;		/* Deactivate the following services: PDO */
		}else if(cs == CS_NETWORK_MANAGMENT_SERVICE_RESET_COMMUNICATION){
			CANopen_Slave_NMT_Restore_OD_Communication_To_Default_Parameters(canopen);		/* Restore the communication objects to default */
		}else if(cs == CS_NETWORK_MANAGMENT_SERVICE_RESET_NODE){
			CANopen_Slave_NMT_Reset_Node_Struct(canopen);									/* Reset node struct and re-initilize it to default parameters */
		}
	}
}

void CANopen_Slave_NMT_Restore_OD_Communication_To_Default_Parameters(CANopen *canopen){
	memset(&canopen->od_communication, 0, sizeof(struct OD_Communication));
	canopen->od_communication.store_parameters[0] = 0x3;
	canopen->od_communication.restore_default_parameters[0] = 0x3;
	canopen->od_communication.error_behavior_object[0] = 0x1;
	canopen->od_communication.consumer_heartbeat_time[0] = 0x7F;
	canopen->od_communication.emergency_consumer_object[0] = 0x7F;
}

void CANopen_Slave_NMT_Reset_Node_Struct(CANopen *canopen){
	/* Reset the whole canopen struct */
	memset(canopen, 0, sizeof(CANopen));
	canopen->slave.nmt.status_operational = STATUS_OPERATIONAL_STOPPED;

	/* Restore the communication struct */
	CANopen_Slave_NMT_Restore_OD_Communication_To_Default_Parameters(canopen);

	/* Send out a boot up message via HEARTBEAT service */
	canopen->slave.nmt.status_operational = STATUS_OPERATIONAL_BOOT_UP;
	CANopen_Producer_HEARTBEAT_Transmit_Heartbeat(canopen);

	/* Activate the following services: PDO, SDO, SYNC, TIME, EMCY */
	canopen->slave.nmt.status_operational = STATUS_OPERATIONAL_OPERATIONAL;
}
