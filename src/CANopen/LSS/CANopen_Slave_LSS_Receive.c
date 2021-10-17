/*
 * CANopen_Slave_LSS_Receive.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS.h"

/* Layers */
#include "../OD/OD.h"
#include "../../Hardware/Hardware.h"

static void CANopen_Slave_LSS_Receive_Request_Switch_Mode_Global_Protocol(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Switch_Mode_Selective_Protocol_Value(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Configure_Protocol_Node_ID(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Configure_Protocol_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Activate_Protocol_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Store_Configuration_Protocol(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Inquire_Identity_Protocol_Value(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Identity_Remote_Slave_Protocol_Value(CANopen *canopen, uint8_t data[]);
static void CANopen_Slave_LSS_Receive_Request_Identify_Non_Configured_Remote_Slave_Protocol(CANopen *canopen, uint8_t data[]);

void CANopen_Slave_LSS_Receive(CANopen *canopen, uint8_t data[]){
	if(data[0] == CS_SWITCH_MODE_GLOBAL_PROTOCOL){
		return CANopen_Slave_LSS_Receive_Request_Switch_Mode_Global_Protocol(canopen, data);
	}else if(data[0] == CS_SWITCH_MODE_SELECTIVE_PROTOCOL){
		CANopen_Slave_LSS_Receive_Request_Switch_Mode_Selective_Protocol_Value(canopen, data);
	}else if(data[0] == CS_CONFIGURE_PROTOCOL_NODE_ID){
		CANopen_Slave_LSS_Receive_Request_Configure_Protocol_Node_ID(canopen, data);
	}else if(data[0] == CS_CONFIGURE_PROTOCOL_BIT_TIMING_PARAMETERS){
		CANopen_Slave_LSS_Receive_Request_Configure_Protocol_Bit_Timing_Parameters(canopen, data);
	}else if(data[0] == CS_ACTIVATE_PROTOCOL_BIT_TIMING_PARAMETERS){
		CANopen_Slave_LSS_Receive_Request_Activate_Protocol_Bit_Timing_Parameters(canopen, data);
	}else if(data[0] == CS_STORE_CONFIGURATION_PROTOCOL){
		CANopen_Slave_LSS_Receive_Request_Store_Configuration_Protocol(canopen, data);
	}else if(data[0] == CS_INQUIRE_IDENTITY_PROTOCOL){
		CANopen_Slave_LSS_Receive_Request_Inquire_Identity_Protocol_Value(canopen, data);
	}else if(data[0] == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL){
		CANopen_Slave_LSS_Receive_Request_Identity_Remote_Slave_Protocol_Value(canopen, data);
	}else if(data[0] == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_NON_CONFIGURED){
		CANopen_Slave_LSS_Receive_Request_Identify_Non_Configured_Remote_Slave_Protocol(canopen, data);
	}
}

static void CANopen_Slave_LSS_Receive_Request_Switch_Mode_Global_Protocol(CANopen *canopen, uint8_t data[]){
	canopen->slave.lss.switch_mode_global_protocol = data[0];
}

static void CANopen_Slave_LSS_Receive_Request_Switch_Mode_Selective_Protocol_Value(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Save parameter */
	uint8_t cs = data[0];
	if(cs == CS_INQUIRE_IDENTITY_PROTOCOL_VENDOR_ID)
		canopen->slave.lss.vendor_ID = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	else if(cs == CS_INQUIRE_IDENTITY_PROTOCOL_PRODUCT_CODE)
		canopen->slave.lss.product_code = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	else if(cs == CS_INQUIRE_IDENTITY_PROTOCOL_REVISION_NUMBER)
		canopen->slave.lss.revision_number = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	else if(cs == CS_INQUIRE_IDENTITY_PROTOCOL_SERIAL_NUMBER)
		canopen->slave.lss.serial_number = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	else if(cs == CS_INQUIRE_IDENTITY_PROTOCOL_NODE_ID)
		canopen->slave.lss.node_ID = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];

	/* Response */
	CANopen_Slave_LSS_Transmit_Response_Switch_Mode_Selective_Protocol_Value();
}

static void CANopen_Slave_LSS_Receive_Request_Configure_Protocol_Node_ID(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Check parameter */
	uint8_t node_ID = data[1];
	if(node_ID == 0 || node_ID > 127){
		/* Node ID 0 is master ID and node ID cannot be larger than 127 */
		CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_CONFIGURE_PROTOCOL_NODE_ID, STATUS_CODE_INVALID_PARAMETER, 0x0);
	}

	/* Save the parameter and give a OK response back */
	canopen->slave.lss.node_ID = node_ID;
	CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_CONFIGURE_PROTOCOL_NODE_ID, STATUS_CODE_SUCCESSFUL, 0x0);
}

static void CANopen_Slave_LSS_Receive_Request_Configure_Protocol_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Check parameter */
	uint8_t table_index = data[2];
	if(table_index > TABLE_INDEX_8_BAUD_RATE_10){
		/* Outside of the table index */
		CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_CONFIGURE_PROTOCOL_BIT_TIMING_PARAMETERS, STATUS_CODE_INVALID_PARAMETER, 0x0);
	}

	/* Save the parameter and give a OK response back */
	canopen->slave.lss.table_index = table_index;
	CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_CONFIGURE_PROTOCOL_BIT_TIMING_PARAMETERS, STATUS_CODE_SUCCESSFUL, 0x0);
}

