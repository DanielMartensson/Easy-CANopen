/*
 * CANopen_LSS_Protocol_Transmit_Response.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS_Protocol.h"

/* Layers */
#include "../../../../Hardware/Hardware.h"

void CANopen_LSS_Protocol_Transmit_Response_Switch_Mode_Selective_Value(){
	uint8_t data[8] = {0};
	data[0] = CS_LSS_SWITCH_MODE_SELECTIVE_RESPONSE;
	Hardware_CAN_Send_Message(FUNCTION_CODE_LSS_RECEIVE, data);
}

void CANopen_LSS_Protocol_Transmit_Response_Status_Message(uint8_t cs, uint8_t status_code, uint8_t status_code_specific){
	uint8_t data[8] = {0};
	data[0] = cs;
	data[1] = status_code;
	data[2] = status_code_specific;
	Hardware_CAN_Send_Message(FUNCTION_CODE_LSS_RECEIVE, data);
}

void CANopen_LSS_Protocol_Transmit_Response_Inquire_Identity_Value(uint8_t cs, uint32_t value){
	uint8_t data[8] = {0};
	data[0] = cs;
	data[1] = value;
	data[2] = value >> 8;
	data[3] = value >> 16;
	data[4] = value >> 24;
	Hardware_CAN_Send_Message(FUNCTION_CODE_LSS_RECEIVE, data);
}

void CANopen_LSS_Protocol_Transmit_Response_Identity_Remote_Slave(){
	uint8_t data[8] = {0};
	data[0] = CS_LSS_IDENTIFY_REMOTE_SLAVE_CONFIGURED_RESPONSE;
	Hardware_CAN_Send_Message(FUNCTION_CODE_LSS_RECEIVE, data);
}

void CANopen_LSS_Protocol_Transmit_Response_Identify_Non_Configured_Remote_Slave(){
	uint8_t data[8] = {0};
	data[0] = CS_LSS_IDENTIFY_REMOTE_SLAVE_NON_CONFIGURED_RESPONSE;
	Hardware_CAN_Send_Message(FUNCTION_CODE_LSS_RECEIVE, data);
}
