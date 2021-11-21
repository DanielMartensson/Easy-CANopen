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

/* What type of bit length is your CAN message */
#define STANDARD 0
#define EXTENDED 1
#define CAN_ID_BITS_LENGTH STANDARD

/* Save files */
#define UINT8_T_ARRAY_NODE_ID_TABLE_INDEX "NODE_ID_TABLE_INDEX.TXT"

/* C standard library */
#include <stdint.h>
#include <stdbool.h>

/* Enums */
#include "../CANopen/Global_Enums/Enum_Status_Codes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Transmit & Receive */
STATUS_CODE Hardware_CAN_Send_Message(uint16_t COB_ID, uint8_t data[]);
bool Hardware_CAN_Read_Message(uint16_t *ID, uint8_t data[]);
bool CAN_Set_Baud_Rate(uint8_t table_index);

/* Save and load data */
bool Hardware_Memory_Save_Bytes(uint8_t data[], uint32_t data_length, char file_name[]);
bool Hardware_Memory_Load_Bytes(uint8_t data[], uint32_t data_length, char file_name[]);

/* Time functions */
uint32_t Hardware_Time_Get_Tick();
void Hardware_Time_Get_RTC(uint8_t *date, uint8_t *month, uint16_t *year, uint8_t *hour, uint8_t *minute, uint8_t *second);

#ifdef __cplusplus
}
#endif

#endif /* HARDWARE_HARDWARE_H_ */
