/*
 * CANopen_Slave_LSS_Transmit.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS.h"

STATUS_CODE CANopen_Slave_LSS_Transmit_Switch_Mode_Selective_Protocol_Value_Response(uint8_t cs){
	uint8_t data[8] = {0};
	data[0] = cs;
	return CAN_Send_Message(FUNCTION_CODE_LSS_RECEIVE, data);
}

STATUS_CODE CANopen_Slave_LSS_Transmit_Status_Response(uint8_t cs, uint8_t status_code, uint8_t status_code_specific){
	uint8_t data[8] = {0};
	data[0] = cs;
	data[1] = status_code;
	data[2] = status_code_specific;
	return CAN_Send_Message(FUNCTION_CODE_LSS_RECEIVE, data);
}

STATUS_CODE CANopen_Slave_LSS_Transmit_Inquire_Identity_Protocol_Response(uint8_t cs, uint32_t value){
	uint8_t data[8] = {0};
	data[0] = cs;
	data[1] = value;
	data[2] = value >> 8;
	data[3] = value >> 16;
	data[4] = value >> 24;
	return CAN_Send_Message(FUNCTION_CODE_LSS_RECEIVE, data);
}

STATUS_CODE CANopen_Slave_LSS_Transmit_Identity_Remote_Slave_Protocol_Reponse(){
	uint8_t data[8] = {0};
	data[0] = CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_CONFIGURED_RESPONSE;
	return CAN_Send_Message(FUNCTION_CODE_LSS_RECEIVE, data);
}

STATUS_CODE CANopen_Slave_LSS_Transmit_Identify_Non_Configured_Remote_Slave_Protocol_Response(){
	uint8_t data[8] = {0};
	data[0] = CS_IDENTIFY_REMOTE_SLAVE_PROTOCOL_NON_CONFIGURED_RESPONSE;
	return CAN_Send_Message(FUNCTION_CODE_LSS_RECEIVE, data);
}
