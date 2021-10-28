/*
 * CANopen_Client_SDO_Receive.c
 *
 *  Created on: 24 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "SDO.h"

/* Layers */
#include "../OD/OD.h"

void CANopen_Client_SDO_Receive_Response(CANopen *canopen, uint8_t node_ID, uint8_t message[]){
	canopen->slave.sdo.cs = message[0];
	canopen->slave.sdo.index = (message[2] << 8) | message[1];
	canopen->slave.sdo.sub_index = message[3];
	canopen->slave.sdo.data = (message[7] << 24) | (message[6] << 16) | (message[5] << 8) | message[4];
	canopen->slave.sdo.from_node_ID = node_ID;
}
