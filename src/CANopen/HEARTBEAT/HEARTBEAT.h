/*
 * HEARTBEAT.h
 *
 *  Created on: 14 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_HEARTBEAT_HEARTBEAT_H_
#define CANOPEN_HEARTBEAT_HEARTBEAT_H_

#include "../../Easy_CANopen/Structs.h"

void CANopen_Producer_HEARTBEAT_Transmit_Heartbeat(CANopen *canopen);
void CANopen_Consumer_HEARTBEAT_Receive_Heartbeat(CANopen *canopen, uint8_t node_ID, uint8_t data[]);

#endif /* CANOPEN_HEARTBEAT_HEARTBEAT_H_ */
