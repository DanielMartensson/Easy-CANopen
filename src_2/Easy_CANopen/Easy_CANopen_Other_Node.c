/*
 * Easy_CANopen_Other_Node.c
 *
 *  Created on: 18 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "Easy_CANopen.h"

/* Layers */
#include "../CANopen/CANopen_User.h"

/*
 * Activates the configuration mode to a node. This MUST be done before if you want to send configurations to the node
 * Requirements: Only ONE node in the network.
 * Responses: 	 No repose back
 */
void Easy_CANopen_Other_Node_Activate_Node_Configuration(bool activate){
	uint8_t mode = activate == true ? MODE_CONFIGURATION : MODE_WAITING;
	CANopen_Master_LSS_Transmit_Request_Switch_Mode_Global(mode);
}

/*
 * Set the vendor ID to a node.
 * Requirements: Only ONE node in the network.
 * 				 The node need have have their configuration activated
 * Responses: 	 When the vendor ID is set, then the boolean selective value in the struct will be true
 */
void Easy_CANopen_Other_Node_Set_Vendor_ID_To_Node(CANopen *canopen, uint32_t vendor_ID){
	canopen->master.lss.selective_value_is_set = false; /* This will update to true when the slave sends out its response back to the master */
	CANopen_Master_LSS_Transmit_Request_Switch_Mode_Selective_Value(CS_LSS_SWITCH_MODE_SELECTIVE_VENDOR_ID, vendor_ID);
}

/*
 * Set the product code to a node.
 * Requirements: Only ONE node in the network.
 * 				 The node need have have their configuration activated
 * Responses: 	 When the product code is set, then the boolean selective value in the struct will be true
 */
void Easy_CANopen_Other_Node_Set_Product_Code_To_Node(CANopen *canopen, uint32_t product_code){
	canopen->master.lss.selective_value_is_set = false; /* This will update to true when the slave sends out its response back to the master */
	CANopen_Master_LSS_Transmit_Request_Switch_Mode_Selective_Value(CS_LSS_SWITCH_MODE_SELECTIVE_PRODUCT_CODE, product_code);
}

/*
 * Set the revision number to a node.
 * Requirements: Only ONE node in the network.
 * 				 The node need have have their configuration activated
 * Responses: 	 When the revision number is set, then the boolean selective value in the struct will be true
 */
void Easy_CANopen_Other_Node_Set_Revision_Number_To_Node(CANopen *canopen, uint32_t revision_number){
	canopen->master.lss.selective_value_is_set = false; /* This will update to true when the slave sends out its response back to the master */
	CANopen_Master_LSS_Transmit_Request_Switch_Mode_Selective_Value(CS_LSS_SWITCH_MODE_SELECTIVE_REVISION_NUMBER, revision_number);
}

/*
 * Set the serial number to a node.
 * Requirements: Only ONE node in the network.
 * 				 The node need have have their configuration activated
 * Responses: 	 When the serial number is set, then the boolean selective value in the struct will be true
 */
void Easy_CANopen_Other_Node_Set_Serial_Number_To_Node(CANopen *canopen, uint32_t serial_number){
	canopen->master.lss.selective_value_is_set = false; /* This will update to true when the slave sends out its response back to the master */
	CANopen_Master_LSS_Transmit_Request_Switch_Mode_Selective_Value(CS_LSS_SWITCH_MODE_SELECTIVE_SERIAL_NUMBER, serial_number);
}

/*
 * Set the node ID to a node.
 * Requirements: Only ONE node in the network.
 * 				 The node need have have their configuration activated
 * Responses:	 When the node is set, then the LSS master will receive a status code back if the node ID was successfully applied or not.
 */
void Easy_CANopen_Other_Node_Set_Node_ID_To_Node(CANopen *canopen, uint8_t node_ID){
	canopen->master.lss.status_code_is_new = false; /* These two error codes will have a value later when the salve responds back */
	canopen->master.lss.status_code = 0;
	canopen->master.lss.status_code_specific = 0;
	CANopen_Master_LSS_Transmit_Request_Configure_Node_ID(node_ID);
}

/*
 * Set the baud rate to a node. Notice that this does not activate the baud rate.
 * Requirements: Only ONE node in the network.
 * 				 The node need have have their configuration activated
 * Responses:	 When the baud rate is set, then the LSS master will receive a status code back if the baud rate was successfully set or not
 */
