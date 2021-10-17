/*
 * CANopen_Master_LSS_Transmit.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS.h"

/* Layers */
#include "../../Hardware/CAN_Network_Layer/CAN_Network_Layer.h"

STATUS_CODE CANopen_Master_LSS_Transmit_Switch_Mode_Global_Protocol(uint8_t mode){
	uint8_t data[8] = {0};
	data[0] = CS_SWITCH_MODE_GLOBAL_PROTOCOL;
	data[1] = mode;
	return CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}

STATUS_CODE CANopen_Master_LSS_Transmit_Switch_Mode_Selective_Protocol_Value(CANopen *canopen, uint8_t cs, uint32_t value){
	uint8_t data[8] = {0};
	data[0] = cs;
	data[1] = value;
	data[2] = value >> 8;
	data[3] = value >> 16;
	data[4] = value >> 24;
	return CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}

STATUS_CODE CANopen_Master_LSS_Transmit_Configure_Protocol_Node_ID(CANopen *canopen, uint8_t node_ID){
	uint8_t data[8] = {0};
	data[0] = CS_CONFIGURE_PROTOCOL_NODE_ID;
	data[1] = node_ID;
	return CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}

STATUS_CODE CANopen_Master_LSS_Transmit_Configure_Protocol_Bit_Timing_Parameters(CANopen *canopen, uint8_t table_index){
	uint8_t data[8] = {0};
	data[0] = CS_CONFIGURE_PROTOCOL_BIT_TIMING_PARAMETERS;
	data[1] = TABLE_SELECTOR_0;																	/* The table for the baud rate from the CiA 301 standard is used */
	data[2] = table_index;																		/* What baud rate we should use */
	return CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}

STATUS_CODE CANopen_Master_LSS_Transmit_Active_Protocol_Bit_Timing_Parameters(CANopen *canopen, uint16_t delay){
	uint8_t data[8] = {0};
	data[0] = CS_ACTIVATE_PROTOCOL_BIT_TIMING_PARAMETERS;
	data[1] = delay;																			/* LSB */
	data[2] = delay >> 8;																		/* MSB */
	return CAN_Send_Message(FUNCTION_CODE_LSS_TRANSMIT, data);
}
