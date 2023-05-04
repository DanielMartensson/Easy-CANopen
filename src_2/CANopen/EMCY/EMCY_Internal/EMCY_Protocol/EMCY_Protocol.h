/*
 * EMCY_Protocol.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_EMCY_EMCY_INTERNAL_EMCY_PROTOCOL_EMCY_PROTOCOL_H_
#define CANOPEN_EMCY_EMCY_INTERNAL_EMCY_PROTOCOL_EMCY_PROTOCOL_H_

#include "../../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* 7.2.7.3.1 in CiA 301 4.2.0 */
void CANopen_EMCY_Protocol_Produce_Error(CANopen *canopen, uint16_t new_error_code, uint8_t new_error_register, uint8_t vendor_specific_data[]);
void CANopen_EMCY_Protocol_Consume_Error(CANopen *canopen, uint8_t node_ID, uint8_t data[]);

#endif /* CANOPEN_EMCY_EMCY_INTERNAL_EMCY_PROTOCOL_EMCY_PROTOCOL_H_ */
