/*
 * Hardware_Time.c
 *
 *  Created on: 15 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "Hardware.h"

uint32_t Hardware_Time_Get_Tick(){
#if PROCESSOR_CHOICE == STM32
	return HAL_GetTick();
#elif PROCESSOR_CHOICE == ARDUINO
	/* Implement your memory handler function for the Arduino platform */
#elif PROCESSOR_CHOICE == PIC
	/* Implement your memory handler function for the PIC platform */
#elif PROCESSOR_CHOICE == AVR
	/* Implement your memory handler function for the AVR platform */
#endif
	return 0;
}

void Hardware_Time_Get_RTC(uint8_t *date, uint8_t *month, uint16_t *year, uint8_t *hour, uint8_t *minute, uint8_t *second){
#if PROCESSOR_CHOICE == STM32
	return HAL_GetTick();
#elif PROCESSOR_CHOICE == ARDUINO
	/* Implement your memory handler function for the Arduino platform */
#elif PROCESSOR_CHOICE == PIC
	/* Implement your memory handler function for the PIC platform */
#elif PROCESSOR_CHOICE == AVR
	/* Implement your memory handler function for the AVR platform */
#endif
}
