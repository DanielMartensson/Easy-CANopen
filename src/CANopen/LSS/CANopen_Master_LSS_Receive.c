/*
 * CANopen_Master_LSS_Receive.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS.h"

static void CANopen_Master_LSS_Receive_Response_Switch_Mode_Selective(CANopen *canopen);
static void CANopen_Master_LSS_Receive_Response_Status_Message(CANopen *canopen, uint8_t data[]);
static void CANopen_Master_LSS_Receive_Response_Inquire_Identity_Value(CANopen *canopen, uint8_t data[]);
static void CANopen_Master_LSS_Receive_Response_Identity_Remote_Slave(CANopen *canopen);
static void CANopen_Master_LSS_Receive_Response_Identify_Non_Configured_Remote_Slave(CANopen *canopen);

void CANopen_Master_LSS_Receive(CANopen *canopen, uint8_t data[]){
	uint8_t cs = data[0];
	if(cs == CS_SWITCH_MODE_SELECTIVE_RESPONSE){
		CANopen_Master_LSS_Receive_Response_Switch_Mode_Selective(canopen);
	}else if(cs == CS_CONFIGURE_NODE_ID){
		CANopen_Master_LSS_Receive_Response_Status_Message(canopen, data);
	}else if(cs == CS_INQUIRE_IDENTITY){
		CANopen_Master_LSS_Receive_Response_Inquire_Identity_Value(canopen, data);
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_CONFIGURED_RESPONSE){
		CANopen_Master_LSS_Receive_Response_Identity_Remote_Slave(canopen);
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_NON_CONFIGURED_RESPONSE){
		CANopen_Master_LSS_Receive_Response_Identify_Non_Configured_Remote_Slave(canopen);
	}
}

static void CANopen_Master_LSS_Receive_Response_Switch_Mode_Selective(CANopen *canopen){
	canopen->master.lss.selective_value_is_set = true;
}

static void CANopen_Master_LSS_Receive_Response_Status_Message(CANopen *canopen, uint8_t data[]){
	canopen->master.lss.status_code_is_new = true;
	canopen->master.lss.status_code = data[1];
	canopen->master.lss.status_code_specific = data[2];
}

static void CANopen_Master_LSS_Receive_Response_Inquire_Identity_Value(CANopen *canopen, uint8_t data[]){
	uint8_t cs = data[0];
	uint32_t value = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	if(cs == CS_INQUIRE_IDENTITY_VENDOR_ID)
		canopen->master.lss.vendor_ID = value;
	else if(cs == CS_INQUIRE_IDENTITY_PRODUCT_CODE)
		canopen->master.lss.product_code = value;
	else if(cs == CS_INQUIRE_IDENTITY_REVISION_NUMBER)
		canopen->master.lss.revision_number = value;
	else if(cs == CS_INQUIRE_IDENTITY_SERIAL_NUMBER)
		canopen->master.lss.serial_number = value;
	else if(cs == CS_INQUIRE_IDENTITY_NODE_ID)
		canopen->master.lss.node_ID = value;
}

static void CANopen_Master_LSS_Receive_Response_Identity_Remote_Slave(CANopen *canopen){
	canopen->master.lss.identity_found = true;
}

static void CANopen_Master_LSS_Receive_Response_Identify_Non_Configured_Remote_Slave(CANopen *canopen){
	canopen->master.lss.non_configured_node_ID_found = true;
}
