/*
 * SDO_Protocol.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_SDO_SDO_INTERNAL_SDO_PROTOCOL_SDO_PROTOCOL_H_
#define CANOPEN_SDO_SDO_INTERNAL_SDO_PROTOCOL_SDO_PROTOCOL_H_

#include "../../../../Easy_CANopen/Easy_CANopen_Structs.h"

/* 7.2.4.3.3 to 7.2.4.3.7 in CiA 301 4.2.0 */
void CANopen_SDO_Protocol_Transmit_Request_Initiate(CANopen *canopen, uint8_t cs, uint8_t node_ID, uint16_t index, uint8_t sub_index, uint32_t value);
void CANopen_SDO_Protocol_Transmit_Request_Segment(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);
void CANopen_SDO_Protocol_Receive_Response_Initiate(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);
void CANopen_SDO_Protocol_Receive_Request_Segment(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);
void CANopen_SDO_Protocol_Transmit_Response_Initiate(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);
void CANopen_SDO_Protocol_Transmit_Response_Segment(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);
void CANopen_SDO_Protocol_Receive_Request_Initiate(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);
void CANopen_SDO_Protocol_Receive_Response_Segment(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);

/* 7.2.4.3.17 in CiA 301 4.2.0 */
/* TODO: Fixa SDO abort-koder */


#endif /* CANOPEN_SDO_SDO_INTERNAL_SDO_PROTOCOL_SDO_PROTOCOL_H_ */
