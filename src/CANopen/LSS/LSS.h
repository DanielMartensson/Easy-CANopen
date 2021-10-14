/*
 * lss.h
 *
 *  Created on: 8 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_LSS_LSS_H_
#define CANOPEN_LSS_LSS_H_

/* Enums and structs */
#include "../../CANopen/Enums/Enum_Baudrate_Codes.h"
#include "../../CANopen/Enums/Enum_Command_Specifier_Codes.h"
#include "../../CANopen/Enums/Enum_Function_Codes.h"
#include "../../CANopen/Enums/Enum_Mode_Codes.h"
#include "../../Easy_CANopen/Structs.h"


/* Transmit master -> slave functions */
void CANopen_Transmit_LSS_Switch_Mode_Global_Protocol_From_Master_To_Slave(uint8_t mode);
void CANopen_Transmit_LSS_Switch_Mode_Selective_Protocol_Vendor_Id_From_Master_To_Slave(uint32_t vendor_id);
void CANopen_Transmit_LSS_Switch_Mode_Selective_Protocol_Product_Code_From_Master_To_Slave(uint32_t product_code);
void CANopen_Transmit_LSS_Switch_Mode_Selective_Protocol_Revision_Number_From_Master_To_Slave(uint32_t revision_number);
void CANopen_Transmit_LSS_Switch_Mode_Selective_Protocol_Serial_Number_From_Master_To_Slave(uint32_t serial_number);
void CANopen_Transmit_LSS_Configure_Node_Id_From_Master_To_Slave(uint8_t node_id);
void CANopen_Transmit_LSS_Configure_Baudrate_From_Master_To_Slave(uint8_t table_index_baudrate);
void CANopen_Transmit_LSS_Activate_Baudrate_From_Master_To_Slave(uint16_t switch_delay);
void CANopen_Transmit_LSS_Store_Configuration_From_Master_To_Slave();
void CANopen_Transmit_LSS_Inquire_Vendor_Id_From_Master_To_Slave();
void CANopen_Transmit_LSS_Inquire_Product_Code_From_Master_To_Slave();
void CANopen_Transmit_LSS_Inquire_Revision_Number_From_Master_To_Slave();
void CANopen_Transmit_LSS_Inquire_Serial_Number_From_Master_To_Slave();
void CANopen_Transmit_LSS_Inquire_Node_Id_From_Master_To_Slave();
void CANopen_Transmit_LSS_Identify_Vendor_Id_From_Master_To_Slave(uint32_t vendor_id);
void CANopen_Transmit_LSS_Identify_Product_Code_From_Master_To_Slave(uint32_t product_code);
void CANopen_Transmit_LSS_Identify_Revision_Number_Low_From_Master_To_Slave(uint32_t serial_number_low);
void CANopen_Transmit_LSS_Identify_Revision_Number_High_From_Master_To_Slave(uint32_t revision_number_high);
void CANopen_Transmit_LSS_Identify_Serial_Number_Low_From_Master_To_Slave(uint32_t serial_number_low);
void CANopen_Transmit_LSS_Identify_Serial_Number_High_From_Master_To_Slave(uint32_t serial_number_high);
void CANopen_Transmit_LSS_Identify_Non_Configured_Remote_Slave_Protocol_From_Master_To_Slave();

/* Receive master -> slave functions */
void CANopen_Receive_LSS_From_Master_To_Slave(CANopen *canopen, uint8_t node_id, uint8_t data[]);

/* Transmit slave -> master functions */
void CANopen_Transmit_LSS_Response_Switch_Mode_Selective_Protocol_Response_From_Slave_To_Master();
void CANopen_Transmit_LSS_Response_Status_Message_From_Slave_To_Master(uint8_t command_specifier, uint8_t status_code, uint8_t status_code_manufacturer_specific);
void CANopen_Transmit_LSS_Response_Vendor_Id_From_Slave_To_Master(CANopen *canopen);
void CANopen_Transmit_LSS_Response_Product_Code_From_Slave_To_Master(CANopen *canopen);
void CANopen_Transmit_LSS_Response_Revision_Number_From_Slave_To_Master(CANopen *canopen);
void CANopen_Transmit_LSS_Response_Serial_Number_From_Slave_To_Master(CANopen *canopen);
void CANopen_Transmit_LSS_Response_Node_Id_From_Slave_To_Master(CANopen *canopen);
void CANopen_Transmit_LSS_Response_Identify_Slave_Remote_Slave_Protocol();

/* Receive slave -> master functions */
void CANopen_Receive_LSS_From_Slave_To_Master(CANopen *canopen, uint8_t node_id, uint8_t data[]);

#endif /* CANOPEN_LSS_LSS_H_ */
