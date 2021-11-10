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
void CANopen_PDO_Protocol_Produce_TPDO(CANopen *canopen, struct PDO *pdo, struct PDO_mapping *tpdo_m, struct PDO_communication *tpdo_c, FUNCTION_CODE function_code);
void CANopen_PDO_Protocol_Consume_TPDO(CANopen *canopen, struct PDO_mapping *rpdo_m, uint8_t data[]);

#endif /* CANOPEN_PDO_PDO_INTERNAL_PDO_PROTOCOL_PDO_PROTOCOL_H_ */
