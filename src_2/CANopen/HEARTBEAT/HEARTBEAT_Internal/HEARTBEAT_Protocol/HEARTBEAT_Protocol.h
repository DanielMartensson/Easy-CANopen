/*
 * HEARTBEAT_Protocol.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_HEARTBEAT_HEARTBEAT_INTERNAL_HEARTBEAT_PROTOCOL_HEARTBEAT_PROTOCOL_H_
#define CANOPEN_HEARTBEAT_HEARTBEAT_INTERNAL_HEARTBEAT_PROTOCOL_HEARTBEAT_PROTOCOL_H_

#include "../../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* 7.2.8.3.2.2 in CiA 301 4.2.0 */
void CANopen_HEARTBEAT_Protocol_Produce_Status(CANopen *canopen, uint8_t node_ID);
void CANopen_HEARTBEAT_Protocol_Produce_Bootup_Mesage(CANopen *canopen, uint8_t node_ID);
void CANopen_HEARTBEAT_Protocol_Consume_Status(CANopen *canopen, uint8_t node_ID, uint8_t data[]);

#endif /* CANOPEN_HEARTBEAT_HEARTBEAT_INTERNAL_HEARTBEAT_PROTOCOL_HEARTBEAT_PROTOCOL_H_ */
