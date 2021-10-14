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
/* Create a new value inside the dictionary object */
void CANopen_OD_add_dictionary_object_index(CANopen* canopen, uint16_t index, uint8_t sub_index, OD_ACCESS access);
OD_STATUS CANopen_OD_get_dictionary_object_value(CANopen* canopen, uint16_t index, uint8_t sub_index, uint32_t* value);
OD_STATUS CANopen_OD_set_dictionary_object_value(CANopen* canopen, uint16_t index, uint8_t sub_index, uint32_t value);
OD_STATUS CANopen_OD_set_force_dictionary_object_value(CANopen* canopen, uint16_t index, uint8_t sub_index, uint32_t value);

#endif /* CANOPEN_OD_OD_H_ */
