/*
 * Easy_CANopen_Thread.c
 *
 *  Created on: 6 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "Easy_CANopen.h"

/* Layers */
#include "../Hardware/Hardware.h"
#include "../CANopen/CANopen_Internal.h"

bool Easy_CANopen_Thread_Listen_Messages(CANopen *canopen) {
	uint32_t COB_ID = 0;
	uint8_t data[8] = { 0 };
	bool is_new_message = Hardware_CAN_Read_Message(&COB_ID, data);
	if (is_new_message) {
		/* Save latest */
		canopen->COB_ID = COB_ID;
		memcpy(canopen->data, data, 8);
		canopen->COB_ID_and_data_is_updated = true;

		/* Read the COB ID */
		uint8_t function_code = COB_ID >> 7;											/* What service should we use */
		uint16_t node_ID = 0x7F & COB_ID;												/* Node ID = 0 for masters. Node ID 1 to 127 for slaves */

		if(function_code == FUNCTION_CODE_NMT){
			CANopen_Slave_NMT_Receive_Request(canopen, node_ID, data);
		}else if(function_code == FUNCTION_CODE_SYNC_EMCY) {
			CANopen_Consumer_SYNC_Receive_Synchronization(canopen, node_ID, data);
			CANopen_Consumer_EMCY_Receive_Error(canopen, node_ID, data);
		}else if(function_code == FUNCTION_CODE_TIME){
			CANopen_Consumer_TIME_Receive_Clock(canopen, node_ID, data);
		}else if(function_code == FUNCTION_CODE_PDO1_TRANSMIT){

		}else if(function_code == FUNCTION_CODE_PDO1_RECEIVE){

		}else if(function_code == FUNCTION_CODE_PDO2_TRANSMIT){

		}else if(function_code == FUNCTION_CODE_PDO2_RECEIVE){

		}else if(function_code == FUNCTION_CODE_PDO3_TRANSMIT){

		}else if(function_code == FUNCTION_CODE_PDO3_RECEIVE){

		}else if(function_code == FUNCTION_CODE_PDO4_TRANSMIT){

		}else if(function_code == FUNCTION_CODE_PDO4_RECEIVE){

		}else if(function_code == FUNCTION_CODE_SDO_TRANSMIT){
			CANopen_Server_SDO_Receive_Request(canopen, node_ID, data);										/* Server -> Client */
		}else if(function_code == FUNCTION_CODE_SDO_RECEIVE){
			CANopen_Client_SDO_Receive_Response(canopen, node_ID, data);									/* Client -> Server */
		}else if(function_code == FUNCTION_CODE_HEARTBEAT_GUARD){
			CANopen_Consumer_HEARTBEAT_Receive_Status(canopen, node_ID, data);
			CANopen_Server_GUARD_Receive_Request_Status(canopen, node_ID, data);
			CANopen_Client_GUARD_Receive_Response_Status(canopen, node_ID, data);
		}else if(COB_ID == FUNCTION_CODE_LSS_TRANSMIT){
			CANopen_Slave_LSS_Receive_Request(canopen, node_ID, data);														/* Master -> Slave */
		}else if(COB_ID == FUNCTION_CODE_LSS_RECEIVE){
			CANopen_Master_LSS_Receive_Response(canopen, node_ID, data);														/* Slave -> Master */
		}
	}

	return is_new_message;
}

void Easy_CANopen_Thread_Transmit_Messages(CANopen *canopen){
	CANopen_Producer_HEARTBEAT_Transmit_Status(canopen);
	CANopen_Producer_TIME_Transmit_Clock(canopen);
}
