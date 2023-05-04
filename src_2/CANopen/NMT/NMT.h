/*
 * NMT.h
 *
 *  Created on: 10 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_NMT_NMT_H_
#define CANOPEN_NMT_NMT_H_

#include "../../Easy_CANopen/Easy_CANopen_Structs.h"

/* Transmit */
void CANopen_Master_NMT_Transmit_Operation_State(CANopen *canopen, uint8_t cs, uint8_t node_ID);

/* Receive + tools */
void CANopen_Slave_NMT_Receive_Request(CANopen *canopen, uint8_t data[]);
void CANopen_Slave_NMT_Restore_OD_Communication_To_Default_Parameters(CANopen *canopen);
void CANopen_Slave_NMT_Reset_Node_Struct(CANopen *canopen);

#endif /* CANOPEN_NMT_NMT_H_ */
