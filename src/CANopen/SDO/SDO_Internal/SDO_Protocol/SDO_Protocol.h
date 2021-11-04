/*
 * SDO_Protocol.h
 *
 *  Created on: 4 nov. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_SDO_SDO_INTERNAL_SDO_PROTOCOL_SDO_PROTOCOL_H_
#define CANOPEN_SDO_SDO_INTERNAL_SDO_PROTOCOL_SDO_PROTOCOL_H_

#include "../../../Easy_CANopen/Structs.h"

/* 7.2.4.3.3 to 7.2.4.3.7 in CiA 301 4.2.0 */
void CANopen_SDO_Protocol_Initiate_Response_Create(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);
uint8_t CANopen_SDO_Protocol_Segment_Response_Create(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);
void CANopen_SDO_Protocol_Initiate_Request_Create(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);
void CANopen_SDO_Protocol_Segment_Request_Create(CANopen *canopen, uint8_t cs_response, uint8_t node_ID, uint8_t data[]);

/* 7.2.4.3.17 in CiA 301 4.2.0 */
/* TODO: Fixa SDO abort-koder */


#endif /* CANOPEN_SDO_SDO_INTERNAL_SDO_PROTOCOL_SDO_PROTOCOL_H_ */
