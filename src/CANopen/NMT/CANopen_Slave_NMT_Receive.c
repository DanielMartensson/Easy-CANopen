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
 * NMT service disables, enables, initialize and restart at a node
 */
void CANopen_Slave_NMT_Receive(CANopen *canopen, uint8_t data[]){
	/* Get the node ID */
	uint8_t node_ID = data[1];

	/* Check if it's correct node we are sending to */
	if(node_ID == canopen->od_manufacturer.node_ID){
		/* Enter the states */
		if(data[0] == CS_NETWORK_MANAGMENT_SERVICE_START_REMOTE_NODE){
			/* TODO: Aktivera */
			canopen->nmt_slave.status_operational = STATUS_OPERATIONAL_OPERATIONAL;		/* Enable the following services: PDO, SDO, SYNC, TIME, EMCY, HEARTBEAT, GUARD */
		}else if(data[0] == CS_NETWORK_MANAGMENT_SERVICE_STOP_REMOTE_NODE){
			/* TODO: Avaktivera */
			canopen->nmt_slave.status_operational = STATUS_OPERATIONAL_STOPPED;			/* Stop the following services: PDO, SDO, SYNC, TIME, EMCY */
		}else if(data[0] == CS_NETWORK_MANAGMENT_SERVICE_ENTER_PRE_OPERATIONAL){
			/* TODO: Avaktivera PDO */
			canopen->nmt_slave.status_operational = STATUS_OPERATIONAL_PRE_OPERATIONAL; /* Stop the following services: PDO */
		}else if(data[0] == CS_NETWORK_MANAGMENT_SERVICE_RESET_COMMUNICATION){
			/* TODO: Läs hur vi ska ladda in variablerna för struct->od_communication */
		}else if(data[0] == CS_NETWORK_MANAGMENT_SERVICE_RESET_NODE){
			/* TODO: Ladda om hela EasyCANopen */
		}
	}
}
