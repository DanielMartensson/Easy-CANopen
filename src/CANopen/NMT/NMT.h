/*
 * NMT.h
 *
 *  Created on: 10 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_NMT_NMT_H_
#define CANOPEN_NMT_NMT_H_

#include "../../Easy_CANopen/Structs.h"

void CANopen_Master_NMT_Transmit_Operation_State(CANopen *canopen, uint8_t cs, uint8_t node_ID);
void CANopen_Slave_NMT_Receive(CANopen *canopen, uint8_t data[]);

#endif /* CANOPEN_NMT_NMT_H_ */
