/*
 * LSS_Internal.h
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_LSS_LSS_INTERNAL_LSS_INTERNAL_H_
#define CANOPEN_LSS_LSS_INTERNAL_LSS_INTERNAL_H_

#include "../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* Internal software functions that the user don't need to call */
void CANopen_Master_LSS_Receive_Response(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Slave_LSS_Receive_Request(CANopen *canopen, uint8_t node_ID, uint8_t data[]);
void CANopen_Slave_LSS_Transmit_Response_Switch_Mode_Selective_Value();
void CANopen_Slave_LSS_Transmit_Response_Status_Message(uint8_t cs, uint8_t status_code, uint8_t status_code_specific);
void CANopen_Slave_LSS_Transmit_Response_Inquire_Identity_Value(uint8_t cs, uint32_t value);
void CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
void CANopen_Slave_LSS_Transmit_Response_Identify_Non_Configured_Remote_Slave();

#endif /* CANOPEN_LSS_LSS_INTERNAL_LSS_INTERNAL_H_ */
