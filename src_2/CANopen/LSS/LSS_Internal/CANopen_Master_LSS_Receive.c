/*
 * CANopen_LSS_ProtocolReceive.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS_Internal.h"

/* Layers */
#include "LSS_Protocol/LSS_Protocol.h"

void CANopen_Master_LSS_Receive_Response(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Only other nodes can send out the LSS to the master */
	if(node_ID == 0x0)
		return;

	uint8_t cs = data[0];
	if(cs == CS_LSS_SWITCH_MODE_SELECTIVE_RESPONSE)
		CANopen_LSS_Protocol_Receive_Response_Switch_Mode_Selective(canopen);
	else if(cs == CS_LSS_CONFIGURE_NODE_ID)
		CANopen_LSS_Protocol_Receive_Response_Status_Message(canopen, data);
	else if(cs == CS_LSS_CONFIGURE_BIT_TIMING_PARAMETERS)
		CANopen_LSS_Protocol_Receive_Response_Status_Message(canopen, data);
	else if(cs == CS_LSS_STORE_CONFIGURATION_PROTOCOL)
		CANopen_LSS_Protocol_Receive_Response_Status_Message(canopen, data);
	else if(cs == CS_LSS_INQUIRE_IDENTITY_VENDOR_ID)
		CANopen_LSS_Protocol_Receive_Response_Inquire_Identity_Value(canopen, data);
	else if(cs == CS_LSS_INQUIRE_IDENTITY_PRODUCT_CODE)
		CANopen_LSS_Protocol_Receive_Response_Inquire_Identity_Value(canopen, data);
	else if(cs == CS_LSS_INQUIRE_IDENTITY_REVISION_NUMBER)
		CANopen_LSS_Protocol_Receive_Response_Inquire_Identity_Value(canopen, data);
	else if(cs == CS_LSS_INQUIRE_IDENTITY_SERIAL_NUMBER)
		CANopen_LSS_Protocol_Receive_Response_Inquire_Identity_Value(canopen, data);
	else if(cs == CS_LSS_INQUIRE_IDENTITY_NODE_ID)
		CANopen_LSS_Protocol_Receive_Response_Inquire_Identity_Value(canopen, data);
	else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_CONFIGURED_RESPONSE)
		CANopen_LSS_Protocol_Receive_Response_Identity_Remote_Slave(canopen);
	else if(cs == CS_LSS_IDENTIFY_REMOTE_SLAVE_NON_CONFIGURED_RESPONSE)
		CANopen_LSS_Protocol_Receive_Response_Identify_Non_Configured_Remote_Slave(canopen);
}
