/*
 * CANopen_Slave_LSS_Receive.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS.h"

/* Slave receive */
static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Global_Protocol(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Vendor_ID(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Product_Code(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Revision_Number(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Serial_Number(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Configure_Protocol_Node_ID(CANopen *canopen, uint8_t data[]);
static STATUS_CODE CANopen_Slave_LSS_Receive_Configure_Protocol_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]);


STATUS_CODE CANopen_Slave_LSS_Receive(CANopen *canopen, uint8_t data[]){
	if(data[0] == CS_SWITCH_MODE_GLOBAL_PROTOCOL){
		return CANopen_Slave_LSS_Receive_Switch_Mode_Global_Protocol(canopen, data);
	}else if(data[0] == CS_SWITCH_MODE_SELECTIVE_PROTOCOL_VENDOR_ID){
		return CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Vendor_ID(canopen, data);
	}else if(data[0] == CS_SWITCH_MODE_SELECTIVE_PROTOCOL_PRODUCT_CODE){
		return CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Product_Code(canopen, data);
	}else if(data[0] == CS_SWITCH_MODE_SELECTIVE_PROTOCOL_REVISION_NUMBER){
		return CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Revision_Number(canopen, data);
	}else if(data[0] == CS_SWITCH_MODE_SELECTIVE_PROTOCOL_SERIAL_NUMBER){
		return CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Serial_Number(canopen, data);
	}else if(data[0] == CS_CONFIGURE_PROTOCOL_NODE_ID){
		return CANopen_Slave_LSS_Receive_Configure_Protocol_Node_ID(canopen, data);
	}else if(data[0] == CS_CONFIGURE_PROTOCOL_BIT_TIMING_PARAMETERS){
		return CANopen_Slave_LSS_Receive_Configure_Protocol_Bit_Timing_Parameters(canopen, data);
	}
	return STATUS_CODE_SUCCESSFUL;
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Global_Protocol(CANopen *canopen, uint8_t data[]){
	canopen->slave.lss.switch_mode_global_protocol = data[0];
	return STATUS_CODE_SUCCESSFUL;
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Vendor_ID(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	/* Save parameter */
	uint32_t vendor_ID = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	return CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_1, vendor_ID);

	/* Response */
	return CANopen_Slave_LSS_Transmit_Command_Specifier(CS_SWITCH_MODE_SELECTIVE_PROTOCOL_RESPONSE);
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Product_Code(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	/* Save parameter */
	uint32_t product_code = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	return CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_2, product_code);

	/* Response */
	return CANopen_Slave_LSS_Transmit_Command_Specifier(CS_SWITCH_MODE_SELECTIVE_PROTOCOL_RESPONSE);
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Revision_Number(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	/* Save parameters */
	uint32_t revision_number = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	return CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_3, revision_number);

	/* Response */
	return CANopen_Slave_LSS_Transmit_Command_Specifier(CS_SWITCH_MODE_SELECTIVE_PROTOCOL_RESPONSE);
}

static STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Selective_Protocol_Serial_Number(CANopen *canopen, uint8_t data[]){
	/* Check if enabled */
	if(canopen->slave.lss.switch_mode_global_protocol == MODE_WAITING)
		return STATUS_CODE_SERVICE_NOT_ENABLED;

	/* Save parameter */
	uint32_t serial_number = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	CANopen_OD_set_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_4, serial_number);

	/* Response */
	return CANopen_Slave_LSS_Transmit_Command_Specifier(CS_SWITCH_MODE_SELECTIVE_PROTOCOL_RESPONSE);
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
