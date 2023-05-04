/*
 * CANopen_LSS_Protocol_Receive_Request.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS_Protocol.h"

/* Layers */
#include "../../../../Hardware/Hardware.h"
#include "../LSS_Internal.h"

void CANopen_LSS_Protocol_Receive_Request_Switch_Mode_Global(CANopen *canopen, uint8_t data[]){
	canopen->slave.lss.switch_mode_global_protocol = data[1]; 									/* Save the mode */
}

void CANopen_LSS_Protocol_Receive_Request_Switch_Mode_Selective_Value(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Save parameter */
	uint8_t cs = data[0];
	uint32_t value = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	if(cs == CS_LSS_SWITCH_MODE_SELECTIVE_VENDOR_ID)
		canopen->od_communication.vendor_ID = value;
	else if(cs == CS_LSS_SWITCH_MODE_SELECTIVE_PRODUCT_CODE)
		canopen->od_communication.product_code = value;
	else if(cs == CS_LSS_SWITCH_MODE_SELECTIVE_REVISION_NUMBER)
		canopen->od_communication.revision_number = value;
	else if(cs == CS_LSS_SWITCH_MODE_SELECTIVE_SERIAL_NUMBER)
		canopen->od_communication.serial_number = value;

	/* Response */
	CANopen_Slave_LSS_Transmit_Response_Switch_Mode_Selective_Value();
}

void CANopen_LSS_Protocol_Receive_Request_Configure_Node_ID(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Check parameter */
	uint8_t node_ID = data[1];
	if(node_ID == 0 || node_ID > 127){
		/* Node ID 0 is master ID and node ID cannot be larger than 127 */
		CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_LSS_CONFIGURE_NODE_ID, STATUS_CODE_INVALID_PARAMETER, 0x0);
		return;
	}

	/* Save the parameter and give a OK response back */
	canopen->slave.this_node_ID = node_ID;
	CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_LSS_CONFIGURE_NODE_ID, STATUS_CODE_SUCCESSFUL, 0x0);
}

void CANopen_LSS_Protocol_Receive_Request_Configure_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Check parameter */
	uint8_t table_index = data[2];
	if(table_index > TABLE_INDEX_8_BAUD_RATE_10){
		/* Outside of the table index */
		CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_LSS_CONFIGURE_BIT_TIMING_PARAMETERS, STATUS_CODE_INVALID_PARAMETER, 0x0);
		return;
	}

	/* Save the parameter and give a OK response back */
	canopen->slave.this_node_table_index = table_index;
	CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_LSS_CONFIGURE_BIT_TIMING_PARAMETERS, STATUS_CODE_SUCCESSFUL, 0x0);
}

void CANopen_LSS_Protocol_Receive_Request_Activate_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Set the baud rate - No response back according to CiA standard */
	CAN_Set_Baud_Rate(canopen->slave.this_node_table_index);
}

void CANopen_LSS_Protocol_Receive_Request_Store_Configuration(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Save the bit timing table index and the node ID */
	uint8_t node_ID_table_index[2] = {canopen->slave.this_node_ID, canopen->slave.this_node_table_index};
	Hardware_Memory_Save_Bytes(node_ID_table_index, sizeof(node_ID_table_index), UINT8_T_ARRAY_NODE_ID_TABLE_INDEX);

	/* Send OK response back */
	CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_LSS_STORE_CONFIGURATION_PROTOCOL, STATUS_CODE_SUCCESSFUL, 0x0);
}

void CANopen_LSS_Protocol_Receive_Request_Inquire_Identity_Value(CANopen *canopen, uint8_t data[]){
	/* Get cs and find value */
	uint8_t cs = data[0];
	uint32_t value = 0;
	if(cs == CS_LSS_INQUIRE_IDENTITY_VENDOR_ID)
		value = canopen->od_communication.vendor_ID;
	else if(cs == CS_LSS_INQUIRE_IDENTITY_PRODUCT_CODE)
		value = canopen->od_communication.product_code;
	else if(cs == CS_LSS_INQUIRE_IDENTITY_REVISION_NUMBER)
		value = canopen->od_communication.revision_number;
	else if(cs == CS_LSS_INQUIRE_IDENTITY_SERIAL_NUMBER)
		value = canopen->od_communication.serial_number;
	else if(cs == CS_LSS_INQUIRE_IDENTITY_NODE_ID)
		value = canopen->slave.this_node_ID;

	/* Send identity response back */
	CANopen_Slave_LSS_Transmit_Response_Inquire_Identity_Value(cs, value);
}

void CANopen_LSS_Protocol_Receive_Request_Identity_Remote_Slave_Value(CANopen *canopen, uint8_t data[]){
	/* Get the value and compare */
	uint8_t cs = data[0];
	uint32_t compare = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_VENDOR_ID){
		if(canopen->od_communication.vendor_ID == compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
	}else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_PRODUCT_CODE){
		if(canopen->od_communication.product_code == compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
	}else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_LOW){
		if(canopen->od_communication.revision_number < compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
	}else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_HIGH){
		if(canopen->od_communication.revision_number > compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
	}else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_SERIAL_NUMBER_LOW){
		if(canopen->od_communication.serial_number < compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
	}else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_SERIAL_NUMBER_HIGH){
		if(canopen->od_communication.serial_number > compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
	}
}

void CANopen_LSS_Protocol_Receive_Request_Identify_Non_Configured_Remote_Slave(CANopen *canopen, uint8_t data[]){
	/* Check if node ID is on the error address */
	if(canopen->slave.this_node_ID == 0xFF)
		CANopen_Slave_LSS_Transmit_Response_Identify_Non_Configured_Remote_Slave();
}
