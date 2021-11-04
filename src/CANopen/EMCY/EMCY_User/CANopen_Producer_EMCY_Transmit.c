/*
 * CANopen_Producer_EMCY_Transmit.c
 *
 *  Created on: 16 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "EMCY_User.h"

/* Layers */
#include "../../../Hardware/Hardware.h"
#include "../EMCY_Internal/EMCY_Internal.h"
#include "../EMCY_Internal/EMCY_Protocol/EMCY_Protocol.h"

void CANopen_Producer_EMCY_Transmit_Error(CANopen *canopen, uint16_t new_error_code, uint8_t new_error_register, uint8_t vendor_specific_data[]){
	/* Check if EMCY service is enabled */
	if(canopen->slave.nmt.status_operational == STATUS_OPERATIONAL_STOPPED)
		return; /* NMT is in the stopped mode. ECMY service is disabled */

	/* Send error */
	CANopen_EMCY_Protocol_Error_Transmit(canopen, new_error_code, new_error_register, vendor_specific_data);
}

/* This function is not available for the user if the user don't include the internal EMCY header */
void CANopen_Producer_EMCY_Transmit_Status(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_SYNC_EMCY << 7 | node_ID;

	/* Send the message to client */
	Hardware_CAN_Send_Message(COB_ID, data);
}
