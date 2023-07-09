/*
 * CANopen_SYNC_Protocol_Produce.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */
 
#include "../../../../Hardware/Hardware.h"

#include "SYNC_Protocol.h"

void CANopen_SYNC_Protocol_Produce_Synchronization(CANopen *canopen){

	/* Should we include a counter value or not */
	uint8_t synchronous_counter_overflow_value = canopen->od_communication.synchronous_counter_overflow_value;
	if(synchronous_counter_overflow_value == 0)
		canopen->master.sync.counter = 0; /* No counting value for the PDO */
	else if(synchronous_counter_overflow_value >= 2 && synchronous_counter_overflow_value <= 0xF0)
		canopen->master.sync.counter = canopen->master.sync.counter == 0 ? 1 : canopen->master.sync.counter++; /* Increase with +1 for every call, but the counter can never be zero */
	else
		return; /* TODO: Send SDO abort code */

	/* Create the COB ID */
	uint16_t COB_ID = FUNCTION_CODE_SYNC_EMCY << 7; /* Node ID is zero here */

	/* Send the data */
	uint8_t data[8] = {0};
	data[0] = canopen->master.sync.counter;
	Hardware_CAN_Send_Message(COB_ID, data);
}
