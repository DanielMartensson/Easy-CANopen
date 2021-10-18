/*
 * CANopen_Master_LSS_Transmit.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS.h"

/* Layers */
#include "../../Hardware/Hardware.h"

void CANopen_Master_LSS_Transmit_Request_Switch_Mode_Global(uint8_t mode){
	uint8_t data[8] = {0};
	data[0] = CS_SWITCH_MODE_GLOBAL;
	data[1] = mode;
	CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}

void CANopen_Master_LSS_Transmit_Request_Switch_Mode_Selective_Value(uint8_t cs, uint32_t value){
	uint8_t data[8] = {0};
	data[0] = cs;
	data[1] = value;
	data[2] = value >> 8;
	data[3] = value >> 16;
	data[4] = value >> 24;
	CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}

void CANopen_Master_LSS_Transmit_Request_Configure_Node_ID(uint8_t node_ID){
	uint8_t data[8] = {0};
	data[0] = CS_CONFIGURE_NODE_ID;
	data[1] = node_ID;
	CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}

void CANopen_Master_LSS_Transmit_Request_Configure_Bit_Timing_Parameters(uint8_t table_index){
	uint8_t data[8] = {0};
	data[0] = CS_CONFIGURE_BIT_TIMING_PARAMETERS;
	data[1] = TABLE_SELECTOR_0;												/* The table for the baud rate from the CiA 301 standard is used */
	data[2] = table_index;													/* What baud rate we should use */
	CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}

void CANopen_Master_LSS_Transmit_Request_Active_Bit_Timing_Parameters(uint16_t delay){
	uint8_t data[8] = {0};
	data[0] = CS_ACTIVATE_BIT_TIMING_PARAMETERS;
	data[1] = delay;														/* LSB */
	data[2] = delay >> 8;													/* MSB */
	CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}

void CANopen_Master_LSS_Transmit_Request_Store_Configuration(){
	uint8_t data[8] = {0};
	data[0] = CS_STORE_CONFIGURATION_PROTOCOL;
	CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}

void CANopen_Master_LSS_Transmit_Request_Inquire_Identity_Value(uint8_t cs){
	uint8_t data[8] = {0};
	data[0] = cs;
	CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}

void CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(uint8_t cs, uint32_t value){
	uint8_t data[8] = {0};
	data[0] = cs;
	data[1] = value;
	data[2] = value >> 8;
	data[3] = value >> 16;
	data[4] = value >> 24;
	CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}

void CANopen_Master_LSS_Transmit_Request_Identify_Non_Configured_Remote_Slave(){
	uint8_t data[8] = {0};
	data[0] = CS_IDENTIFY_REMOTE_SLAVE_NON_CONFIGURED;
	CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}
