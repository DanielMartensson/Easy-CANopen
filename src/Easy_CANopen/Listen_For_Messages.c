/*
 * Listen_For_Messages.c
 *
 *  Created on: 6 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "../CANopen/Global_Enums/Enum_Function_Codes.h"
#include "Easy_CANopen.h"

/* Layers */
#include "../Hardware/CAN_Network_Layer/CAN_Network_Layer.h"

/* Enums */

bool Easy_CANopen_Listen_For_Messages(CANopen *canopen) {
	uint32_t COB_ID = 0;
	uint8_t data[8] = { 0 };
	bool is_new_message = CAN_Read_Message(&COB_ID, data);
	if (is_new_message) {
		/* Save latest */
		canopen->COB_ID = COB_ID;
		memcpy(canopen->data, data, 8);
		canopen->COB_ID_and_data_is_updated = true;

		/* Read the COB ID */
		uint8_t function_code = COB_ID >> 7;											/* What service should we use */
		uint16_t node_ID = 0x7F & COB_ID;												/* Node ID = 0 for masters. Node ID 1 to 127 for slaves */

		/* Get this node ID */
		uint32_t this_node_ID = 0;
		CANopen_OD_get_dictionary_object_value(canopen, OD_INDEX_IDENTITY_OBJECT, OD_SUB_INDEX_5, &this_node_ID);

		if(function_code == FUNCTION_CODE_NMT){

		}else if(function_code == FUNCTION_CODE_SYNC | FUNCTION_CODE_EMCY) {
			if(node_ID == 0x0){
				/* SYNC */
			}else{
				/* EMCY */
			}
		}else if(function_code == FUNCTION_CODE_TIME){

		}else if(function_code == FUNCTION_CODE_PDO1_TRANSMIT){

		}else if(function_code == FUNCTION_CODE_PDO1_RECEIVE){

		}else if(function_code == FUNCTION_CODE_PDO2_TRANSMIT){

		}else if(function_code == FUNCTION_CODE_PDO2_RECEIVE){

		}else if(function_code == FUNCTION_CODE_PDO3_TRANSMIT){

		}else if(function_code == FUNCTION_CODE_PDO3_RECEIVE){

		}else if(function_code == FUNCTION_CODE_PDO4_TRANSMIT){

		}else if(function_code == FUNCTION_CODE_PDO4_RECEIVE){

		}else if(function_code == FUNCTION_CODE_SDO_TRANSMIT){

		}else if(function_code == FUNCTION_CODE_SDO_RECEIVE){

		}else if(function_code == FUNCTION_CODE_HEARTBEAT | FUNCTION_CODE_GUARD){
			if(data[0] == 0x0 && node_ID == this_node_ID){
				CANopen_Client_GUARD_Receive_Request_Guard(canopen, node_ID); 								/* Guard requests have zero data */
			}else{
				CANopen_Consumer_HEARTBEAT_Receive_Heartbeat(canopen, node_ID, data);						/* Only one process can be active */
				CANopen_Server_GUARD_Receive_Response_Guard(canopen, node_ID, data);
			}
		}else if(function_code == FUNCTION_CODE_LSS_TRANSMIT){

		}else if(function_code == FUNCTION_CODE_LSS_RECEIVE){

		}
	}

	return is_new_message;
}
