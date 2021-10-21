/*
 * DO.h
 *
 *  Created on: 14 okt. 2021
 *      Author: Danie Mårtensson
 */

#ifndef CANOPEN_OD_OD_H_
#define CANOPEN_OD_OD_H_

#include "../../Easy_CANopen/Structs.h"

/* Handlers for dictionary objects */
OD_STATUS CANopen_OD_set_get_value(CANopen *canopen, uint16_t index, uint8_t sub_index, bool write_value, bool force_write, uint32_t *value);


#endif /* CANOPEN_OD_OD_H_ */
