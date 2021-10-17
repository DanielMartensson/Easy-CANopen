/*
 * Hardware.h
 *
 *  Created on: 17 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef HARDWARE_HARDWARE_H_
#define HARDWARE_HARDWARE_H_

/* Select your processor choice here */

#define	INTERNAL 0
#define	STM32 1
#define	ARDUINO 2
#define	PIC 3
#define	AVR 4
#define	QT_USB 5
#define PROCESSOR_CHOICE INTERNAL

/* C standard library */
#include <stdint.h>
#include <stdbool.h>

/* Enums */
#include "../CANopen/Global_Enums/Enum_Status_Codes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Transmit & Receive */
STATUS_CODE CAN_Send_Message(uint32_t COB_ID, uint8_t data[]);
STATUS_CODE CAN_Send_Request(uint32_t COB_ID, uint8_t PGN[]);
bool CAN_Read_Message(uint32_t *ID, uint8_t data[]);

/* Save and load data */
bool Save_Data_Bytes(uint8_t data[], uint32_t data_length, char file_name[]);
bool Load_Data_Bytes(uint8_t data[], uint32_t data_length, char file_name[]);

/* Time functions */
uint32_t Hardware_Get_Time_Tick();

#ifdef __cplusplus
}
#endif

#endif /* HARDWARE_HARDWARE_H_ */
