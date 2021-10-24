/*
 * CANopen_Server_SDO_Receive.c
 *
 *  Created on: 24 okt. 2021
 *      Author: Daniel Mårtensson
 */

void CANopen_Server_SDO_Receive_Response(CANopen *canopen, uint8_t node_ID, uint8_t message[]){
	uint8_t cs = message[0];
	uint16_t index = (message[2] << 8) | message[1];
	uint8_t sub_index = message[3];
	uint32_t data = (message[7] << 24) | (message[6] << 16) | (message[5] << 8) | message[4];
	if(cs == CS_SDO_CLIENT_RESPONDS){

	}else if(cs == CS_SDO_SERVER_WRITE_DATA_UNKNOWN){

	}
}
