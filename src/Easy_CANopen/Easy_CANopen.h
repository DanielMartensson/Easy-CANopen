/*
 * Easy_CANopen.h
 *
 *  Created on: 6 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef EASY_CANOPEN_EASY_CANOPEN_H_
#define EASY_CANOPEN_EASY_CANOPEN_H_

/* Enums and structs */
#include "Structs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* This functions must be called all the time, or be placed inside an interrupt listener */
bool Easy_CANopen_Listen_For_Messages(CANopen *canopen);

/* This function must be called every millisecond */
void Easy_CANopen_Transmitting_Of_Messages(CANopen *canopen);

/* This function should ONLY be called at your node startup */
bool Easy_CANopen_Startup_Node(CANopen *canopen);

#ifdef __cplusplus
}
#endif

#endif /* EASY_CANOPEN_EASY_CANOPEN_H_ */
