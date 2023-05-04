/*
 * NMT_Internal.h
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_NMT_NMT_INTERNAL_NMT_INTERNAL_H_
#define CANOPEN_NMT_NMT_INTERNAL_NMT_INTERNAL_H_

#include "../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* Internal software functions that the user don't need to call */
void CANopen_Slave_NMT_Receive_Request(CANopen *canopen, uint8_t node_ID, uint8_t data[]);

#endif /* CANOPEN_NMT_NMT_INTERNAL_NMT_INTERNAL_H_ */
