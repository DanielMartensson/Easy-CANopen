/*
 * FLASH_EEPROM_RAM_Memory.h
 *
 *  Created on: 19 juli 2021
 *      Author: Daniel Mårtensson
 */

#ifndef HARDWARE_CAN_MEMORY_LAYER_CAN_MEMORY_LAYER_H_
#define HARDWARE_CAN_MEMORY_LAYER_CAN_MEMORY_LAYER_H_

/* C standard library */
#include <stdint.h>
#include <stdbool.h>

#include "../Processor_Choice.h"

#ifdef __cplusplus
extern "C" {
#endif

bool Save_Struct(uint8_t data[], uint32_t data_length, char file_name[]);
bool Load_Struct(uint8_t data[], uint32_t data_length, char file_name[]);

#ifdef __cplusplus
}
#endif

#endif /* HARDWARE_CAN_MEMORY_LAYER_CAN_MEMORY_LAYER_H_ */
