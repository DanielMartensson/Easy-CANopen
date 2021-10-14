/*
 * CAN_Network.h
 *
 *  Created on: 14 juli 2021
 *      Author: Daniel Mårtensson
 */

#ifndef HARDWARE_CAN_NETWORK_H_
#define HARDWARE_CAN_NETWORK_H_

/* C standard library */
#include <stdint.h>
#include <stdbool.h>

#include "../../CANopen/Global_Enums/Enum_Status_Codes.h"
/* Enums and processor choices */
#include "../Processor_Choice.h"

#ifdef __cplusplus
extern "C" {
#endif

STATUS_CODE CAN_Send_Message(uint32_t COB_ID, uint8_t data[]);
STATUS_CODE CAN_Send_Request(uint32_t COB_ID, uint8_t PGN[]);
bool CAN_Read_Message(uint32_t *ID, uint8_t data[]);

#ifdef __cplusplus
}
#endif

#endif /* HARDWARE_CAN_NETWORK_H_ */
