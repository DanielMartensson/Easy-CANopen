/*
 * CANopen_Slave_LSS_Receive.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS_Internal.h"

/* Layers */
#include "LSS_Protocol/LSS_Protocol.h"

void CANopen_Slave_LSS_Receive_Request(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	uint8_t cs = data[0];
	if(cs == CS_LSS_SWITCH_MODE_GLOBAL){
		CANopen_LSS_Protocol_Receive_Request_Switch_Mode_Global(canopen, data);
	}else if(cs == CS_LSS_SWITCH_MODE_SELECTIVE_VENDOR_ID || cs == CS_LSS_SWITCH_MODE_SELECTIVE_PRODUCT_CODE || cs == CS_LSS_SWITCH_MODE_SELECTIVE_REVISION_NUMBER || cs == CS_LSS_SWITCH_MODE_SELECTIVE_SERIAL_NUMBER){
		CANopen_LSS_Protocol_Receive_Request_Switch_Mode_Selective_Value(canopen, data);
	}else if(cs == CS_LSS_CONFIGURE_NODE_ID){
		CANopen_LSS_Protocol_Receive_Request_Configure_Node_ID(canopen, data);
	}else if(cs == CS_LSS_CONFIGURE_BIT_TIMING_PARAMETERS){
		CANopen_LSS_Protocol_Receive_Request_Configure_Bit_Timing_Parameters(canopen, data);
	}else if(cs == CS_LSS_ACTIVATE_BIT_TIMING_PARAMETERS){
		CANopen_LSS_Protocol_Receive_Request_Activate_Bit_Timing_Parameters(canopen, data);
	}else if(cs == CS_LSS_STORE_CONFIGURATION_PROTOCOL){
		CANopen_LSS_Protocol_Receive_Request_Store_Configuration(canopen, data);
	}else if(cs == CS_LSS_INQUIRE_IDENTITY_VENDOR_ID){
		CANopen_LSS_Protocol_Receive_Request_Inquire_Identity_Value(canopen, data);
	}else if(cs == CS_LSS_INQUIRE_IDENTITY_PRODUCT_CODE){
		CANopen_LSS_Protocol_Receive_Request_Inquire_Identity_Value(canopen, data);
	}else if(cs == CS_LSS_INQUIRE_IDENTITY_REVISION_NUMBER){
		CANopen_LSS_Protocol_Receive_Request_Inquire_Identity_Value(canopen, data);
	}else if(cs == CS_LSS_INQUIRE_IDENTITY_SERIAL_NUMBER){
		CANopen_LSS_Protocol_Receive_Request_Inquire_Identity_Value(canopen, data);
	}else if(cs == CS_LSS_INQUIRE_IDENTITY_NODE_ID){
		CANopen_LSS_Protocol_Receive_Request_Inquire_Identity_Value(canopen, data);
	}else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_VENDOR_ID){
		CANopen_LSS_Protocol_Receive_Request_Identity_Remote_Slave_Value(canopen, data);
	}else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_PRODUCT_CODE){
			CANopen_LSS_Protocol_Receive_Request_Identity_Remote_Slave_Value(canopen, data);
	}else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_HIGH){
			CANopen_LSS_Protocol_Receive_Request_Identity_Remote_Slave_Value(canopen, data);
	}else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_LOW){
			CANopen_LSS_Protocol_Receive_Request_Identity_Remote_Slave_Value(canopen, data);
	}else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_SERIAL_NUMBER_HIGH){
			CANopen_LSS_Protocol_Receive_Request_Identity_Remote_Slave_Value(canopen, data);
	}else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_SERIAL_NUMBER_LOW){
			CANopen_LSS_Protocol_Receive_Request_Identity_Remote_Slave_Value(canopen, data);
	}else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_NON_CONFIGURED){
		CANopen_LSS_Protocol_Receive_Request_Identify_Non_Configured_Remote_Slave(canopen, data);
	}
}
