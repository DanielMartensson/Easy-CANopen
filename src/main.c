#include <stdio.h>
#include <stdlib.h>

/* Include Easy CANopen */
#include "Easy_CANopen/Easy_CANopen.h"

int main() {
	/* Declare our structures */
	CANopen master_node = { 0 };
	CANopen slave_node = { 0 }; /* Notice that ONLY one slave node can be connected to the CAN network */

	/* Begin to activate node configuration so we can write our node ID */
	Easy_CANopen_Other_Node_Activate_Node_Configuration(true);

	/* Reading process for the slave node */
	Easy_CANopen_Thread_Listen_Messages(&slave_node);

	/* Set identification to slave */
	uint32_t vendor_ID = 10003;
	uint32_t product_code = 65467;
	uint32_t revision_number = 565;
	uint32_t serial_number = 3234;
	Easy_CANopen_Other_Node_Set_Vendor_ID_To_Node(&master_node, vendor_ID);
	Easy_CANopen_Other_Node_Set_Product_Code_To_Node(&master_node, product_code);
	Easy_CANopen_Other_Node_Set_Revision_Number_To_Node(&master_node, revision_number);
	Easy_CANopen_Other_Node_Set_Serial_Number_To_Node(&master_node, serial_number);

	/* Reading process for the slave */
	Easy_CANopen_Thread_Listen_Messages(&slave_node);
	Easy_CANopen_Thread_Listen_Messages(&slave_node);
	Easy_CANopen_Thread_Listen_Messages(&slave_node);
	Easy_CANopen_Thread_Listen_Messages(&slave_node);

	/* Read the process for the master */
	Easy_CANopen_Thread_Listen_Messages(&master_node);

	/* Display the identifications for slave node */
	printf("Vendor ID = %i\n", slave_node.od_communication.vendor_ID);
	printf("Product code = %i\n", slave_node.od_communication.product_code);
	printf("Revision number = %i\n", slave_node.od_communication.revision_number);
	printf("Serial number = %i\n", slave_node.od_communication.serial_number);

	/* Dispay the response from the slave */
	printf("Response is set: %i\n", master_node.master.lss.selective_value_is_set);

	return 0;
}