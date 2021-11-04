/*
 * GUARD_Protocol.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_GUARD_GUARD_INTERNAL_GUARD_PROTOCOL_GUARD_PROTOCOL_H_
#define CANOPEN_GUARD_GUARD_INTERNAL_GUARD_PROTOCOL_GUARD_PROTOCOL_H_

/* 7.2.8.3.2.1 in CiA 301 4.2.0 */
void CANopen_GUARD_Protocol_Status_Request_Create(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_GUARD_Protocol_Status_Response_Create(CANopen *canopen, uint8_t node_ID, uint8_t data[]);

#endif /* CANOPEN_GUARD_GUARD_INTERNAL_GUARD_PROTOCOL_GUARD_PROTOCOL_H_ */