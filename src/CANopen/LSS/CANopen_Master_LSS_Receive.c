/*
 * CANopen_Master_LSS_Receive.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS.h"

static void CANopen_Master_LSS_Receive_Response_Switch_Mode_Selective_Protocol(CANopen *canopen, uint8_t data[]);
static void CANopen_Master_LSS_Receive_Response_Status_Message(CANopen *canopen, uint8_t data[]);
static void CANopen_Master_LSS_Receive_Response_Inquire_Identity_Protocol_Value(CANopen *canopen, uint8_t data[]);
static void CANopen_Master_LSS_Receive_Response_Identity_Remote_Slave_Protocol(CANopen *canopen, uint8_t data[]);
static void CANopen_Master_LSS_Receive_Response_Identify_Non_Configured_Remote_Slave_Protocol(CANopen *canopen, uint8_t data[]);

void CANopen_Master_LSS_Receive(CANopen *canopen, uint8_t data[]){
	if(data[0] == CS_SWITCH_MODE_SELECTIVE_PROTOCOL_RESPONSE){
		CANopen_Master_LSS_Receive_Response_Switch_Mode_Selective_Protocol(canopen, data);
	}else if(data[0] == CS_CONFIGURE_PROTOCOL_NODE_ID){
		CANopen_Master_LSS_Receive_Response_Status_Message(canopen, data);
	}else if(data[0] == CS_INQUIRE_IDENTITY_PROTOCOL){
		CANopen_Master_LSS_Receive_Response_Inquire_Identity_Protocol_Value(canopen, data);
	}else if(data[0] == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_CONFIGURED_RESPONSE){
		CANopen_Master_LSS_Receive_Response_Identity_Remote_Slave_Protocol(canopen, data);
	}else if(data[0] == CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_NON_CONFIGURED_RESPONSE){
		CANopen_Master_LSS_Receive_Response_Identify_Non_Configured_Remote_Slave_Protocol(canopen, data);
	}
}

static void CANopen_Master_LSS_Receive_Response_Switch_Mode_Selective_Protocol(CANopen *canopen, uint8_t data[]){
	canopen->master.lss.cs = data[0];
}

static void CANopen_Master_LSS_Receive_Response_Status_Message(CANopen *canopen, uint8_t data[]){
	canopen->master.lss.cs = data[0];
	canopen->master.lss.status_code = data[1];
	canopen->master.lss.status_code_specific = data[2];
}

static void CANopen_Master_LSS_Receive_Response_Inquire_Identity_Protocol_Value(CANopen *canopen, uint8_t data[]){
	canopen->master.lss.cs = data[0];
	uint32_t value = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	if(data[0] == CS_INQUIRE_IDENTITY_PROTOCOL_VENDOR_ID)
		canopen->master.lss.vendor_ID = value;
	else if(data[0] == CS_INQUIRE_IDENTITY_PROTOCOL_PRODUCT_CODE)
		canopen->master.lss.product_code = value;
	else if(data[0] == CS_INQUIRE_IDENTITY_PROTOCOL_REVISION_NUMBER)
		canopen->master.lss.revision_number = value;
	else if(data[0] == CS_INQUIRE_IDENTITY_PROTOCOL_SERIAL_NUMBER)
		canopen->master.lss.serial_number = value;
	else if(data[0] == CS_INQUIRE_IDENTITY_PROTOCOL_NODE_ID)
		canopen->master.lss.node_ID = value;
}

static void CANopen_Master_LSS_Receive_Response_Identity_Remote_Slave_Protocol(CANopen *canopen, uint8_t data[]){
	canopen->master.lss.identity_found = true;
}

static void CANopen_Master_LSS_Receive_Response_Identify_Non_Configured_Remote_Slave_Protocol(CANopen *canopen, uint8_t data[]){
	canopen->master.lss.non_configured_node_ID = true;
}
