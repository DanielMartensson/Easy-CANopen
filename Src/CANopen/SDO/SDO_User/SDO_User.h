/*
 * SDO_User.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_SDO_SDO_USER_SDO_USER_H_
#define CANOPEN_SDO_SDO_USER_SDO_USER_H_

#include "../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* User application functions */
void CANopen_Client_SDO_Transmit_Request(CANopen *canopen, uint8_t cs, uint8_t node_ID, uint16_t index, uint8_t sub_index, uint32_t value);

#endif /* CANOPEN_SDO_SDO_USER_SDO_USER_H_ */
