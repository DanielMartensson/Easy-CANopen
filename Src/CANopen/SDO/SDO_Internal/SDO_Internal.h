/*
 * SDO_Internal.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_SDO_SDO_INTERNAL_SDO_INTERNAL_H_
#define CANOPEN_SDO_SDO_INTERNAL_SDO_INTERNAL_H_

#include "../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* Internal software functions that the user don't need to call */
void CANopen_Client_SDO_Receive_Response(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Server_SDO_Receive_Request(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Server_SDO_Transmit_Response(CANopen *canopen, uint8_t node_ID, uint8_t data[]);

#endif /* CANOPEN_SDO_SDO_INTERNAL_SDO_INTERNAL_H_ */
