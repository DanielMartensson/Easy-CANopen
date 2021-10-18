/*
 * CANopen_Master_LSS_Receive.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS.h"

static void CANopen_Master_LSS_Receive_Response_Switch_Mode_Selective(CANopen *canopen, uint8_t data[]);
static void CANopen_Master_LSS_Receive_Response_Status_Message(CANopen *canopen, uint8_t data[]);
static void CANopen_Master_LSS_Receive_Response_Inquire_Identity_Value(CANopen *canopen, uint8_t data[]);
static void CANopen_Master_LSS_Receive_Response_Identity_Remote_Slave(CANopen *canopen, uint8_t data[]);
static void CANopen_Master_LSS_Receive_Response_Identify_Non_Configured_Remote_Slave(CANopen *canopen, uint8_t data[]);

void CANopen_Master_LSS_Receive(CANopen *canopen, uint8_t data[]){
	if(data[0] == CS_SWITCH_MODE_SELECTIVE_RESPONSE){
		CANopen_Master_LSS_Receive_Response_Switch_Mode_Selective(canopen, data);
	}else if(data[0] == CS_CONFIGURE_NODE_ID){
		CANopen_Master_LSS_Receive_Response_Status_Message(canopen, data);
	}else if(data[0] == CS_INQUIRE_IDENTITY){
		CANopen_Master_LSS_Receive_Response_Inquire_Identity_Value(canopen, data);
	}else if(data[0] == CS_IDENTIFY_REMOTE_SLAVE_CONFIGURED_RESPONSE){
		CANopen_Master_LSS_Receive_Response_Identity_Remote_Slave(canopen, data);
	}else if(data[0] == CS_IDENTIFY_REMOTE_SLAVE_NON_CONFIGURED_RESPONSE){
		CANopen_Master_LSS_Receive_Response_Identify_Non_Configured_Remote_Slave(canopen, data);
	}
}

static void CANopen_Master_LSS_Receive_Response_Switch_Mode_Selective(CANopen *canopen, uint8_t data[]){
	canopen->master.lss.selective_value_is_set = true;
}

static void CANopen_Master_LSS_Receive_Response_Status_Message(CANopen *canopen, uint8_t data[]){
	canopen->master.lss.status_code_is_new = true;
	canopen->master.lss.status_code = data[1];
	canopen->master.lss.status_code_specific = data[2];
}

static void CANopen_Master_LSS_Receive_Response_Inquire_Identity_Value(CANopen *canopen, uint8_t data[]){
	uint32_t value = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	if(data[0] == CS_INQUIRE_IDENTITY_VENDOR_ID)
		canopen->master.lss.vendor_ID = value;
	else if(data[0] == CS_INQUIRE_IDENTITY_PRODUCT_CODE)
		canopen->master.lss.product_code = value;
	else if(data[0] == CS_INQUIRE_IDENTITY_REVISION_NUMBER)
		canopen->master.lss.revision_number = value;
	else if(data[0] == CS_INQUIRE_IDENTITY_SERIAL_NUMBER)
		canopen->master.lss.serial_number = value;
	else if(data[0] == CS_INQUIRE_IDENTITY_NODE_ID)
		canopen->master.lss.node_ID = value;
}

static void CANopen_Master_LSS_Receive_Response_Identity_Remote_Slave(CANopen *canopen, uint8_t data[]){
	canopen->master.lss.identity_found = true;
}

static void CANopen_Master_LSS_Receive_Response_Identify_Non_Configured_Remote_Slave(CANopen *canopen, uint8_t data[]){
	canopen->master.lss.non_configured_node_ID_found = true;
}
