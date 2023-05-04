/*
 * GUARD_Internal.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_GUARD_GUARD_INTERNAL_GUARD_INTERNAL_H_
#define CANOPEN_GUARD_GUARD_INTERNAL_GUARD_INTERNAL_H_

#include "../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* Internal software functions that the user don't need to call */
void CANopen_Client_GUARD_Receive_Response_Status(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Server_GUARD_Receive_Request_Status(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Server_GUARD_Transmit_Response(CANopen *canopen, uint8_t node_ID);

#endif /* CANOPEN_GUARD_GUARD_INTERNAL_GUARD_INTERNAL_H_ */
