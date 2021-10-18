/*
 * Easy_CANopen.h
 *
 *  Created on: 6 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef EASY_CANOPEN_EASY_CANOPEN_H_
#define EASY_CANOPEN_EASY_CANOPEN_H_

/* Enums and structs */
#include "Structs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* This functions must be called all the time, or be placed inside an interrupt listener */
bool Easy_CANopen_Listen_For_Messages(CANopen *canopen);

/* This function must be called every millisecond */
void Easy_CANopen_Transmitting_Of_Messages(CANopen *canopen);

/* This function should ONLY be called at your node startup */
bool Easy_CANopen_Startup_Node(CANopen *canopen);

/* Node configurations */
void Easy_CANopen_Activate_Node_Configuration(bool activate);
void Easy_CANopen_Set_Vendor_ID_To_Node(CANopen *canopen, uint32_t vendor_ID);
void Easy_CANopen_Set_Product_Code_To_Node(CANopen *canopen, uint32_t product_code);
void Easy_CANopen_Set_Revision_Number_To_Node(CANopen *canopen, uint32_t revision_number);
void Easy_CANopen_Set_Serial_Number_To_Node(CANopen *canopen, uint32_t serial_number);
void Easy_CANopen_Set_Node_ID_To_Node(CANopen *canopen, uint8_t node_ID);
void Easy_CANopen_Set_Baud_Rate_To_Node(CANopen *canopen, uint8_t table_index, uint16_t delay);
void Easy_CANopen_Save_Node_ID_And_Baud_Rate_In_Node();
void Easy_CANopen_Get_Vendor_ID_From_Node(CANopen *canopen);
void Easy_CANopen_Get_Product_Code_From_Node(CANopen *canopen);
void Easy_CANopen_Get_Revision_Number_From_Node(CANopen *canopen);
void Easy_CANopen_Get_Serial_Number_From_Node(CANopen *canopen);
void Easy_CANopen_Get_Node_ID_From_Node(CANopen *canopen);
void Easy_CANopen_Check_If_This_Vendor_ID_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t vendor_ID);
void Easy_CANopen_Check_If_This_Product_Code_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t product_code);
void Easy_CANopen_Check_If_This_Revision_Number_Or_Lower_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t revision_number);
void Easy_CANopen_Check_If_This_Revision_Number_Or_Higher_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t revision_number);
void Easy_CANopen_Check_If_This_Serial_Number_Or_Lower_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t serial_number);
void Easy_CANopen_Check_If_This_Serial_Number_Or_Higher_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t serial_number);
void Easy_CANopen_Check_If_There_Are_Any_Non_Configured_Nodes_At_The_CAN_Network(CANopen *canopen);

#ifdef __cplusplus
}
#endif

#endif /* EASY_CANOPEN_EASY_CANOPEN_H_ */
