/*
 * EMCY.h
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_EMCY_EMCY_H_
#define CANOPEN_EMCY_EMCY_H_

#include "../../Easy_CANopen/Structs.h"

void CANopen_Producer_EMCY_Transmit_Error_Message(CANopen *canopen, uint16_t new_error_code, uint8_t new_error_register, uint8_t vendor_specific_data[]);
void CANopen_Consumer_EMCY_Receive_Error_Message(CANopen *canopen, uint8_t node_ID, uint8_t data[]);

#endif /* CANOPEN_EMCY_EMCY_H_ */
