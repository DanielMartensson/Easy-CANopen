/*
 * GUARD_User.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_GUARD_GUARD_USER_GUARD_USER_H_
#define CANOPEN_GUARD_GUARD_USER_GUARD_USER_H_

#include "../../../Easy_CANopen/Structs.h"

void CANopen_Client_GUARD_Transmit_Request(CANopen *canopen, uint8_t node_ID, uint8_t data[]);

#endif /* CANOPEN_GUARD_GUARD_USER_GUARD_USER_H_ */
