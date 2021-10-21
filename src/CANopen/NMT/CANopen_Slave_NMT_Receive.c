/*
 * CANopen_Slave_NMT_Receive.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "NMT.h"

/* Layers */
#include "../OD/OD.h"
#include "../../Hardware/Hardware.h"

/* Private functions */
static void service_TIME_configuration(CANopen *canopen, uint8_t node_ID, bool canopen_device_consumes_TIME_message, bool canopen_device_produces_TIME_message);
static void service_EMCY_configuration(CANopen *canopen, uint8_t node_ID, bool EMCY_does_not_exist);

void CANopen_Slave_NMT_Receive(CANopen *canopen, uint8_t data[]){
	/* Get the node ID */
	uint8_t node_ID = data[1];

	/* Check if it's correct node ID */
	uint32_t this_node_ID = canopen->od_manufacturer.node_ID;
	if(node_ID == this_node_ID){
		/* Set operational status */
		canopen->nmt_slave.status_operational = data[0];

		/* Shutdown or enable */
		if(canopen->nmt_slave.status_operational == CS_NETWORK_MANAGMENT_SERVICE_START_REMOTE_NODE){
			/* Enable the following services: PDO, SDO, SYNC, TIME, EMCY */
			/* TODO: fyll på här */
			service_EMCY_configuration(canopen, node_ID, false);
			service_TIME_configuration(canopen, node_ID, true, false);
			canopen->nmt_slave.status_operational = STATUS_OPERATIONAL_NORMAL_OPERATIONAL;
		}else if(canopen->nmt_slave.status_operational == CS_NETWORK_MANAGMENT_SERVICE_STOP_REMOTE_NODE){
			/* Stop the following services: PDO, SDO, SYNC, TIME, EMCY */
			/* TODO: fyll på här */
			service_EMCY_configuration(canopen, node_ID, true);
			service_TIME_configuration(canopen, node_ID, false, false);
			canopen->nmt_slave.status_operational = STATUS_OPERATIONAL_IS_STOPPED;
		}else if(canopen->nmt_slave.status_operational == CS_NETWORK_MANAGMENT_SERVICE_ENTER_PRE_OPERATIONAL){
			/* Stop the following services: PDO */
			/* TODO: Disable PDO only */
			canopen->nmt_slave.status_operational = STATUS_OPERATIONAL_ENTER_PRE_OPERATIONAL;
		}else if(canopen->nmt_slave.status_operational == CS_NETWORK_MANAGMENT_SERVICE_RESET_COMMUNICATION){
			Easy_CANopen_Load_Dictionary_Objects(canopen);
		}else if(canopen->nmt_slave.status_operational == CS_NETWORK_MANAGMENT_SERVICE_RESET_NODE){
			Easy_CANopen_Load_Node_Configuration(canopen);
			Easy_CANopen_Load_Dictionary_Objects(canopen);
		}
	}
}

static void service_TIME_configuration(CANopen *canopen, uint8_t node_ID, bool canopen_device_consumes_TIME_message, bool canopen_device_produces_TIME_message){
	canopen->od_communication.COB_ID_time_stamp_object = (canopen_device_consumes_TIME_message << 31) | (canopen_device_produces_TIME_message << 30) | (CAN_ID_BITS_LENGTH << 29) | (FUNCTION_CODE_NMT << 7) | node_ID;
}

static void service_EMCY_configuration(CANopen *canopen, uint8_t node_ID, bool EMCY_does_not_exist){
	canopen->od_communication.COB_ID_emcy = (EMCY_does_not_exist << 31) | (CAN_ID_BITS_LENGTH << 29) | (FUNCTION_CODE_SYNC_EMCY << 7) | node_ID;
}

