/*
 * LSS_Protocol.h
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_LSS_LSS_INTERNAL_LSS_PROTOCOL_LSS_PROTOCOL_H_
#define CANOPEN_LSS_LSS_INTERNAL_LSS_PROTOCOL_LSS_PROTOCOL_H_

#include "../../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* 5 LSS PROTOCOL PERSPECTIVE in CiA 305 1.1.1 */
void CANopen_LSS_Protocol_Transmit_Request_Switch_Mode_Global(uint8_t mode);
void CANopen_LSS_Protocol_Transmit_Request_Switch_Mode_Selective_Value(uint8_t cs, uint32_t value);
void CANopen_LSS_Protocol_Transmit_Request_Configure_Node_ID(uint8_t node_ID);
void CANopen_LSS_Protocol_Transmit_Request_Configure_Bit_Timing_Parameters(uint8_t table_index);
void CANopen_LSS_Protocol_Transmit_Request_Active_Bit_Timing_Parameters(uint16_t delay);
void CANopen_LSS_Protocol_Transmit_Request_Store_Configuration();
void CANopen_LSS_Protocol_Transmit_Request_Inquire_Identity_Value(uint8_t cs);
void CANopen_LSS_Protocol_Transmit_Request_Identity_Remote_Slave_Value(uint8_t cs, uint32_t value);
void CANopen_LSS_Protocol_Transmit_Request_Identify_Non_Configured_Remote_Slave();

/* 5 LSS PROTOCOL PERSPECTIVE in CiA 305 1.1.1 */
void CANopen_LSS_Protocol_Receive_Request_Switch_Mode_Global(CANopen *canopen, uint8_t data[]);
void CANopen_LSS_Protocol_Receive_Request_Switch_Mode_Selective_Value(CANopen *canopen, uint8_t data[]);
void CANopen_LSS_Protocol_Receive_Request_Configure_Node_ID(CANopen *canopen, uint8_t data[]);
void CANopen_LSS_Protocol_Receive_Request_Configure_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]);
void CANopen_LSS_Protocol_Receive_Request_Activate_Bit_Timing_Parameters(CANopen *canopen, uint8_t data[]);
void CANopen_LSS_Protocol_Receive_Request_Store_Configuration(CANopen *canopen, uint8_t data[]);
void CANopen_LSS_Protocol_Receive_Request_Inquire_Identity_Value(CANopen *canopen, uint8_t data[]);
void CANopen_LSS_Protocol_Receive_Request_Identity_Remote_Slave_Value(CANopen *canopen, uint8_t data[]);
void CANopen_LSS_Protocol_Receive_Request_Identify_Non_Configured_Remote_Slave(CANopen *canopen, uint8_t data[]);

/* 5 LSS PROTOCOL PERSPECTIVE in CiA 305 1.1.1 */
void CANopen_LSS_Protocol_Transmit_Response_Switch_Mode_Selective_Value();
void CANopen_LSS_Protocol_Transmit_Response_Status_Message(uint8_t cs, uint8_t status_code, uint8_t status_code_specific);
void CANopen_LSS_Protocol_Transmit_Response_Inquire_Identity_Value(uint8_t cs, uint32_t value);
void CANopen_LSS_Protocol_Transmit_Response_Identity_Remote_Slave();
void CANopen_LSS_Protocol_Transmit_Response_Identify_Non_Configured_Remote_Slave();

/* 5 LSS PROTOCOL PERSPECTIVE in CiA 305 1.1.1 */
void CANopen_LSS_Protocol_Receive_Response_Switch_Mode_Selective(CANopen *canopen);
void CANopen_LSS_Protocol_Receive_Response_Status_Message(CANopen *canopen, uint8_t data[]);
void CANopen_LSS_Protocol_Receive_Response_Inquire_Identity_Value(CANopen *canopen, uint8_t data[]);
void CANopen_LSS_Protocol_Receive_Response_Identity_Remote_Slave(CANopen *canopen);
void CANopen_LSS_Protocol_Receive_Response_Identify_Non_Configured_Remote_Slave(CANopen *canopen);


#endif /* CANOPEN_LSS_LSS_INTERNAL_LSS_PROTOCOL_LSS_PROTOCOL_H_ */
