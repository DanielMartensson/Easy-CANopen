/*
 * PDO_User.h
 *
 *  Created on: 15 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_PDO_PDO_USER_PDO_USER_H_
#define CANOPEN_PDO_PDO_USER_PDO_USER_H_

#include "../../../Easy_CANopen/Easy_CANopen_Structs.h"

void CANopen_Consumer_PDO_Transmit_Request(CANopen *canopen, uint8_t node_ID);

#endif /* CANOPEN_PDO_PDO_USER_PDO_USER_H_ */
