/*
 * CANopen_Producer_PDO_Transmit.c
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "PDO_Internal.h"

/* Layers */
#include "PDO_Protocol/PDO_Protocol.h"

void CANopen_Producer_PDO_Transmit_TPDO(CANopen *canopen) {
	/* Check if PDO service is enabled */
	if(canopen->slave.nmt.status_operational != STATUS_OPERATIONAL_OPERATIONAL)
		return; /* NMT is not in operational mode. PDO service is disabled */

	/* There are 4 transmit PDO channels */
	CANopen_PDO_Protocol_Produce_Data(canopen, &canopen->slave.pdo1, &canopen->od_communication.t_pdo1_mapping, &canopen->od_communication.t_pdo1_communication, FUNCTION_CODE_PDO1_RECEIVE);
	CANopen_PDO_Protocol_Produce_Data(canopen, &canopen->slave.pdo2, &canopen->od_communication.t_pdo2_mapping, &canopen->od_communication.t_pdo2_communication, FUNCTION_CODE_PDO2_RECEIVE);
	CANopen_PDO_Protocol_Produce_Data(canopen, &canopen->slave.pdo3, &canopen->od_communication.t_pdo3_mapping, &canopen->od_communication.t_pdo3_communication, FUNCTION_CODE_PDO3_RECEIVE);
	CANopen_PDO_Protocol_Produce_Data(canopen, &canopen->slave.pdo4, &canopen->od_communication.t_pdo4_mapping, &canopen->od_communication.t_pdo4_communication, FUNCTION_CODE_PDO4_RECEIVE);
}
