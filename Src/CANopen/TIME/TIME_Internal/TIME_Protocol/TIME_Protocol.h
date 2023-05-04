/*
 * TIME_Protocol.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_TIME_TIME_INTERNAL_TIME_PROTOCOL_TIME_PROTOCOL_H_
#define CANOPEN_TIME_TIME_INTERNAL_TIME_PROTOCOL_TIME_PROTOCOL_H_

#include "../../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* 7.2.6.3.1 CiA 301 4.2.0 */
void CANopen_TIME_Protocol_Produce_Clock(CANopen *canopen);
void CANopen_TIME_Protocol_Consume_Clock(CANopen *canopen, uint8_t data[]);


#endif /* CANOPEN_TIME_TIME_INTERNAL_TIME_PROTOCOL_TIME_PROTOCOL_H_ */
