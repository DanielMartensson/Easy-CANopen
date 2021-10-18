/*
 * Node_Configuration.c
 *
 *  Created on: 18 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "Easy_CANopen.h"

/* Layers */
#include "../CANopen/LSS/LSS.h"

void Easy_CANopen_Activate_Node_Configuration(bool activate){
	uint8_t mode = activate == true ? MODE_CONFIGURATION : MODE_WAITING;
	CANopen_Master_LSS_Transmit_Request_Switch_Mode_Global(mode);
}

void Easy_CANopen_Set_Vendor_ID_To_Node(CANopen *canopen, uint32_t vendor_ID){
	canopen->master.lss.selective_value_is_set = false; /* This will update to true when the slave sends out its response back to the master */
	CANopen_Master_LSS_Transmit_Request_Switch_Mode_Selective_Value(CS_SWITCH_MODE_SELECTIVE_VENDOR_ID, vendor_ID);
}

void Easy_CANopen_Set_Product_Code_To_Node(CANopen *canopen, uint32_t product_code){
	canopen->master.lss.selective_value_is_set = false; /* This will update to true when the slave sends out its response back to the master */
	CANopen_Master_LSS_Transmit_Request_Switch_Mode_Selective_Value(CS_SWITCH_MODE_SELECTIVE_PRODUCT_CODE, product_code);
}

void Easy_CANopen_Set_Revision_Number_To_Node(CANopen *canopen, uint32_t revision_number){
	canopen->master.lss.selective_value_is_set = false; /* This will update to true when the slave sends out its response back to the master */
	CANopen_Master_LSS_Transmit_Request_Switch_Mode_Selective_Value(CS_SWITCH_MODE_SELECTIVE_REVISION_NUMBER, revision_number);
}

void Easy_CANopen_Set_Serial_Number_To_Node(CANopen *canopen, uint32_t serial_number){
	canopen->master.lss.selective_value_is_set = false; /* This will update to true when the slave sends out its response back to the master */
	CANopen_Master_LSS_Transmit_Request_Switch_Mode_Selective_Value(CS_SWITCH_MODE_SELECTIVE_SERIAL_NUMBER, serial_number);
}

void Easy_CANopen_Set_Node_ID_To_Node(CANopen *canopen, uint8_t node_ID){
	canopen->master.lss.status_code_is_new = false; /* These two error codes will have a value later when the salve responds back */
	canopen->master.lss.status_code = 0;
	canopen->master.lss.status_code_specific = 0;
	CANopen_Master_LSS_Transmit_Request_Configure_Node_ID(node_ID);
}

void Easy_CANopen_Set_Baud_Rate_To_Node(CANopen *canopen, uint8_t table_index, uint16_t delay){
	canopen->master.lss.status_code_is_new = false; /* These two error codes will have a value later when the salve responds back */
	canopen->master.lss.status_code = 0;
	canopen->master.lss.status_code_specific = 0;
	CANopen_Master_LSS_Transmit_Request_Configure_Bit_Timing_Parameters(table_index);
	CANopen_Master_LSS_Transmit_Request_Active_Bit_Timing_Parameters(delay);
}

void Easy_CANopen_Save_Node_ID_And_Baud_Rate_In_Node(CANopen *canopen){
	canopen->master.lss.status_code_is_new = false; /* These two error codes will have a value later when the salve responds back */
	canopen->master.lss.status_code = 0;
	canopen->master.lss.status_code_specific = 0;
	CANopen_Master_LSS_Transmit_Request_Store_Configuration();
}

void Easy_CANopen_Get_Vendor_ID_From_Node(CANopen *canopen){
	canopen->master.lss.vendor_ID = 0; /* Reset, then it will have another number when the master receive the response */
	CANopen_Master_LSS_Transmit_Request_Inquire_Identity_Value(CS_INQUIRE_IDENTITY_VENDOR_ID);
}

void Easy_CANopen_Get_Product_Code_From_Node(CANopen *canopen){
	canopen->master.lss.product_code = 0; /* Reset, then it will have another number when the master receive the response */
	CANopen_Master_LSS_Transmit_Request_Inquire_Identity_Value(CS_INQUIRE_IDENTITY_PRODUCT_CODE);
}

void Easy_CANopen_Get_Revision_Number_From_Node(CANopen *canopen){
	canopen->master.lss.revision_number = 0; /* Reset, then it will have another number when the master receive the response */
	CANopen_Master_LSS_Transmit_Request_Inquire_Identity_Value(CS_INQUIRE_IDENTITY_REVISION_NUMBER);
}

void Easy_CANopen_Get_Serial_Number_From_Node(CANopen *canopen){
	canopen->master.lss.serial_number = 0; /* Reset, then it will have another number when the master receive the response */
	CANopen_Master_LSS_Transmit_Request_Inquire_Identity_Value(CS_INQUIRE_IDENTITY_SERIAL_NUMBER);
}

void Easy_CANopen_Get_Node_ID_From_Node(CANopen *canopen){
	canopen->master.lss.node_ID = 0; /* Reset, then it will have another number when the master receive the response */
	CANopen_Master_LSS_Transmit_Request_Inquire_Identity_Value(CS_INQUIRE_IDENTITY_NODE_ID);
}

void Easy_CANopen_Check_If_This_Vendor_ID_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t vendor_ID){
	canopen->master.lss.identity_found = false; /* Reset, then it will be true if it exist */
	CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(CS_IDENTIFY_REMOTE_SLAVE_VENDOR_ID, vendor_ID);
}

void Easy_CANopen_Check_If_This_Product_Code_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t product_code){
	canopen->master.lss.identity_found = false; /* Reset, then it will be true if it exist */
	CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(CS_IDENTIFY_REMOTE_SLAVE_PRODUCT_CODE, product_code);
}

void Easy_CANopen_Check_If_This_Revision_Number_Or_Lower_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t revision_number){
	canopen->master.lss.identity_found = false; /* Reset, then it will be true if it exist */
	CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(CS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_LOW, revision_number);
}

void Easy_CANopen_Check_If_This_Revision_Number_Or_Higher_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t revision_number){
	canopen->master.lss.identity_found = false; /* Reset, then it will be true if it exist */
	CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(CS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_HIGH, revision_number);
}

void Easy_CANopen_Check_If_This_Serial_Number_Or_Lower_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t serial_number){
	canopen->master.lss.identity_found = false; /* Reset, then it will be true if it exist */
	CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(CS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_LOW, serial_number);
}

void Easy_CANopen_Check_If_This_Serial_Number_Or_Higher_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t serial_number){
	canopen->master.lss.identity_found = false; /* Reset, then it will be true if it exist */
	CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(CS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_HIGH, serial_number);
}

void Easy_CANopen_Check_If_There_Are_Any_Non_Configured_Nodes_At_The_CAN_Network(CANopen *canopen){
	canopen->master.lss.non_configured_node_ID_found = false;
	CANopen_Master_LSS_Transmit_Request_Identify_Non_Configured_Remote_Slave();
}
