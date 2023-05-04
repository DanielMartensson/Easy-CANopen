/*
 * SYNC_Protocol.h
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_SYNC_SYNC_INTERNAL_SYNC_PROTOCOL_SYNC_PROTOCOL_H_
#define CANOPEN_SYNC_SYNC_INTERNAL_SYNC_PROTOCOL_SYNC_PROTOCOL_H_

#include "../../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* 7.2.5.3.1 in CiA 301 4.2.0 */
void CANopen_SYNC_Protocol_Consume_Synchronization(CANopen *canopen, uint8_t data[]);
void CANopen_SYNC_Protocol_Produce_Synchronization(CANopen *canopen);


#endif /* CANOPEN_SYNC_SYNC_INTERNAL_SYNC_PROTOCOL_SYNC_PROTOCOL_H_ */