void Easy_CANopen_Other_Node_Set_Baud_Rate_To_Node(CANopen *canopen, uint8_t table_index, uint16_t delay){
	canopen->master.lss.status_code_is_new = false; /* These two error codes will have a value later when the salve responds back */
	canopen->master.lss.status_code = 0;
	canopen->master.lss.status_code_specific = 0;
	CANopen_Master_LSS_Transmit_Request_Configure_Bit_Timing_Parameters(table_index);
	CANopen_Master_LSS_Transmit_Request_Active_Bit_Timing_Parameters(delay);
}

/*
 * Activate the baud rate to a node.
 * Requirements: Only ONE node in the network.
 * 				 The node need have have their configuration activated
 * Responses:	 When the baud rate is activated, then the LSS master will receive a status code back if the baud rate was successfully activated or not.
 */
void Easy_CANopen_Other_Node_Save_Node_ID_And_Baud_Rate_In_Node(CANopen *canopen){
	canopen->master.lss.status_code_is_new = false; /* These two error codes will have a value later when the salve responds back */
	canopen->master.lss.status_code = 0;
	canopen->master.lss.status_code_specific = 0;
	CANopen_Master_LSS_Transmit_Request_Store_Configuration();
}

/*
 * Get the vendor ID from a node.
 * Requirements: Only ONE node in the network.
 * Responses:	 Then the LSS master will receive the vendor ID back from the node.
 */
void Easy_CANopen_Other_Node_Get_Vendor_ID_From_Node(CANopen *canopen){
	canopen->master.lss.vendor_ID = 0; /* Reset, then it will have another number when the master receive the response */
	CANopen_Master_LSS_Transmit_Request_Inquire_Identity_Value(CS_LSS_INQUIRE_IDENTITY_VENDOR_ID);
}

/*
 * Get the product code from a node.
 * Requirements: Only ONE node in the network.
 * Responses:	 The LSS master will receive the vendor ID back from the node.
 */
void Easy_CANopen_Other_Node_Get_Product_Code_From_Node(CANopen *canopen){
	canopen->master.lss.product_code = 0; /* Reset, then it will have another number when the master receive the response */
	CANopen_Master_LSS_Transmit_Request_Inquire_Identity_Value(CS_LSS_INQUIRE_IDENTITY_PRODUCT_CODE);
}

/*
 * Get the revision number from a node.
 * Requirements: Only ONE node in the network.
 * Responses:	 The LSS master will receive the revision number back from the node.
 */
void Easy_CANopen_Other_Node_Get_Revision_Number_From_Node(CANopen *canopen){
	canopen->master.lss.revision_number = 0; /* Reset, then it will have another number when the master receive the response */
	CANopen_Master_LSS_Transmit_Request_Inquire_Identity_Value(CS_LSS_INQUIRE_IDENTITY_REVISION_NUMBER);
}

/*
 * Get the serial number from a node.
 * Requirements: Only ONE node in the network.
 * Responses:	 The LSS master will receive the serial number back from the node.
 */
void Easy_CANopen_Other_Node_Get_Serial_Number_From_Node(CANopen *canopen){
	canopen->master.lss.serial_number = 0; /* Reset, then it will have another number when the master receive the response */
	CANopen_Master_LSS_Transmit_Request_Inquire_Identity_Value(CS_LSS_INQUIRE_IDENTITY_SERIAL_NUMBER);
}

/*
 * Get the node ID from a node.
 * Requirements: Only ONE node in the network.
 * Responses:	 The LSS master will receive the node ID back from the node.
 */
void Easy_CANopen_Other_Node_Get_Node_ID_From_Node(CANopen *canopen){
	canopen->master.lss.node_ID = 0; /* Reset, then it will have another number when the master receive the response */
	CANopen_Master_LSS_Transmit_Request_Inquire_Identity_Value(CS_LSS_INQUIRE_IDENTITY_NODE_ID);
}

/*
 * Check the identity if the vendor ID exist in a CAN network
 * Requirements: No requirements
 * Responses:	 The LSS master will receive a boolean value in the struct if the identity has been found
 */
