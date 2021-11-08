/*
 * CANopen_PDO_Protocol_Produce.c
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "PDO_Protocol.h"

void CANopen_PDO_Protocol_Produce_Data(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Check if TPDO Communication parameter is valid */
	uint8_t valid = canopen->od_communication.TPDO1_C.COB_ID >> 31;
	if(valid == 0)
		return; /* Nope */

	/* Starting values */
	bool execute_transmission = false;
	uint8_t type = canopen->od_communication.TPDO1_C.transmission_type;
	uint16_t event_timer = canopen->od_communication.TPDO1_C.event_timer;
	uint8_t sync_start_value = canopen->od_communication.TPDO1_C.sync_start_value;

	/* Check transmission type */
	if(type == 0xFF) {
		/* event-driven (device profile and application profile specific) */
		if(canopen->slave.pdo1.event_timer_counter >= event_timer)
			execute_transmission = true;

		/* Count +1 or reset to 0 if counter is event_timer */
		canopen->slave.pdo1.event_timer_counter = canopen->slave.pdo1.event_timer_counter == event_timer ? 0 : canopen->slave.pdo1.event_timer_counter++;

	}else if(type >= 0x1 && type <= 0xF0) {
		/* This is a starting threshold */
		if(canopen->slave.sync.counter >= sync_start_value)
			canopen->slave.pdo1.start_counting_sync = true;

		/* Count +1 or reset to 1 if counter is type */
		if(canopen->slave.pdo1.start_counting_sync)
			canopen->slave.pdo1.sync_counter_value = canopen->slave.pdo1.sync_counter_value == type ? 1 : canopen->slave.pdo1.sync_counter_value++;

		/* synchronous (cyclic every X SYNC) */
		if(canopen->slave.pdo1.sync_counter_value >= type)
			execute_transmission = true;
	}else{
		/* Reset */
		canopen->slave.pdo1.event_timer_counter = 0;
		canopen->slave.pdo1.start_counting_sync = false;
		canopen->slave.pdo1.sync_counter_value = 0;
		return; /* Only synchronous and event-driven transmission is supported */
	}

	/* Collect data and send */
	uint8_t i = canopen->od_communication.TPDO1_M.number_of_mapped_objects_in_PDO;

}

