/*
 * Hardware_CAN.c
 *
 *  Created on: 11 juli 2021
 *      Author: Daniel Mårtensson
 */


#include "Hardware.h"

/* This is a call back function e.g listener, that will be called once SAE J1939 data is going to be sent */
static void (*Callback_Function_Send)(uint32_t, uint8_t, uint8_t[]) = NULL;
static void (*Callback_Function_Read)(uint32_t*, uint8_t[], bool*) = NULL;
static void (*Callback_Function_Traffic)(uint32_t, uint8_t, uint8_t[], bool) = NULL;
static void (*Callback_Function_Delay_ms)(uint8_t) = NULL;

/* Platform independent library headers for CAN */
#if PROCESSOR_CHOICE == STM32
#include "main.h"
#elif PROCESSOR_CHOICE == ARDUINO
#elif PROCESSOR_CHOICE == PIC
#elif PROCESSOR_CHOICE == AVR
#elif PROCESSOR_CHOICE == QT_USB
#include "CAN_to_USB/can_to_usb.h"
#elif EASY_CAN_OPEN_TARGET_PLATFORM == INTERNAL_CALLBACK
/* Nothing here because else statement should not be running */
#else
#include <stdio.h>
/* Internal fields */
static bool internal_new_message[256] = {false};
static uint8_t internal_data[256*8] = {0};
static uint16_t internal_COB_ID[256] = {0};
static uint8_t buffer_index_transmit = 0;
static uint8_t buffer_index_receive = 0;

/* Internal functions */
static STATUS_CODE Internal_Transmit(uint16_t COB_ID, uint8_t data[], uint8_t DLC) {
	internal_COB_ID[buffer_index_transmit] = COB_ID;
	for (uint8_t i = 0; i < 8; i++) {
		internal_data[buffer_index_transmit * 8 + i] = data[i];
	}
	internal_new_message[buffer_index_transmit] = true;
	buffer_index_transmit++;									/* When this is 256, then it will be come 0 again */
	return STATUS_CODE_SUCCESSFUL;
}

static void Internal_Receive(uint16_t *COB_ID, uint8_t data[], bool *is_new_message) {
	/* Do a quick check if we are going to read message that have no data */
	if (internal_new_message[buffer_index_receive] == false) {
		*is_new_message = false;
		return;
	}
	*COB_ID = internal_COB_ID[buffer_index_receive];
	for (uint8_t i = 0; i < 8; i++) {
		data[i] = internal_data[buffer_index_receive * 8 + i];
	}
	*is_new_message = internal_new_message[buffer_index_receive];
	/* Reset */
	internal_new_message[buffer_index_receive] = false;
	buffer_index_receive++;										/* When this is 256, then it will be come 0 again */
}
#endif

STATUS_CODE Easy_CANopen_Hardware_CAN_Send_Message(uint16_t COB_ID, uint8_t data[]) {
	STATUS_CODE status;
#if PROCESSOR_CHOICE == STM32
	CAN_TxHeaderTypeDef TxHeader;
	TxHeader.DLC = 8;											/* Here we are sending 8 bytes */
	TxHeader.RTR = CAN_RTR_DATA;								/* Data frame */
	TxHeader.IDE = CAN_ID_EXT;									/* We want to send an extended ID */
	TxHeader.TransmitGlobalTime = DISABLE;
	TxHeader.ExtId = ID;
	TxHeader.StdId = 0x00; 										/* Not used */
	status = STM32_PLC_CAN_Transmit(data, &TxHeader);
#elif PROCESSOR_CHOICE == ARDUINO
	/* Implement your CAN send 8 bytes message function for the Arduino platform */
#elif PROCESSOR_CHOICE == PIC
	/* Implement your CAN send 8 bytes message function for the PIC platform */
#elif PROCESSOR_CHOICE == AVR
	/* Implement your CAN send 8 bytes message function for the AVR platform */
#elif PROCESSOR_CHOICE == QT_USB
    status = QT_USB_Transmit(ID, data, 8);
#elif EASY_CAN_OPEN_TARGET_PLATFORM == INTERNAL_CALLBACK
	/* Call our callback function */
	Callback_Function_Send(COB_ID, 8, data);
	status = STATUS_CODE_SUCCESSFUL;
#else
	/* If no processor are used, use internal feedback for debugging */
	status = Internal_Transmit(COB_ID, data, 8);
#endif

	/* Display traffic */
	if (Callback_Function_Traffic != NULL) {
		Callback_Function_Traffic(COB_ID, 8, data, true); /* ID, 8 bytes of data, data array, TX = true */
	}

	return status;
}

