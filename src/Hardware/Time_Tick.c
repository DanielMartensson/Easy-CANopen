/*
 * Time_Tick.c
 *
 *  Created on: 15 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "Hardware.h"

uint32_t Hardware_Get_Time_Tick(){
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
