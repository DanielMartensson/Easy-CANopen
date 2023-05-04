/*
 * NMT_Protocol.h
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_NMT_NMT_INTERNAL_NMT_PROTOCOL_NMT_PROTOCOL_H_
#define CANOPEN_NMT_NMT_INTERNAL_NMT_PROTOCOL_NMT_PROTOCOL_H_

#include "../../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* 7.2.8.3.1 in CiA 305 1.1.1 */
void CANopen_NMT_Protocol_Receive_Request_Enter_Status(CANopen *canopen, uint8_t status);
void CANopen_NMT_Protocol_Transmit_Request_State(CANopen *canopen, uint8_t cs, uint8_t node_ID);
void CANopen_NMT_Protocol_Receive_Request_Node_Reset(CANopen *canopen);
void CANopen_NMT_Protocol_Receive_Request_Restore_Communication_Parameters(CANopen *canopen);

#endif /* CANOPEN_NMT_NMT_INTERNAL_NMT_PROTOCOL_NMT_PROTOCOL_H_ */
