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
STATUS_CODE CANopen_Master_LSS_Transmit_Switch_Mode_Global_Protocol(uint8_t mode);
STATUS_CODE CANopen_Master_LSS_Transmit_Switch_Mode_Selective_Protocol_Value(CANopen *canopen, uint8_t cs, uint32_t value);
STATUS_CODE CANopen_Master_LSS_Transmit_Configure_Protocol_Node_ID(CANopen *canopen, uint8_t node_ID);
STATUS_CODE CANopen_Master_LSS_Transmit_Configure_Protocol_Bit_Timing_Parameters(CANopen *canopen, uint8_t table_index);
STATUS_CODE CANopen_Master_LSS_Transmit_Active_Protocol_Bit_Timing_Parameters(CANopen *canopen, uint16_t delay);
STATUS_CODE CANopen_Master_LSS_Transmit_Store_Configuration_Protocol(CANopen *canopen);
STATUS_CODE CANopen_Master_LSS_Transmit_Inquire_Identity_Value(CANopen *canopen, uint8_t cs);
STATUS_CODE CANopen_Master_LSS_Transmit_Identity_Remote_Slave_Protocol_Value(CANopen *canopen, uint8_t cs, uint32_t value);
STATUS_CODE CANopen_Master_LSS_Transmit_Identify_Non_Configured_Remote_Slave_Protocol(CANopen *canopen);
STATUS_CODE CANopen_Master_LSS_Receive(CANopen *canopen, uint8_t data[]);

/* Slave */
STATUS_CODE CANopen_Slave_LSS_Transmit_Switch_Mode_Selective_Protocol_Value_Response(uint8_t cs);
STATUS_CODE CANopen_Slave_LSS_Transmit_Status_Response(uint8_t cs, uint8_t status_code, uint8_t status_code_specific);
STATUS_CODE CANopen_Slave_LSS_Transmit_Inquire_Identity_Protocol_Response(uint8_t cs, uint32_t value);
STATUS_CODE CANopen_Slave_LSS_Transmit_Identity_Remote_Slave_Protocol_Reponse();
STATUS_CODE CANopen_Slave_LSS_Transmit_Identify_Non_Configured_Remote_Slave_Protocol_Response();
STATUS_CODE CANopen_Slave_LSS_Receive(CANopen *canopen, uint8_t data[]);

#endif /* CANOPEN_LSS_LSS_H_ */
