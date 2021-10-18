/*
 * lss.h
 *
 *  Created on: 8 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_LSS_LSS_H_
#define CANOPEN_LSS_LSS_H_

#include "../../Easy_CANopen/Structs.h"

/* Master */
void CANopen_Master_LSS_Transmit_Request_Switch_Mode_Global(uint8_t mode);
void CANopen_Master_LSS_Transmit_Request_Switch_Mode_Selective_Value(uint8_t cs, uint32_t value);
void CANopen_Master_LSS_Transmit_Request_Configure_Node_ID(uint8_t node_ID);
void CANopen_Master_LSS_Transmit_Request_Configure_Bit_Timing_Parameters(uint8_t table_index);
void CANopen_Master_LSS_Transmit_Request_Active_Bit_Timing_Parameters(uint16_t delay);
void CANopen_Master_LSS_Transmit_Request_Store_Configuration();
void CANopen_Master_LSS_Transmit_Request_Inquire_Identity_Value(uint8_t cs);
void CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(uint8_t cs, uint32_t value);
void CANopen_Master_LSS_Transmit_Request_Identify_Non_Configured_Remote_Slave();
void CANopen_Master_LSS_Receive(CANopen *canopen, uint8_t data[]);

/* Slave */
void CANopen_Slave_LSS_Transmit_Response_Switch_Mode_Selective_Value();
void CANopen_Slave_LSS_Transmit_Response_Status_Message(uint8_t cs, uint8_t status_code, uint8_t status_code_specific);
void CANopen_Slave_LSS_Transmit_Response_Inquire_Identity_Value(uint8_t cs, uint32_t value);
void CANopen_Slave_LSS_Transmit_Response_Identity_Remote_Slave();
void CANopen_Slave_LSS_Transmit_Response_Identify_Non_Configured_Remote_Slave();
void CANopen_Slave_LSS_Receive(CANopen *canopen, uint8_t data[]);

#endif /* CANOPEN_LSS_LSS_H_ */
