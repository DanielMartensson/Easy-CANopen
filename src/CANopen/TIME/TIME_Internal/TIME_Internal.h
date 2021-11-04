/*
 * TIME_Internal.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_TIME_TIME_INTERNAL_TIME_INTERNAL_H_
#define CANOPEN_TIME_TIME_INTERNAL_TIME_INTERNAL_H_

/* Internal software functions that the user don't need to call */
void CANopen_Consumer_TIME_Receive_Clock(CANopen *canopen, uint8_t data[]);

#endif /* CANOPEN_TIME_TIME_INTERNAL_TIME_INTERNAL_H_ */