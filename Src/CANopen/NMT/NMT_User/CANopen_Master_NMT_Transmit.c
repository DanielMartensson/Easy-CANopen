/*
 * CANopen_Master_NMT_Transmit.c
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "NMT_User.h"

/* Layers */
#include "../NMT_Internal/NMT_Protocol/NMT_Protocol.h"

void CANopen_Master_NMT_Transmit_Operation_State(CANopen *canopen, uint8_t cs, uint8_t node_ID){
	CANopen_NMT_Protocol_Transmit_Request_State(canopen, cs, node_ID);
}
