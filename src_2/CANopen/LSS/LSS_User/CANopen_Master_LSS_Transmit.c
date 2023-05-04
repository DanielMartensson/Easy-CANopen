/*
 * CANopen_Master_LSS_Transmit.c
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "LSS_User.h"

/* Layers */
#include "../LSS_Internal/LSS_Protocol/LSS_Protocol.h"

void CANopen_Master_LSS_Transmit_Request_Switch_Mode_Global(uint8_t mode){
	CANopen_LSS_Protocol_Transmit_Request_Switch_Mode_Global(mode);
}

void CANopen_Master_LSS_Transmit_Request_Switch_Mode_Selective_Value(uint8_t cs, uint32_t value){
	CANopen_LSS_Protocol_Transmit_Request_Switch_Mode_Selective_Value(cs, value);
}

void CANopen_Master_LSS_Transmit_Request_Configure_Node_ID(uint8_t node_ID){
	CANopen_LSS_Protocol_Transmit_Request_Configure_Node_ID(node_ID);
}

void CANopen_Master_LSS_Transmit_Request_Configure_Bit_Timing_Parameters(uint8_t table_index){
	CANopen_LSS_Protocol_Transmit_Request_Configure_Bit_Timing_Parameters(table_index);
}

void CANopen_Master_LSS_Transmit_Request_Active_Bit_Timing_Parameters(uint16_t delay){
	CANopen_LSS_Protocol_Transmit_Request_Active_Bit_Timing_Parameters(delay);
}

void CANopen_Master_LSS_Transmit_Request_Store_Configuration(){
	CANopen_LSS_Protocol_Transmit_Request_Store_Configuration();
}

void CANopen_Master_LSS_Transmit_Request_Inquire_Identity_Value(uint8_t cs){
	CANopen_LSS_Protocol_Transmit_Request_Inquire_Identity_Value(cs);
}

void CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(uint8_t cs, uint32_t value){
	CANopen_LSS_Protocol_Transmit_Request_Identity_Remote_Slave_Value(cs, value);
}

void CANopen_Master_LSS_Transmit_Request_Identify_Non_Configured_Remote_Slave(){
	CANopen_LSS_Protocol_Transmit_Request_Identify_Non_Configured_Remote_Slave();
}
