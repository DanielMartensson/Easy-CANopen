/*
 * CANopen_Slave_LSS_Transmit.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS_Internal.h"

/* Layers */
#include "LSS_Protocol/LSS_Protocol.h"

void CANopen_Slave_LSS_Transmit_Response_Switch_Mode_Selective_Value(){
	CANopen_LSS_Protocol_Transmit_Response_Switch_Mode_Selective_Value();
}

void CANopen_Slave_LSS_Transmit_Response_Status_Message(uint8_t cs, uint8_t status_code, uint8_t status_code_specific){
	CANopen_LSS_Protocol_Transmit_Response_Status_Message(cs, status_code, status_code_specific);
}

void CANopen_Slave_LSS_Transmit_Response_Inquire_Identity_Value(uint8_t cs, uint32_t value){
	CANopen_LSS_Protocol_Transmit_Response_Inquire_Identity_Value(cs, value);
}

void CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave(){
	CANopen_LSS_Protocol_Transmit_Response_Identity_Remote_Slave();
}

void CANopen_Slave_LSS_Transmit_Response_Identify_Non_Configured_Remote_Slave(){
	CANopen_LSS_Protocol_Transmit_Response_Identify_Non_Configured_Remote_Slave();
}
