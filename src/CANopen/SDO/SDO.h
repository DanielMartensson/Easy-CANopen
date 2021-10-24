/*
 * SDO.h
 *
 *  Created on: 24 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_SDO_SDO_H_
#define CANOPEN_SDO_SDO_H_

#include "../../Easy_CANopen/Structs.h"

/* Server */
void CANopen_Server_SDO_Transmit_Request(CANopen *canopen, uint8_t cs, uint8_t node_ID, uint16_t index, uint8_t sub_index, uint32_t data);
void CANopen_Server_SDO_Receive_Response(CANopen *canopen, uint8_t node_ID, uint8_t message[]);

/* Client */
void CANopen_Client_SDO_Receive_Request(CANopen *canopen, uint8_t node_ID, uint8_t message[]);
void CANopen_Client_SDO_Transmit_Response(CANopen *canopen, uint8_t cs, uint8_t node_ID, uint16_t index, uint8_t sub_index, uint32_t data);

#endif /* CANOPEN_SDO_SDO_H_ */
