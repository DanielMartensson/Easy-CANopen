/*
 * CANopen_PDO_Protocol_Produce.c
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "PDO_Protocol.h"

/* Layers */
#include "../../../OD/OD.h"
#include "../../../../Hardware/Hardware.h"

void CANopen_PDO_Protocol_Produce_TPDO(CANopen *canopen, struct PDO *pdo, struct PDO_mapping *tpdo_m, struct PDO_communication *tpdo_c, FUNCTION_CODE function_code){
	/* Check if TPDO Communication parameter is valid */
	uint8_t valid = tpdo_c->COB_ID >> 31;
	if(valid == 0)
		return; /* Nope */

	/* Set the execute flag */
	bool execute_transmission = false;

	/* Check transmission type */
	if(tpdo_c->transmission_type == 0xFF) {
		/* event-driven (device profile and application profile specific) */
		if(pdo->event_timer_counter >= tpdo_c->event_timer)
			execute_transmission = true;

		/* Count +1 or reset to 0 if counter is event_timer */
		pdo->event_timer_counter = pdo->event_timer_counter == tpdo_c->event_timer ? 0 : pdo->event_timer_counter++;

	}else if(tpdo_c->transmission_type >= 0x1 && tpdo_c->transmission_type <= 0xF0) {
		/* This is a starting threshold */
		if(canopen->slave.sync.counter >= tpdo_c->sync_start_value)
			pdo->start_counting_sync = true;

		/* Count +1 or reset to 1 if counter is type */
		if(pdo->start_counting_sync)
			pdo->sync_counter_value = pdo->sync_counter_value == tpdo_c->transmission_type ? 1 : pdo->sync_counter_value++;

		/* synchronous (cyclic every X SYNC) */
		if(pdo->sync_counter_value >= tpdo_c->transmission_type)
			execute_transmission = true;
	}else{
		/* Reset */
		pdo->event_timer_counter = 0;
		pdo->start_counting_sync = false;
		pdo->sync_counter_value = 0;
		return; /* Only synchronous and event-driven transmission is supported */
	}

	/* Collect data and send */
	uint8_t data[8] = {0};
	uint8_t position = 0;
	for(uint8_t i = 0; i < tpdo_m->number_of_mapped_objects_in_PDO; i++){

		/* Get the mapping parameters of PDO */
		uint16_t index = tpdo_m->object_to_be_mapped[i] >> 16;
		uint8_t sub_index = tpdo_m->object_to_be_mapped[i] >> 8;
		uint8_t length = tpdo_m->object_to_be_mapped[i];
		uint8_t length_in_bytes = length / 8;

		/* Get the value from OD */
		uint32_t value = CANopen_OD_Get_Value(canopen, index, sub_index);

		/* Quick check if the data array is full */
		if(length_in_bytes + position >= 8)
			break;

		/* Insert value to data  */
		switch(length){
		case 8:
			data[position++] = value;
			break;
		case 16:
			data[position++] = value;
			data[position++] = value >> 8;
			break;
		case 32:
			data[position++] = value;
			data[position++] = value >> 8;
			data[position++] = value >> 16;
			data[position++] = value >> 32;
			break;
		}
	}

	/* Create the COB ID */
	uint32_t COB_ID = function_code << 7 | canopen->slave.this_node_ID;

	/* Send the message to client */
	Hardware_CAN_Send_Message(COB_ID, data);
}
