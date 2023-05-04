/*
 * HEARTBEAT_Internal.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_HEARTBEAT_HEARTBEAT_INTERNAL_HEARTBEAT_INTERNAL_H_
#define CANOPEN_HEARTBEAT_HEARTBEAT_INTERNAL_HEARTBEAT_INTERNAL_H_

#include "../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* Internal software functions that the user don't need to call */
void CANopen_Consumer_HEARTBEAT_Receive_Status(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Producer_HEARTBEAT_Transmit_Status(CANopen *canopen);
void CANopen_Producer_HEARTBEAT_Transmit_Bootup_Message(CANopen *canopen);

#endif /* CANOPEN_HEARTBEAT_HEARTBEAT_INTERNAL_HEARTBEAT_INTERNAL_H_ */
