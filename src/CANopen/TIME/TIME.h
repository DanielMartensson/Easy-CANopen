/*
 * TIME.h
 *
 *  Created on: 19 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_TIME_TIME_H_
#define CANOPEN_TIME_TIME_H_

#include "../../Easy_CANopen/Structs.h"

void CANopen_Producer_TIME_Transmit_Clock(CANopen *canopen);
void CANopen_Consumer_TIME_Receive_Clock(CANopen *canopen, uint8_t data[]);

#endif /* CANOPEN_TIME_TIME_H_ */