void Easy_CANopen_Other_Node_Check_If_This_Vendor_ID_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t vendor_ID){
	canopen->master.lss.identity_found = false; /* Reset, then it will be true if it exist */
	CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(CS_LSS_IDENTIFY_REMOTE_SLAVE_VENDOR_ID, vendor_ID);
}

/*
 * Check the identity if the product code exist in a CAN network
 * Requirements: No requirements
 * Responses:	 The LSS master will receive a boolean value in the struct if the identity has been found
 */
void Easy_CANopen_Other_Node_Check_If_This_Product_Code_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t product_code){
	canopen->master.lss.identity_found = false; /* Reset, then it will be true if it exist */
	CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(CS_LSS_IDENTIFY_REMOTE_SLAVE_PRODUCT_CODE, product_code);
}

/*
 * Check the identity if the revision number or lower exist in a CAN network
 * Requirements: No requirements
 * Responses:	 The LSS master will receive a boolean value in the struct if the identity has been found
 */
void Easy_CANopen_Other_Node_Check_If_This_Revision_Number_Or_Lower_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t revision_number){
	canopen->master.lss.identity_found = false; /* Reset, then it will be true if it exist */
	CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(CS_LSS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_LOW, revision_number);
}

/*
 * Check the identity if the revision number or higher exist in a CAN network
 * Requirements: No requirements
 * Responses:	 The LSS master will receive a boolean value in the struct if the identity has been found
 */
void Easy_CANopen_Other_Node_Check_If_This_Revision_Number_Or_Higher_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t revision_number){
	canopen->master.lss.identity_found = false; /* Reset, then it will be true if it exist */
	CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(CS_LSS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_HIGH, revision_number);
}

/*
 * Check the identity if the serial number or lower exist in a CAN network
 * Requirements: No requirements
 * Responses:	 The LSS master will receive a boolean value in the struct if the identity has been found
 */
void Easy_CANopen_Other_Node_Check_If_This_Serial_Number_Or_Lower_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t serial_number){
	canopen->master.lss.identity_found = false; /* Reset, then it will be true if it exist */
	CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(CS_LSS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_LOW, serial_number);
}

/*
 * Check the identity if the serial number or higher exist in a CAN network
 * Requirements: No requirements
 * Responses:	 The LSS master will receive a boolean value in the struct if the identity has been found
 */
void Easy_CANopen_Other_Node_Check_If_This_Serial_Number_Or_Higher_Exist_At_The_CAN_Network(CANopen *canopen, uint32_t serial_number){
	canopen->master.lss.identity_found = false; /* Reset, then it will be true if it exist */
	CANopen_Master_LSS_Transmit_Request_Identity_Remote_Slave_Value(CS_LSS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_HIGH, serial_number);
}

/*
 * Check if there are any nodes that have the error address 0xFF in a CAN network
 * Requirements: No requirements
 * Responses:	 The LSS master will receive a boolean value in the struct if a non configured node ID has been found
 */
void Easy_CANopen_Other_Node_Check_If_There_Are_Any_Non_Configured_Nodes_At_The_CAN_Network(CANopen *canopen){
	canopen->master.lss.non_configured_node_ID_found = false; /* This will be true when a node has the node ID 0xFF */
	CANopen_Master_LSS_Transmit_Request_Identify_Non_Configured_Remote_Slave();
}

/*
 * Activate the services PDO, SDO, SYNC, TIME, EMCY, HEARTBEAT and GUARD at a node.
 * Requirements: The node need to have a node ID address
 * Responses:	 No responses back
 */
void Easy_CANopen_Other_Node_Start_Remote_Node(CANopen *canopen, uint8_t node_ID){
	CANopen_Master_NMT_Transmit_Operation_State(canopen, CS_NMT_SERVICE_START_REMOTE_NODE, node_ID);
}

/*
 * Deactivate the services PDO, SDO, SYNC, TIME, EMCY at a node.
 * Requirements: The node need to have a node ID address
 * Responses:	 No responses back
 */
void Easy_CANopen_Other_Node_Stop_Remote_Node(CANopen *canopen, uint8_t node_ID){
	CANopen_Master_NMT_Transmit_Operation_State(canopen, CS_NMT_SERVICE_STOP_REMOTE_NODE, node_ID);
}

