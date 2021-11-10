/*
 * PDO_Protocol.h
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_PDO_PDO_INTERNAL_PDO_PROTOCOL_PDO_PROTOCOL_H_
#define CANOPEN_PDO_PDO_INTERNAL_PDO_PROTOCOL_PDO_PROTOCOL_H_

#include "../../../../Easy_CANopen/Structs.h"

/* 7.5.2 and 7.2.2 in CiA 305 1.1.1 */
void CANopen_PDO_Protocol_Produce_Data(CANopen *canopen, struct PDO *pdo, struct PDO_mapping *pdo_mapping, struct PDO_communication *pdo_communication, FUNCTION_CODE function_code);
void CANopen_PDO_Protocol_Consume_Data(CANopen *canopen, struct PDO_mapping *pdo_communication, uint8_t data[]);

#endif /* CANOPEN_PDO_PDO_INTERNAL_PDO_PROTOCOL_PDO_PROTOCOL_H_ */
