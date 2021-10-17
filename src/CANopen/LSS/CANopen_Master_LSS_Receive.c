/*
 * CANopen_Master_LSS_Receive.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS.h"

static STATUS_CODE CANopen_Master_LSS_Receive_Command_Specifier(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
static STATUS_CODE CANopen_Master_LSS_Receive_Status_Response(CANopen *canopen, uint8_t node_ID, uint8_t data[]);

STATUS_CODE CANopen_Master_LSS_Receive(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	if(data[0] == CS_SWITCH_MODE_SELECTIVE_PROTOCOL_RESPONSE){
		CANopen_Master_LSS_Receive_Command_Specifier(canopen, node_ID, data);
	}else if(data[0] == CS_CONFIGURE_PROTOCOL_NODE_ID){
		CANopen_Master_LSS_Receive_Status_Response(canopen, node_ID, data);
	}
	return STATUS_CODE_SUCCESSFUL;
}

static STATUS_CODE CANopen_Master_LSS_Receive_Command_Specifier(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	canopen->master.lss.cs = data[0];
	canopen->master.lss.from_node_ID = node_ID;
	return STATUS_CODE_SUCCESSFUL;
}

static STATUS_CODE CANopen_Master_LSS_Receive_Status_Response(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	canopen->master.lss.cs = data[0];
	canopen->master.lss.status_code = data[1];
	canopen->master.lss.status_code_specific = data[2];
	canopen->master.lss.from_node_ID = node_ID;
	return STATUS_CODE_SUCCESSFUL;
}
