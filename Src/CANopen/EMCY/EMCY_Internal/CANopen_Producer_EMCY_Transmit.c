/*
 * CANopen_Producer_EMCY_Transmit.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY_Internal.h"

/* Layers */
#include "../../../Hardware/Hardware.h"
#include "EMCY_Protocol/EMCY_Protocol.h"

void CANopen_Producer_EMCY_Transmit_Error(CANopen *canopen, uint16_t new_error_code, uint8_t new_error_register, uint8_t vendor_specific_data[]){
	/* Check if EMCY service is enabled */
	if(canopen->slave.nmt.this_node_status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. ECMY service is disabled */

	/* Check if EMCY is valid */
	uint8_t valid = canopen->od_communication.COB_ID_emcy >> 31;
	if(valid == 1)
		return; /* Does not exist */

	/* Create error */
	CANopen_EMCY_Protocol_Produce_Error(canopen, new_error_code, new_error_register, vendor_specific_data);
}
