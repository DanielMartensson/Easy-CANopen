/*
 * PDO_Internal.h
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_PDO_PDO_INTERNAL_PDO_INTERNAL_H_
#define CANOPEN_PDO_PDO_INTERNAL_PDO_INTERNAL_H_

#include "../../../Easy_CANopen/Structs.h"

/* Internal software functions that the user don't need to call */
void CANopen_Producer_PDO_Transmit_TPDO1(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Producer_PDO_Transmit_TPDO2(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Producer_PDO_Transmit_TPDO3(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Producer_PDO_Transmit_TPDO4(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Producer_PDO_Transmit_RPDO1(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Producer_PDO_Transmit_RPDO2(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Producer_PDO_Transmit_RPDO3(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Producer_PDO_Transmit_RPDO4(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Consumer_PDO_Receive_TPDO1(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Consumer_PDO_Receive_TPDO2(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Consumer_PDO_Receive_TPDO3(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Consumer_PDO_Receive_TPDO4(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Consumer_PDO_Receive_RPDO1(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Consumer_PDO_Receive_RPDO2(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Consumer_PDO_Receive_RPDO3(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Consumer_PDO_Receive_RPDO4(CANopen *canopen, uint8_t node_ID, uint8_t data[]);

#endif /* CANOPEN_PDO_PDO_INTERNAL_PDO_INTERNAL_H_ */
