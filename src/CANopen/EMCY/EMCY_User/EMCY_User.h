/*
 * EMCY_User.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_EMCY_EMCY_USER_EMCY_USER_H_
#define CANOPEN_EMCY_EMCY_USER_EMCY_USER_H_

#include "../../../Easy_CANopen/Structs.h"

void CANopen_Producer_EMCY_Transmit_Error(CANopen *canopen, uint16_t new_error_code, uint8_t new_error_register, uint8_t vendor_specific_data[]);

#endif /* CANOPEN_EMCY_EMCY_USER_EMCY_USER_H_ */