/* Read the current CAN-bus message. Returning false if the message has been read before, else true */
bool Easy_CANopen_Hardware_CAN_Read_Message(uint16_t *COB_ID, uint8_t data[]) {
	bool is_new_message;
	#if PROCESSOR_CHOICE == STM32
	STM32_PLC_CAN_Get_ID_Data(ID, data, &is_new_message);
#elif PROCESSOR_CHOICE == ARDUINO
	/* Implement your CAN function to get ID, data[] and the flag is_new_message here for the Arduino platform */
#elif PROCESSOR_CHOICE == PIC
	/* Implement your CAN function to get ID, data[] and the flag is_new_message here for the PIC platform */
#elif PROCESSOR_CHOICE == AVR
	/* Implement your CAN function to get ID, data[] and the flag is_new_message here for the AVR platform */
#elif PROCESSOR_CHOICE == QT_USB
    QT_USB_Get_ID_Data(ID, data, &is_new_message);
#elif EASY_CAN_OPEN_TARGET_PLATFORM == INTERNAL_CALLBACK
	Callback_Function_Read(COB_ID, data, &is_new_message);
#else
	/* If no processor are used, use internal feedback for debugging */
	Internal_Receive(COB_ID, data, &is_new_message);
#endif

	/* Display traffic */
	if (Callback_Function_Traffic != NULL && is_new_message) {
		Callback_Function_Traffic(*COB_ID, 8, data, false); /* ID, 8 bytes of data, data array, TX = false */
	}

	return is_new_message;
}

bool Easy_CANopen_CAN_Set_Baud_Rate(uint8_t table_index){
	bool is_set = false;
	#if PROCESSOR_CHOICE == STM32

#elif PROCESSOR_CHOICE == ARDUINO
	/* Implement your CAN function to get ID, data[] and the flag is_new_message here for the Arduino platform */
#elif PROCESSOR_CHOICE == PIC
	/* Implement your CAN function to get ID, data[] and the flag is_new_message here for the PIC platform */
#elif PROCESSOR_CHOICE == AVR
	/* Implement your CAN function to get ID, data[] and the flag is_new_message here for the AVR platform */
#elif PROCESSOR_CHOICE == QT_USB
    QT_USB_Get_ID_Data(ID, data, &is_new_message);
#else

#endif
	return is_set;
}

void Easy_CANopen_Hardware_Set_Callback_Functions(void (*Callback_Function_Send_)(uint32_t, uint8_t, uint8_t[]),
	void (*Callback_Function_Read_)(uint32_t*, uint8_t[], bool*),
	void (*Callback_Function_Traffic_)(uint32_t, uint8_t, uint8_t[], bool),
	void (*Callback_Function_Delay_ms_)(uint8_t)
) {
	Callback_Function_Send = Callback_Function_Send_;
	Callback_Function_Read = Callback_Function_Read_;
	Callback_Function_Traffic = Callback_Function_Traffic_;
	Callback_Function_Delay_ms = Callback_Function_Delay_ms_;
}

void Easy_CANopen_Hardware_Delay(uint8_t milliseconds) {
#if EASY_CAN_OPEN_TARGET_PLATFORM == STM32

#elif EASY_CAN_OPEN_TARGET_PLATFORM == ARDUINO

#elif EASY_CAN_OPEN_TARGET_PLATFORM == PIC

#elif EASY_CAN_OPEN_TARGET_PLATFORM == AVR

#elif EASY_CAN_OPEN_TARGET_PLATFORM == QT_USB

#elif EASY_CAN_OPEN_TARGET_PLATFORM == INTERNAL_CALLBACK
	Callback_Function_Delay_ms(milliseconds);
#else
	/* Nothing */
#endif
}