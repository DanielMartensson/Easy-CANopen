/*
 * EMCY_Internal.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_EMCY_EMCY_INTERNAL_EMCY_INTERNAL_H_
#define CANOPEN_EMCY_EMCY_INTERNAL_EMCY_INTERNAL_H_

#include "../../../Easy_CANopen/Structs.h"

/* Internal software functions that the user don't need to call */
void CANopen_Consumer_EMCY_Receive(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Producer_EMCY_Transmit_Status(CANopen *canopen, uint8_t node_ID, uint8_t data[]);

#endif /* CANOPEN_EMCY_EMCY_INTERNAL_EMCY_INTERNAL_H_ */
