/*
 * CANopen_Producer_PDO_Transmit.c
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "PDO_Internal.h"

/* Layers */
#include "PDO_Protocol/PDO_Protocol.h"

void CANopen_Producer_PDO_Transmit_Data(CANopen *canopen) {
	/* Check if this is master node */
	uint8_t node_ID = canopen->slave.this_node_ID;
	if(node_ID == 0)
		return; /* This is master node - Cannot send */

	/* Check if PDO service is enabled */
	if(canopen->slave.nmt.this_node_status_operational != STATUS_OPERATIONAL_OPERATIONAL)
		return; /* NMT is not in operational mode. PDO service is disabled */

	for(uint8_t i = 0; i < PDO_LENGTH; i++){
		/* Check if TPDO Communication parameter is valid */
		uint8_t valid = canopen->od_communication.PDO_communication_transmit[i].COB_ID >> 31; /// @todo I dont't understand
		if(valid == 1)
			continue; /* Just skip */

		/* Set the execute flag */
		bool execute_transmission = false;

		/* Check transmission type */
		if(canopen->od_communication.PDO_communication_transmit[i].transmission_type == 0xFF) {
			/* event-driven (device profile and application profile specific) */
			if(canopen->slave.pdo[i].event_timer_counter >= canopen->od_communication.PDO_communication_transmit[i].event_timer)
				execute_transmission = true;

			/* Count +1 or reset to 0 if counter is event_timer */
			if(canopen->slave.pdo[i].event_timer_counter == canopen->od_communication.PDO_communication_transmit[i].event_timer)
				canopen->slave.pdo[i].event_timer_counter = 0;
			else
				canopen->slave.pdo[i].event_timer_counter++;
		}else if(canopen->od_communication.PDO_communication_transmit[i].transmission_type >= 0x1 && canopen->od_communication.PDO_communication_transmit[i].transmission_type <= 0xF0){
			/* This is a starting threshold */
			if(canopen->slave.sync.counter >= canopen->od_communication.PDO_communication_transmit[i].sync_start_value)
				canopen->slave.pdo[i].start_counting_sync = true;

			/* Count +1 or reset to 1 if counter is type */
			if(canopen->slave.pdo[i].start_counting_sync){
				if(canopen->slave.pdo[i].sync_counter_value < canopen->od_communication.PDO_communication_transmit[i].transmission_type){
					/* Count */
					canopen->slave.pdo[i].sync_counter_value++;

					/* If we exceeded */
					if(canopen->slave.pdo[i].sync_counter_value == canopen->od_communication.PDO_communication_transmit[i].transmission_type)
						execute_transmission = true;

				}else{
					canopen->slave.pdo[i].sync_counter_value = 0;
				}
			}
		}else{
			/* Reset */
			canopen->slave.pdo[i].event_timer_counter = 0;
			canopen->slave.pdo[i].start_counting_sync = false;
			canopen->slave.pdo[i].sync_counter_value = 0;
			return; /* Only synchronous and event-driven transmission is supported */
		}


		/* Check if it's true to send the transmission */
		if(!execute_transmission)
			return; /* Nope */

		/* Transmit */
		uint16_t CAN_ID = canopen->od_communication.PDO_communication_transmit[i].COB_ID & 0x7FF;
		CANopen_PDO_Protocol_Produce_Data(canopen, CAN_ID, &canopen->od_communication.PDO_mapping_transmit[i]);
	}
}
