/*
 * Hardware_CAN.c
 *
 *  Created on: 11 juli 2021
 *      Author: Daniel Mårtensson
 */


#include "Hardware.h"

/* Platform independent library headers for CAN */
#if PROCESSOR_CHOICE == STM32
#include "main.h"
#elif PROCESSOR_CHOICE == ARDUINO
#elif PROCESSOR_CHOICE == PIC
#elif PROCESSOR_CHOICE == AVR
#elif PROCESSOR_CHOICE == QT_USB
#include "CAN_to_USB/can_to_usb.h"
#else
#include <stdio.h>
#define ENABLE_INTERNAL_CAN_DEBUG 1
/* Internal fields */
static bool internal_new_message[256] = {false};
static uint8_t internal_data[256*8] = {0};
static uint16_t internal_COB_ID[256] = {0};
static uint8_t buffer_index_transmit = 0;
static uint8_t buffer_index_receive = 0;

/* Internal functions */
static STATUS_CODE Internal_Transmit(uint16_t COB_ID, uint8_t data[], uint8_t DLC) {
#if ENABLE_INTERNAL_CAN_DEBUG
	printf("->: %03x|    ", COB_ID);
#endif
	internal_COB_ID[buffer_index_transmit] = COB_ID;

	for (uint8_t i = 0; i < 8; i++) {
		internal_data[buffer_index_transmit * 8 + i] = data[i];
#if ENABLE_INTERNAL_CAN_DEBUG
		printf("%02x ", internal_data[buffer_index_transmit * 8 + i]);
#endif
	}
#if ENABLE_INTERNAL_CAN_DEBUG
	printf("\n");
#endif
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
#if ENABLE_INTERNAL_CAN_DEBUG
	printf("<-: %03x|    ", *COB_ID);
#endif
	for (uint8_t i = 0; i < 8; i++) {
		data[i] = internal_data[buffer_index_receive * 8 + i];
#if ENABLE_INTERNAL_CAN_DEBUG
		printf("%02x ", data[i]);
#endif
	}
#if ENABLE_INTERNAL_CAN_DEBUG
	printf("\n");
#endif
	*is_new_message = internal_new_message[buffer_index_receive];
	/* Reset */
	internal_new_message[buffer_index_receive] = false;
	buffer_index_receive++;										/* When this is 256, then it will be come 0 again */
}
#endif

STATUS_CODE Hardware_CAN_Send_Message(uint16_t COB_ID, uint8_t data[]) {
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
#else
	/* If no processor are used, use internal feedback for debugging */
	status = Internal_Transmit(COB_ID, data, 8);
#endif
	return status;
}

/* Read the current CAN-bus message. Returning false if the message has been read before, else true */
bool Hardware_CAN_Read_Message(uint16_t *COB_ID, uint8_t data[]) {
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
#else
	/* If no processor are used, use internal feedback for debugging */
	Internal_Receive(COB_ID, data, &is_new_message);
#endif
	return is_new_message;
}

bool CAN_Set_Baud_Rate(uint8_t table_index){
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
