/*
 * Listen_For_Messages.c
 *
 *  Created on: 6 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "Easy_CANopen.h"

/* Layers */
#include "../Hardware/CAN_Network_Layer/CAN_Network_Layer.h"

/* Enums */
#include "../COB/COB_Enums/Enum_Function_Codes.h"

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
		uint8_t function_code = COB_ID >> 7;
		uint16_t node_ID = 0x7F & COB_ID;												/* Node ID = 0 for masters. Node ID 1 to 127 for slaves */

		if(function_code == NMT_FUNCTION_CODE){

		}else if(function_code == SYNC_FUNCTION_CODE && node_ID == 0x0){

		}else if(function_code == EMCY_FUNCTION_CODE && node_ID > 0x0){

		}else if(function_code == TIME_FUNCTION_CODE){

		}else if(function_code == PDO1_TRANSMIT_FUNCTION_CODE){

		}else if(function_code == PDO1_RECEIVE_FUNCTION_CODE){

		}else if(function_code == PDO2_TRANSMIT_FUNCTION_CODE){

		}else if(function_code == PDO2_RECEIVE_FUNCTION_CODE){

		}else if(function_code == PDO3_TRANSMIT_FUNCTION_CODE){

		}else if(function_code == PDO3_RECEIVE_FUNCTION_CODE){

		}else if(function_code == PDO4_TRANSMIT_FUNCTION_CODE){

		}else if(function_code == PDO4_RECEIVE_FUNCTION_CODE){

		}else if(function_code == SDO_TRANSMIT_FUNCTION_CODE){

		}else if(function_code == SDO_RECEIVE_FUNCTION_CODE){

		}else if(function_code == HEARTBEAT_FUNCTION_CODE){

		}else if(function_code == NMT_EC_FUNCTION_CODE){

		}else if(function_code == LSS_FUNCTION_CODE && node_ID == 0x64){

		}else if(function_code == LSS_FUNCTION_CODE && node_ID == 0x65){

		}
	}

	return is_new_message;
}
