/*
 * CANopen_Consumer_PDO_Receive.c
 *
 *  Created on: 7 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "PDO_Internal.h"

/* Layers */
#include "PDO_Protocol/PDO_Protocol.h"

void CANopen_Consumer_PDO_Receive_TPDO1(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	CANopen_PDO_Protocol_Consume_TPD1(canopen, node_ID, data);
}

void CANopen_Consumer_PDO_Receive_TPDO2(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	CANopen_PDO_Protocol_Consume_TPD2(canopen, node_ID, data);
}

void CANopen_Consumer_PDO_Receive_TPDO3(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	CANopen_PDO_Protocol_Consume_TPD3(canopen, node_ID, data);
}

void CANopen_Consumer_PDO_Receive_TPDO4(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	CANopen_PDO_Protocol_Consume_TPD4(canopen, node_ID, data);
}

void CANopen_Consumer_PDO_Receive_RPDO1(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	CANopen_PDO_Protocol_Consume_RPD1(canopen, node_ID, data);
}

void CANopen_Consumer_PDO_Receive_RPDO2(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	CANopen_PDO_Protocol_Consume_RPD2(canopen, node_ID, data);
}

void CANopen_Consumer_PDO_Receive_RPDO3(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	CANopen_PDO_Protocol_Consume_RPD3(canopen, node_ID, data);
}

void CANopen_Consumer_PDO_Receive_RPDO4(CANopen *canopen, uint8_t node_ID, uint8_t data[]){
	CANopen_PDO_Protocol_Consume_RPD4(canopen, node_ID, data);
}
