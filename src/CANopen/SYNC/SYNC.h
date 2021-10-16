/*
 * SYNC.h
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_SYNC_SYNC_H_
#define CANOPEN_SYNC_SYNC_H_

#include "../../Easy_CANopen/Structs.h"

STATUS_CODE CANopen_Master_SYNC_Transmit_Synchronization(CANopen *canopen);
STATUS_CODE CANopen_Slave_SYNC_Receive_Synchronization(CANopen *canopen);

#endif /* CANOPEN_SYNC_SYNC_H_ */
