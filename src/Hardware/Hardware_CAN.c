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
/* Internal fields */
static bool internal_new_message[256] = {false};
static uint8_t internal_data[256*8] = {0};
static uint8_t internal_DLC[256] = {0};
static uint32_t internal_COB_ID[256] = {0};
static uint8_t buffer_index_transmit = 0;
static uint8_t buffer_index_receive = 0;

/* Internal functions */
static STATUS_CODE Internal_Transmit(uint32_t COB_ID, uint8_t data[], uint8_t DLC) {
	internal_COB_ID[buffer_index_transmit] = COB_ID;
	internal_DLC[buffer_index_transmit] = DLC;
	for(uint8_t i = 0; i < 8; i++)
		if(i < DLC)
			internal_data[buffer_index_transmit*8 + i] = data[i];
		else
			internal_data[buffer_index_transmit*8 + i] = 0x0;
	internal_new_message[buffer_index_transmit] = true;
	buffer_index_transmit++;									/* When this is 256, then it will be come 0 again */
	return STATUS_CODE_SUCCESSFUL;
}

static void Internal_Receive(uint32_t *COB_ID, uint8_t data[], bool *is_new_message) {
	/* Do a quick check if we are going to read message that have no data */
	if(internal_new_message[buffer_index_receive] == false){
		*is_new_message = false;
		return;
	}

	*COB_ID = internal_DLC[buffer_index_receive];
	for(uint8_t i = 0; i < 8; i++)
		if(i < internal_DLC[buffer_index_receive])
			data[i] = internal_data[buffer_index_receive*8 + i];
	*is_new_message = internal_new_message[buffer_index_receive];
	/* Reset */
	internal_new_message[buffer_index_receive] = false;
	internal_DLC[buffer_index_receive] = 0;
	buffer_index_receive++;										/* When this is 256, then it will be come 0 again */
}
#endif

STATUS_CODE Hardware_CAN_Send_Message(uint32_t COB_ID, uint8_t data[]) {
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

/* Send a PGN request
 * PGN: 0x00EA00 (59904)
 */
STATUS_CODE CAN_Send_Request(uint32_t ID, uint8_t PGN[]) {
	STATUS_CODE status;
#if PROCESSOR_CHOICE == STM32
	CAN_TxHeaderTypeDef TxHeader;
	TxHeader.DLC = 3;											/* Here we are only sending 3 bytes */
	TxHeader.RTR = CAN_RTR_DATA;								/* Data frame */
	TxHeader.IDE = CAN_ID_EXT;									/* We want to send an extended ID */
	TxHeader.TransmitGlobalTime = DISABLE;
	TxHeader.ExtId = ID;
	TxHeader.StdId = 0x00; 										/* Not used */
	status = STM32_PLC_CAN_Transmit(PGN, &TxHeader);
#elif PROCESSOR_CHOICE == ARDUINO
	/* Implement your CAN send 3 bytes message function for the Arduino platform */
#elif PROCESSOR_CHOICE == PIC
	/* Implement your CAN send 3 bytes message function for the PIC platform */
#elif PROCESSOR_CHOICE == AVR
	/* Implement your CAN send 3 bytes message function for the AVR platform */
#elif PROCESSOR_CHOICE == QT_USB
    status = QT_USB_Transmit(ID, PGN, 3);                       /* PGN is always 3 bytes */
#else
	/* If no processor are used, use internal feedback for debugging */
	status = Internal_Transmit(ID, PGN, 3);
#endif
	return status;
}

/* Read the current CAN-bus message. Returning false if the message has been read before, else true */
bool Hardware_CAN_Read_Message(uint32_t *COB_ID, uint8_t data[]) {
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
