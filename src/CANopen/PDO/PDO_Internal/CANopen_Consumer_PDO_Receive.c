/*
 * CANopen_Consumer_PDO_Receive.c
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "PDO_Internal.h"

/* Layers */
#include "PDO_Protocol/PDO_Protocol.h"

void CANopen_Consumer_PDO_Receive_TPDO(CANopen *canopen, struct PDO_mapping *rpdo_m, uint8_t data[]){
	CANopen_PDO_Protocol_Consume_Data(canopen, rpdo_m, data);
}

