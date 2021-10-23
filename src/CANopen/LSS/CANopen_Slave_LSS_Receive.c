/*
 * CANopen_Slave_LSS_Receive.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS.h"

/* Layers */
#include "../../Hardware/Hardware.h"

static void CANopen_Slave_LSS_Receive_Request_Switch_Mode_Global(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Switch_Mode_Selective_Value(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Configure_Node_ID(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Configure_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Activate_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Store_Configuration(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Inquire_Identity_Value(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Identity_Remote_Slave_Value(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Identify_Non_Configured_Remote_Slave(CANopen *canopen, uint8_t data[]);

void CANopen_Slave_LSS_Receive(CANopen *canopen, uint8_t data[]){
	uint8_t cs = data[0];
	if(cs == CS_SWITCH_MODE_GLOBAL){
		return CANopen_Slave_LSS_Receive_Request_Switch_Mode_Global(canopen, data);
	}else if(cs == CS_SWITCH_MODE_SELECTIVE){
		CANopen_Slave_LSS_Receive_Request_Switch_Mode_Selective_Value(canopen, data);
	}else if(cs == CS_CONFIGURE_NODE_ID){
		CANopen_Slave_LSS_Receive_Request_Configure_Node_ID(canopen, data);
	}else if(cs == CS_CONFIGURE_BIT_TIMING_PARAMETERS){
		CANopen_Slave_LSS_Receive_Request_Configure_Bit_Timing_Parameters(canopen, data);
	}else if(cs == CS_ACTIVATE_BIT_TIMING_PARAMETERS){
		CANopen_Slave_LSS_Receive_Request_Activate_Bit_Timing_Parameters(canopen, data);
	}else if(cs == CS_STORE_CONFIGURATION_PROTOCOL){
		CANopen_Slave_LSS_Receive_Request_Store_Configuration(canopen, data);
	}else if(cs == CS_INQUIRE_IDENTITY){
		CANopen_Slave_LSS_Receive_Request_Inquire_Identity_Value(canopen, data);
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE){
		CANopen_Slave_LSS_Receive_Request_Identity_Remote_Slave_Value(canopen, data);
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_NON_CONFIGURED){
		CANopen_Slave_LSS_Receive_Request_Identify_Non_Configured_Remote_Slave(canopen, data);
	}
}

static void CANopen_Slave_LSS_Receive_Request_Switch_Mode_Global(CANopen *canopen, uint8_t data[]){
	canopen->lss_slave.switch_mode_global_protocol = data[0];
}

static void CANopen_Slave_LSS_Receive_Request_Switch_Mode_Selective_Value(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->lss_slave.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Save parameter */
	uint8_t cs = data[0];
	uint32_t value = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	if(cs == CS_INQUIRE_IDENTITY_VENDOR_ID)
		canopen->od_communication.identity_object[1] = value;
	else if(cs == CS_INQUIRE_IDENTITY_PRODUCT_CODE)
		canopen->od_communication.identity_object[2] = value;
	else if(cs == CS_INQUIRE_IDENTITY_REVISION_NUMBER)
		canopen->od_communication.identity_object[3] = value;
	else if(cs == CS_INQUIRE_IDENTITY_SERIAL_NUMBER)
		canopen->od_communication.identity_object[4] = value;

	/* Response */
	CANopen_Slave_LSS_Transmit_Response_Switch_Mode_Selective_Value();
}

static void CANopen_Slave_LSS_Receive_Request_Configure_Node_ID(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->lss_slave.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Check parameter */
	uint8_t node_ID = data[1];
	if(node_ID == 0 || node_ID > 127){
		/* Node ID 0 is master ID and node ID cannot be larger than 127 */
		return CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_CONFIGURE_NODE_ID, STATUS_CODE_INVALID_PARAMETER, 0x0);
	}

	/* Save the parameter and give a OK response back */
	canopen->lss_slave.node_ID = node_ID;
	CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_CONFIGURE_NODE_ID, STATUS_CODE_SUCCESSFUL, 0x0);
}

static void CANopen_Slave_LSS_Receive_Request_Configure_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->lss_slave.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Check parameter */
	uint8_t table_index = data[2];
	if(table_index > TABLE_INDEX_8_BAUD_RATE_10){
		/* Outside of the table index */
		return CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_CONFIGURE_BIT_TIMING_PARAMETERS, STATUS_CODE_INVALID_PARAMETER, 0x0);
	}

	/* Save the parameter and give a OK response back */
	canopen->lss_slave.table_index = table_index;
	CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_CONFIGURE_BIT_TIMING_PARAMETERS, STATUS_CODE_SUCCESSFUL, 0x0);
}

static void CANopen_Slave_LSS_Receive_Request_Activate_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->lss_slave.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Set the baud rate - No response back according to CiA standard */
	CAN_Set_Baud_Rate(canopen->lss_slave.table_index);
}

static void CANopen_Slave_LSS_Receive_Request_Store_Configuration(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->lss_slave.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Save the bit timing table index and the node ID */
	canopen->od_manufacturer.bit_timing_table_index = canopen->lss_slave.table_index;
	canopen->od_manufacturer.node_ID = canopen->lss_slave.node_ID;

	/* Send OK response back */
	CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_STORE_CONFIGURATION_PROTOCOL, STATUS_CODE_SUCCESSFUL, 0x0);
}

static void CANopen_Slave_LSS_Receive_Request_Inquire_Identity_Value(CANopen *canopen, uint8_t data[]){
	/* Get cs and find value */
	uint8_t cs = data[0];
	uint32_t value = 0;
	if(cs == CS_INQUIRE_IDENTITY_VENDOR_ID)
		value = canopen->od_communication.identity_object[1];
	else if(cs == CS_INQUIRE_IDENTITY_PRODUCT_CODE)
		value = canopen->od_communication.identity_object[2];
	else if(cs == CS_INQUIRE_IDENTITY_REVISION_NUMBER)
		value = canopen->od_communication.identity_object[3];
	else if(cs == CS_INQUIRE_IDENTITY_SERIAL_NUMBER)
		value = canopen->od_communication.identity_object[4];
	else if(cs == CS_INQUIRE_IDENTITY_NODE_ID)
		value = canopen->od_manufacturer.node_ID;

	/* Send identity response back */
	CANopen_Slave_LSS_Transmit_Response_Inquire_Identity_Value(cs, value);
}

static void CANopen_Slave_LSS_Receive_Request_Identity_Remote_Slave_Value(CANopen *canopen, uint8_t data[]){
	/* Get the value and compare */
	uint8_t cs = data[0];
	uint32_t compare = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	if(cs == CS_IDENTIFY_REMOTE_SLAVE_VENDOR_ID){
		if(canopen->od_communication.identity_object[1] == compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_PRODUCT_CODE){
		if(canopen->od_communication.identity_object[2] == compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_LOW){
		if(canopen->od_communication.identity_object[3] < compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_HIGH){
		if(canopen->od_communication.identity_object[3] > compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_SERIAL_NUMBER_LOW){
		if(canopen->od_communication.identity_object[4] < compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_SERIAL_NUMBER_HIGH){
		if(canopen->od_communication.identity_object[4] > compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
	}
}

static void CANopen_Slave_LSS_Receive_Request_Identify_Non_Configured_Remote_Slave(CANopen *canopen, uint8_t data[]){
	/* Check if node ID is on the error address */
	if(canopen->od_manufacturer.node_ID == 0xFF)
		CANopen_Slave_LSS_Transmit_Response_Identify_Non_Configured_Remote_Slave();
}
