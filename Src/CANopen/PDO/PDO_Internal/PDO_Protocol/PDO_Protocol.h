/*
 * PDO_Protocol.h
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_PDO_PDO_INTERNAL_PDO_PROTOCOL_PDO_PROTOCOL_H_
#define CANOPEN_PDO_PDO_INTERNAL_PDO_PROTOCOL_PDO_PROTOCOL_H_

#include "../../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* 7.5.2 and 7.2.2 in CiA 305 1.1.1 */
void CANopen_PDO_Protocol_Produce_Request(uint16_t CAN_ID);
void CANopen_PDO_Protocol_Produce_Data(CANopen *canopen, PDO_mapping* PDO_mapping_transmit, uint16_t COB_ID);
void CANopen_PDO_Protocol_Consume_Data(CANopen *canopen, PDO_mapping* PDO_mapping_receive, uint8_t data[]);

#endif /* CANOPEN_PDO_PDO_INTERNAL_PDO_PROTOCOL_PDO_PROTOCOL_H_ */
