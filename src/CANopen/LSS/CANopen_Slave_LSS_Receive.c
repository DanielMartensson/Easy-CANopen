/*
 * CANopen_Slave_LSS_Receive.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS.h"

static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Global_Protocol(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Value(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Configure_Protocol_Node_ID(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Configure_Protocol_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Activate_Protocol_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Store_Configuration_Protocol(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Inquire_Identity_Protocol_Value(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Identity_Remote_Slave_Protocol_Value(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Identify_Non_Configured_Remote_Slave_Protocol(CANopen *canopen, uint8_t data[]);

STATUS_CODE CANopen_Slave_LSS_Receive(CANopen *canopen, uint8_t data[]){
	if(data[0] == CS_SWITCH_MODE_GLOBAL_PROTOCOL){
		return CANopen_Slave_LSS_Receive_Switch_Mode_Global_Protocol(canopen, data);
	}else if(data[0] == CS_SWITCH_MODE_SELECTIVE_PROTOCOL_VENDOR_ID | CS_SWITCH_MODE_SELECTIVE_PROTOCOL_PRODUCT_CODE | CS_SWITCH_MODE_SELECTIVE_PROTOCOL_REVISION_NUMBER | CS_SWITCH_MODE_SELECTIVE_PROTOCOL_SERIAL_NUMBER){
		return CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Value(canopen, data);
	}else if(data[0] == CS_CONFIGURE_PROTOCOL_NODE_ID){
		return CANopen_Slave_LSS_Receive_Configure_Protocol_Node_ID(canopen, data);
	}else if(data[0] == CS_CONFIGURE_PROTOCOL_BIT_TIMING_PARAMETERS){
		return CANopen_Slave_LSS_Receive_Configure_Protocol_Bit_Timing_Parameters(canopen, data);
	}else if(data[0] == CS_ACTIVATE_PROTOCOL_BIT_TIMING_PARAMETERS){
		return CANopen_Slave_LSS_Receive_Activate_Protocol_Bit_Timing_Parameters(canopen, data);
	}else if(data[0] == CS_STORE_CONFIGURATION_PROTOCOL){
		return CANopen_Slave_LSS_Receive_Store_Configuration_Protocol(canopen, data);
	}else if(data[0] == CS_INQUIRE_IDENTITY_PROTOCOL_VENDOR_ID | CS_INQUIRE_IDENTITY_PROTOCOL_PRODUCT_CODE | CS_INQUIRE_IDENTITY_PROTOCOL_REVISION_NUMBER | CS_INQUIRE_IDENTITY_PROTOCOL_SERIAL_NUMBER | CS_INQUIRE_IDENTITY_PROTOCOL_NODE_ID){
		return CANopen_Slave_LSS_Receive_Inquire_Identity_Protocol_Value(canopen, data);
	}else if(data[0] == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_VENDOR_ID | CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_PRODUCT_CODE | CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_REVISION_NUMBER_LOW | CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_REVISION_NUMBER_HIGH | CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_SERIAL_NUMBER_LOW | CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_SERIAL_NUMBER_HIGH){
		return CANopen_Slave_LSS_Receive_Identity_Remote_Slave_Protocol_Value(canopen, data);
	}else if(data[0] == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_NON_CONFIGURED){
		return CANopen_Slave_LSS_Receive_Identify_Non_Configured_Remote_Slave_Protocol(canopen, data);
	}
	return STATUS_CODE_SUCCESSFUL;
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Global_Protocol(CANopen *canopen, uint8_t data[]){
	canopen->slave.lss.switch_mode_global_protocol = data[0];
	return STATUS_CODE_SUCCESSFUL;
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Value(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	/* Save parameter */
	uint8_t cs = data[0];
	if(data[0] == CS_INQUIRE_IDENTITY_PROTOCOL_VENDOR_ID)
		canopen->slave.lss.vendor_ID = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	else if(data[0] == CS_INQUIRE_IDENTITY_PROTOCOL_PRODUCT_CODE)
		canopen->slave.lss.product_code = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	else if(data[0] == CS_INQUIRE_IDENTITY_PROTOCOL_REVISION_NUMBER)
		canopen->slave.lss.revision_number = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	else if(data[0] == CS_INQUIRE_IDENTITY_PROTOCOL_SERIAL_NUMBER)
		canopen->slave.lss.serial_number = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	else if(data[0] == CS_INQUIRE_IDENTITY_PROTOCOL_NODE_ID)
		canopen->slave.lss.node_ID = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];

	/* Response */
	return CANopen_Slave_LSS_Transmit_Switch_Mode_Selective_Protocol_Value_Response(CS_SWITCH_MODE_SELECTIVE_PROTOCOL_RESPONSE);
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Configure_Protocol_Node_ID(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	/* Check parameter */
	uint8_t node_ID = data[1];
	if(node_ID == 0 || node_ID > 127){
		/* Node ID 0 is master ID and node ID cannot be larger than 127 */
		return CANopen_Slave_LSS_Transmit_Status_Response(CS_CONFIGURE_PROTOCOL_NODE_ID, STATUS_CODE_INVALID_PARAMETER, 0x0);
	}

	/* Save the parameter and give a OK response back */
	canopen->slave.lss.node_ID = node_ID;
	return CANopen_Slave_LSS_Transmit_Status_Response(CS_CONFIGURE_PROTOCOL_NODE_ID, STATUS_CODE_SUCCESSFUL, 0x0);
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Configure_Protocol_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	/* Check parameter */
	uint8_t table_index = data[2];
	if(table_index > TABLE_INDEX_8_BAUD_RATE_10){
		/* Outside of the table index */
		return CANopen_Slave_LSS_Transmit_Status_Response(CS_CONFIGURE_PROTOCOL_NODE_ID, STATUS_CODE_INVALID_PARAMETER, 0x0);
	}

	/* Save the parameter and give a OK response back */
	canopen->slave.lss.table_index = table_index;
	return CANopen_Slave_LSS_Transmit_Status_Response(CS_CONFIGURE_PROTOCOL_NODE_ID, STATUS_CODE_SUCCESSFUL, 0x0);
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Activate_Protocol_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	// TODO: Hur ska vi aktivera baud rate?

	/* Send OK response back */
	return CANopen_Slave_LSS_Transmit_Status_Response(CS_CONFIGURE_PROTOCOL_NODE_ID, STATUS_CODE_SUCCESSFUL, 0x0);
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Store_Configuration_Protocol(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	// TODO: Hur ska vi spara LSS parametern Buad Rate som inte finns i OD ?
	// TODO: Spara vendor ID, product code, revision number, serial number, node ID här i OD

	/* Send OK response back */
	return CANopen_Slave_LSS_Transmit_Status_Response(CS_CONFIGURE_PROTOCOL_NODE_ID, STATUS_CODE_SUCCESSFUL, 0x0);
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Inquire_Identity_Protocol_Value(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	/* Get cs and find value */
	uint8_t cs = data[0];
	uint32_t value = 0;
	if(cs == CS_INQUIRE_IDENTITY_PROTOCOL_VENDOR_ID)
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_1, &value);
	else if(cs == CS_INQUIRE_IDENTITY_PROTOCOL_PRODUCT_CODE)
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_2, &value);
	else if(cs == CS_INQUIRE_IDENTITY_PROTOCOL_REVISION_NUMBER)
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_3, &value);
	else if(cs == CS_INQUIRE_IDENTITY_PROTOCOL_SERIAL_NUMBER)
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_4, &value);
	else if(cs == CS_INQUIRE_IDENTITY_PROTOCOL_NODE_ID)
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_5, &value);

	/* Send identity response back */
	return CANopen_Slave_LSS_Transmit_Inquire_Identity_Protocol_Response(cs, value);
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Identity_Remote_Slave_Protocol_Value(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	/* Get the value and compare */
	uint8_t cs = data[0];
	uint32_t compare = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	uint32_t value = 0;
	if(cs == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_VENDOR_ID){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_1, &value);
		if(value == compare)
			CANopen_Slave_LSS_Transmit_Identity_Remote_Slave_Protocol_Reponse();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_PRODUCT_CODE){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_2, &value);
		if(value == compare)
			CANopen_Slave_LSS_Transmit_Identity_Remote_Slave_Protocol_Reponse();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_REVISION_NUMBER_LOW){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_3, &value);
		if(value < compare)
			CANopen_Slave_LSS_Transmit_Identity_Remote_Slave_Protocol_Reponse();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_REVISION_NUMBER_HIGH){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_3, &value);
		if(value > compare)
			CANopen_Slave_LSS_Transmit_Identity_Remote_Slave_Protocol_Reponse();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_SERIAL_NUMBER_LOW){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_4, &value);
		if(value < compare)
			CANopen_Slave_LSS_Transmit_Identity_Remote_Slave_Protocol_Reponse();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_SERIAL_NUMBER_HIGH){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_4, &value);
		if(value > compare)
			CANopen_Slave_LSS_Transmit_Identity_Remote_Slave_Protocol_Reponse();
	}

	return STATUS_CODE_SUCCESSFUL;
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Identify_Non_Configured_Remote_Slave_Protocol(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	/* Get value */
	uint32_t node_ID = 0;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_5, &node_ID);

	/* Check if node ID is on the error address */
	if(node_ID == 0xFF)
		CANopen_Slave_LSS_Transmit_Identify_Non_Configured_Remote_Slave_Protocol_Response();

	return STATUS_CODE_SUCCESSFUL;
}
