/*
 * lss.h
 *
 *  Created on: 8 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_LSS_LSS_H_
#define CANOPEN_LSS_LSS_H_

#include "../../Easy_CANopen/Structs.h"

/* Master transmit */
STATUS_CODE CANopen_Master_LSS_Transmit_Switch_Mode_Global_Protocol(uint8_t mode);
STATUS_CODE CANopen_Master_LSS_Transmit_Switch_Mode_Selective_Protocol(CANopen *canopen, uint8_t cs, uint32_t value);


/* Slave receive */
STATUS_CODE CANopen_Slave_LSS_Receive_Switch_Mode_Global_Protocol(CANopen *canopen, uint8_t data[]);

#endif /* CANOPEN_LSS_LSS_H_ */