static void CANopen_Slave_LSS_Receive_Request_Activate_Protocol_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Set the baud rate - If fail, returns false */
	if(!CAN_Set_Baud_Rate(canopen->slave.lss.table_index))
		return CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_ACTIVATE_PROTOCOL_BIT_TIMING_PARAMETERS, STATUS_CODE_ERROR_DURING_OPERATION, 0x0);

	/* Send OK response back */
	CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_ACTIVATE_PROTOCOL_BIT_TIMING_PARAMETERS, STATUS_CODE_SUCCESSFUL, 0x0);
}

static void CANopen_Slave_LSS_Receive_Request_Store_Configuration_Protocol(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return;

	// TODO: Hur ska vi spara LSS parametern Buad Rate som inte finns i OD ?
	CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_1, canopen->slave.lss.vendor_ID);
	CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_2, canopen->slave.lss.product_code);
	CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_3, canopen->slave.lss.revision_number);
	CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_4, canopen->slave.lss.serial_number);
	CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_5, canopen->slave.lss.node_ID);

	/* Send OK response back */
	CANopen_Slave_LSS_Transmit_Response_Status_Message(CS_STORE_CONFIGURATION_PROTOCOL, STATUS_CODE_SUCCESSFUL, 0x0);
}

static void CANopen_Slave_LSS_Receive_Request_Inquire_Identity_Protocol_Value(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return;

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
	CANopen_Slave_LSS_Transmit_Response_Inquire_Identity_Protocol_Value(cs, value);
}

static void CANopen_Slave_LSS_Receive_Request_Identity_Remote_Slave_Protocol_Value(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Get the value and compare */
	uint8_t cs = data[0];
	uint32_t compare = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	uint32_t value = 0;
	if(cs == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_VENDOR_ID){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_1, &value);
		if(value == compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave_Protocol();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_PRODUCT_CODE){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_2, &value);
		if(value == compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave_Protocol();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_REVISION_NUMBER_LOW){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_3, &value);
		if(value < compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave_Protocol();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_REVISION_NUMBER_HIGH){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_3, &value);
		if(value > compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave_Protocol();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_SERIAL_NUMBER_LOW){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_4, &value);
		if(value < compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave_Protocol();
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_SERIAL_NUMBER_HIGH){
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_4, &value);
		if(value > compare)
			CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave_Protocol();
	}
}

static void CANopen_Slave_LSS_Receive_Request_Identify_Non_Configured_Remote_Slave_Protocol(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return;

	/* Get value */
	uint32_t node_ID = 0;
	CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_5, &node_ID);

	/* Check if node ID is on the error address */
	if(node_ID == 0xFF)
		CANopen_Slave_LSS_Transmit_Response_Identify_Non_Configured_Remote_Slave_Protocol();

}
