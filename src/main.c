#include <stdio.h>
#include <stdlib.h>

/* Include Easy CANopen */
#include "Easy_CANopen/Easy_CANopen.h"

int main() {
	/* Declare our structures */
	CANopen slave_node_1 = {0};
	CANopen slave_node_2 = {0}; /* Notice that ONLY one slave node can be connected to the CAN network */

	/* Set node ID for the slave */
	slave_node_1.slave.this_node_ID = 50;
	slave_node_2.slave.this_node_ID = 100;

	/* To receive guard status messages, then producer heartbeat must be zero */
	slave_node_1.od_communication.producer_heartbeat_time = 0;
	slave_node_2.od_communication.producer_heartbeat_time = 0;

	/* Also set the guard time and life time factor */
	slave_node_1.od_communication.guard_time = 100;
	slave_node_1.od_communication.life_time_factor = 1;

	/* Set the operational status */
	slave_node_2.slave.nmt.this_node_status_operational = STATUS_OPERATIONAL_PRE_OPERATIONAL;

	/* Send 10 heartbeat messages */
	for(uint8_t i = 0; i < 10; i++){

		/* Send guard request from slave node 1 to slave node 2 */
		Easy_CANopen_This_Node_Transmit_Guard_Status_Request(&slave_node_1, slave_node_2.slave.this_node_ID);

		/* Readning process for the slave nodes */
		Easy_CANopen_Thread_Listen_Messages(&slave_node_2); /* Read request and send response */
		Easy_CANopen_Thread_Listen_Messages(&slave_node_1); /* Read response */

		/* Check the response from slave node 1 */
		printf("Status operational for slave node 2: %i\n", slave_node_1.slave.nmt.from_node_status_operational);
		printf("Toggle for slave node 2: %i\n", slave_node_1.slave.nmt.from_node_toggle);
	}

	return 0;
}
