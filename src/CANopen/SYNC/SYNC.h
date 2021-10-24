/*
 * SYNC.h
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_SYNC_SYNC_H_
#define CANOPEN_SYNC_SYNC_H_

#include "../../Easy_CANopen/Structs.h"

void CANopen_Producer_SYNC_Transmit_Synchronization(CANopen *canopen, uint8_t node_ID, uint8_t counter);
void CANopen_Consumer_SYNC_Receive_Synchronization(CANopen *canopen);

#endif /* CANOPEN_SYNC_SYNC_H_ */
