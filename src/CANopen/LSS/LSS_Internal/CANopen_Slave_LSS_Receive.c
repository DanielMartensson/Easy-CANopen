/*
 * CANopen_Slave_LSS_Receive.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS_Internal.h"

/* Layers */
#include "LSS_Protocol/LSS_Protocol.h"

void CANopen_Slave_LSS_Receive(CANopen *canopen, uint8_t data[]){
	uint8_t cs = data[0];
	if(cs == CS_SWITCH_MODE_GLOBAL){
		CANopen_LSS_Protocol_Receive_Request_Switch_Mode_Global(canopen, data);
	}else if(cs == CS_SWITCH_MODE_SELECTIVE){
		CANopen_LSS_Protocol_Receive_Request_Switch_Mode_Selective_Value(canopen, data);
	}else if(cs == CS_CONFIGURE_NODE_ID){
		CANopen_LSS_Protocol_Receive_Request_Configure_Node_ID(canopen, data);
	}else if(cs == CS_CONFIGURE_BIT_TIMING_PARAMETERS){
		CANopen_LSS_Protocol_Receive_Request_Configure_Bit_Timing_Parameters(canopen, data);
	}else if(cs == CS_ACTIVATE_BIT_TIMING_PARAMETERS){
		CANopen_LSS_Protocol_Receive_Request_Activate_Bit_Timing_Parameters(canopen, data);
	}else if(cs == CS_STORE_CONFIGURATION_PROTOCOL){
		CANopen_LSS_Protocol_Receive_Request_Store_Configuration(canopen, data);
	}else if(cs == CS_INQUIRE_IDENTITY){
		CANopen_LSS_Protocol_Receive_Request_Inquire_Identity_Value(canopen, data);
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE){
		CANopen_LSS_Protocol_Receive_Request_Identity_Remote_Slave_Value(canopen, data);
	}else if(cs == CS_IDENTIFY_REMOTE_SLAVE_NON_CONFIGURED){
		CANopen_LSS_Protocol_Receive_Request_Identify_Non_Configured_Remote_Slave(canopen, data);
	}
}
