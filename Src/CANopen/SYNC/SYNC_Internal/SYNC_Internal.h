/*
 * SYNC_Internal.h
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_SYNC_SYNC_INTERNAL_SYNC_INTERNAL_H_
#define CANOPEN_SYNC_SYNC_INTERNAL_SYNC_INTERNAL_H_

#include "../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* Internal software functions that the user don't need to call */
void CANopen_Producer_SYNC_Transmit_Synchronization(CANopen *canopen);
void CANopen_Consumer_SYNC_Receive_Synchronization(CANopen *canopen, uint8_t node_ID, uint8_t data[]);


#endif /* CANOPEN_SYNC_SYNC_INTERNAL_SYNC_INTERNAL_H_ */
