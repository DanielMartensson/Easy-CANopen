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
	uint32_t this_node_ID = 0;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_NODE_ID, OD_SUB_INDEX_0, &this_node_ID);
	if(node_ID == this_node_ID){
		/* Set operational status */
		canopen->slave.nmt.status_operational = data[0];

		/* Shutdown or enable */
		if(canopen->slave.nmt.status_operational == CS_NETWORK_MANAGMENT_SERVICE_START_REMOTE_NODE){
			/* Enable the following services: PDO, SDO, SYNC, TIME, EMCY */
			/* TODO: fyll på här */
			service_EMCY_configuration(canopen, node_ID, false);
			service_TIME_configuration(canopen, node_ID, true, false);
			canopen->slave.nmt.status_operational = STATUS_OPERATIONAL_NORMAL_OPERATIONAL;
		}else if(canopen->slave.nmt.status_operational == CS_NETWORK_MANAGMENT_SERVICE_STOP_REMOTE_NODE){
			/* Stop the following services: PDO, SDO, SYNC, TIME, EMCY */
			/* TODO: fyll på här */
			service_EMCY_configuration(canopen, node_ID, true);
			service_TIME_configuration(canopen, node_ID, false, false);
			canopen->slave.nmt.status_operational = STATUS_OPERATIONAL_IS_STOPPED;
		}else if(canopen->slave.nmt.status_operational == CS_NETWORK_MANAGMENT_SERVICE_ENTER_PRE_OPERATIONAL){
			/* Stop the following services: PDO */
			/* TODO: Disable PDO only */
			canopen->slave.nmt.status_operational = STATUS_OPERATIONAL_ENTER_PRE_OPERATIONAL;
		}else if(canopen->slave.nmt.status_operational == CS_NETWORK_MANAGMENT_SERVICE_RESET_COMMUNICATION){
			Easy_CANopen_Load_Dictionary_Objects(canopen);
		}else if(canopen->slave.nmt.status_operational == CS_NETWORK_MANAGMENT_SERVICE_RESET_NODE){
			Easy_CANopen_Load_Node_Configuration(canopen);
			Easy_CANopen_Load_Dictionary_Objects(canopen);
		}
	}
}

static void service_TIME_configuration(CANopen *canopen, uint8_t node_ID, bool canopen_device_consumes_TIME_message, bool canopen_device_produces_TIME_message){
	uint32_t value = (canopen_device_consumes_TIME_message << 31) | (canopen_device_produces_TIME_message << 30) | (CAN_ID_BITS_LENGTH << 29) | (FUNCTION_CODE_NMT << 7) | node_ID;
	CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_COB_ID_TIME_STAMP_OBJECT, OD_SUB_INDEX_0, value);
}

static void service_EMCY_configuration(CANopen *canopen, uint8_t node_ID, bool EMCY_does_not_exist){
	uint32_t value = (EMCY_does_not_exist << 31) | (CAN_ID_BITS_LENGTH << 29) | (FUNCTION_CODE_SYNC_EMCY << 7) | node_ID;
	CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_COB_ID_EMCY, OD_SUB_INDEX_0, value);
}

