/*
 * PDO_Internal.h
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_PDO_PDO_INTERNAL_PDO_INTERNAL_H_
#define CANOPEN_PDO_PDO_INTERNAL_PDO_INTERNAL_H_

#include "../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* Internal software functions that the user don't need to call */
void CANopen_Producer_PDO_Transmit_Data(CANopen *canopen);
void CANopen_Producer_PDO_Receive_Request(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Consumer_PDO_Receive_Data(CANopen *canopen, uint8_t node_ID, uint8_t data[]);


#endif /* CANOPEN_PDO_PDO_INTERNAL_PDO_INTERNAL_H_ */
