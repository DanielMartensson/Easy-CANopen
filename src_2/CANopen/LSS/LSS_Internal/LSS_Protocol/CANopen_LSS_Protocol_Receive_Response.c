/*
 * CANopen_LSS_Protocol_Receive_Response.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS_Protocol.h"

void CANopen_LSS_Protocol_Receive_Response_Switch_Mode_Selective(CANopen *canopen){
	canopen->master.lss.selective_value_is_set = true;
}

void CANopen_LSS_Protocol_Receive_Response_Status_Message(CANopen *canopen, uint8_t data[]){
	canopen->master.lss.status_code_is_new = true;
	canopen->master.lss.status_code = data[1];
	canopen->master.lss.status_code_specific = data[2];
}

void CANopen_LSS_Protocol_Receive_Response_Inquire_Identity_Value(CANopen *canopen, uint8_t data[]){
	uint8_t cs = data[0];
	uint32_t value = (data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1];
	if(cs == CS_LSS_INQUIRE_IDENTITY_VENDOR_ID)
		canopen->master.lss.vendor_ID = value;
	else if(cs == CS_LSS_INQUIRE_IDENTITY_PRODUCT_CODE)
		canopen->master.lss.product_code = value;
	else if(cs == CS_LSS_INQUIRE_IDENTITY_REVISION_NUMBER)
		canopen->master.lss.revision_number = value;
	else if(cs == CS_LSS_INQUIRE_IDENTITY_SERIAL_NUMBER)
		canopen->master.lss.serial_number = value;
	else if(cs == CS_LSS_INQUIRE_IDENTITY_NODE_ID)
		canopen->master.lss.node_ID = value;
}

void CANopen_LSS_Protocol_Receive_Response_Identity_Remote_Slave(CANopen *canopen){
	canopen->master.lss.identity_found = true;
}

void CANopen_LSS_Protocol_Receive_Response_Identify_Non_Configured_Remote_Slave(CANopen *canopen){
	canopen->master.lss.non_configured_node_ID_found = true;
}
