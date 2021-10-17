/*
 * CANopen_Slave_LSS_Transmit.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS.h"

STATUS_CODE CANopen_Slave_LSS_Transmit_Command_Specifier(uint8_t cs){
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
