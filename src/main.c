#include <stdio.h>
#include <stdlib.h>

/* Include Easy CANopen */
#include "Easy_CANopen/Easy_CANopen.h"

int main() {
	/* Declare our structures */
	CANopen master_node = {0};
	CANopen slave_node = {0}; /* Notice that ONLY one slave node can be connected to the CAN network */

	/* Begin to activate node configuration so we can write our node ID */
	Easy_CANopen_Other_Node_Activate_Node_Configuration(true);

	/* Reading process */
	Easy_CANopen_Thread_Listen_Messages(&slave_node);

	/* Set new ID to slave node */
	uint8_t new_node_ID = 0x20; /* 32 */
	Easy_CANopen_Other_Node_Set_Node_ID_To_Node(&master_node, new_node_ID);

	/* Reading process */
	Easy_CANopen_Thread_Listen_Messages(&slave_node);

	/* Display the node ID for slave node */
	printf("New node ID for slave node = 0x%X", slave_node.slave.this_node_ID);

	return 0;
}
