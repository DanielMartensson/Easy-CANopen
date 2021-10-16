/*
 * GUARD.h
 *
 *  Created on: 15 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_GUARD_GUARD_H_
#define CANOPEN_GUARD_GUARD_H_

#include "../../Easy_CANopen/Structs.h"

STATUS_CODE CANopen_Server_GUARD_Receive_Response_Guard(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
STATUS_CODE CANopen_Server_GUARD_Transmit_Request_Guard(CANopen *canopen, uint8_t node_ID);
STATUS_CODE CANopen_Client_GUARD_Receive_Request_Guard(CANopen *canopen, uint8_t node_ID);
STATUS_CODE CANopen_Client_GUARD_Transmit_Response_Guard(CANopen *canopen, uint8_t node_ID);

#endif /* CANOPEN_GUARD_GUARD_H_ */
