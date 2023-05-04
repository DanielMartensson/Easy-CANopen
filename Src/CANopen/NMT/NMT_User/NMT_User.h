/*
 * NMT_User.h
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_NMT_NMT_USER_NMT_USER_H_
#define CANOPEN_NMT_NMT_USER_NMT_USER_H_

#include "../../../Easy_CANopen/Easy_CANopen_Structs.h"

void CANopen_Master_NMT_Transmit_Operation_State(CANopen *canopen, uint8_t cs, uint8_t node_ID);

#endif /* CANOPEN_NMT_NMT_USER_NMT_USER_H_ */
