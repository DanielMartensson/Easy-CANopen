/*
 * Dictionary_Objects.c
 *
 *  Created on: 13 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "../OD/OD.h"

static bool iterative_binary_search(CANopen* canopen, uint32_t key, uint16_t* selected_index);

/* Create a new value inside the dictionary object */
void CANopen_OD_add_dictionary_object_index(CANopen* canopen, uint16_t index, uint8_t sub_index, OD_ACCESS access){
	/* Change index and set values */
	canopen->object_dictionaries[canopen->array_position].key = index << 16 | sub_index;
	canopen->object_dictionaries[canopen->array_position].access = access;
	canopen->object_dictionaries[canopen->array_position].value = 0;
	canopen->array_position++;
}

/* Get the dictionary object value */
OD_STATUS CANopen_OD_get_dictionary_object_value(CANopen* canopen, uint16_t index, uint8_t sub_index, uint32_t* value){
	/* Get selected index */
	uint16_t selected_index;
	if(!iterative_binary_search(canopen, index << 16 | sub_index, &selected_index))
		return OD_STATUS_BINARY_SEARCH_ERROR;

	/* Check if we have read access */
    if(canopen->object_dictionaries[selected_index].access & OD_ACCESS_READ){
        *value = canopen->object_dictionaries[selected_index].value;
        return OD_STATUS_OK; /* You got the value */
    }

    return OD_STATUS_NOT_PERMITTED; /* Wrong access */

}

/* Change dictionary object value */
OD_STATUS CANopen_OD_set_dictionary_object_value(CANopen* canopen, uint16_t index, uint8_t sub_index, uint32_t value){
	/* Get selected index */
	uint16_t selected_index;
	if(!iterative_binary_search(canopen, index << 16 | sub_index, &selected_index))
		return OD_STATUS_BINARY_SEARCH_ERROR;

	/* Check if we have write access */
    if(canopen->object_dictionaries->access & OD_ACCESS_WRITE){
    	canopen->object_dictionaries->value = value;
    	return OD_STATUS_OK; /* The value is set */
    }

    return OD_STATUS_NOT_PERMITTED; /* The value could not be set */
}

/* Change dictionary object value - Don't take account on the writing rights */
OD_STATUS CANopen_OD_set_force_dictionary_object_value(CANopen* canopen, uint16_t index, uint8_t sub_index, uint32_t value){
	/* Get selected index */
	uint16_t selected_index;
	if(!iterative_binary_search(canopen, index << 16 | sub_index, &selected_index))
		return OD_STATUS_BINARY_SEARCH_ERROR;

	/* Set the value */
    canopen->object_dictionaries[selected_index].value = value;
   	return OD_STATUS_OK; /* The value is set */
}

static bool iterative_binary_search(CANopen* canopen, uint32_t key, uint16_t* selected_index){
   /* Perform binary search */
   uint16_t start_index = 0;
   uint16_t end_index = canopen->array_position;
   while (start_index <= end_index){

      /* Find the middle index */
      *selected_index = start_index + (end_index - start_index ) / 2;

      /* Check if that's correct key value */
      if (canopen->object_dictionaries[*selected_index].key == key)
         return true;
      if (canopen->object_dictionaries->key < key)
         start_index = *selected_index + 1;
      else
         end_index = *selected_index - 1;
   }
   return false;
}
