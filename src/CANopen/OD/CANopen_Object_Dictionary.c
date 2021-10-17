/*
 * Dictionary_Objects.c
 *
 *  Created on: 13 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "../OD/OD.h"

static struct Object_dictionary* iterative_binary_search(CANopen* canopen, uint32_t key);

/* Create a new value inside the dictionary object */
void CANopen_OD_add_dictionary_object_index(CANopen* canopen, uint16_t index, uint8_t sub_index, OD_ACCESS access){
	/* Realloc memory for a new dictionary object */
	canopen->length_object_dictionaries++;
	canopen->object_dictionaries = (struct Object_dictionary*)realloc(canopen->object_dictionaries, canopen->length_object_dictionaries * sizeof(struct Object_dictionary));

	/* Change index and set values */
	canopen->object_dictionaries += canopen->length_object_dictionaries - 1;
	canopen->object_dictionaries->key = index << 16 | sub_index;
	canopen->object_dictionaries->access = access;
	canopen->object_dictionaries->value = 0;
}

/* Get the dictionary object value */
OD_STATUS CANopen_OD_get_dictionary_object_value(CANopen* canopen, uint16_t index, uint8_t sub_index, uint32_t* value){
	/* Get selected one */
	canopen->object_dictionaries = iterative_binary_search(canopen, index << 16 | sub_index);

	/* Error */
	if(canopen->object_dictionaries == NULL)
	    return OD_STATUS_BINARY_SEARCH_ERROR; /* Binary search error */

	/* Check if we have read access */
    if(canopen->object_dictionaries->access & OD_ACCESS_READ){
        *value = canopen->object_dictionaries->value;
        return OD_STATUS_OK; /* You got the value */
    }

    return OD_STATUS_NOT_PERMITTED; /* Wrong access */

}

/* Change dictionary object value */
OD_STATUS CANopen_OD_set_dictionary_object_value(CANopen* canopen, uint16_t index, uint8_t sub_index, uint32_t value){
    /* Get selected */
	canopen->object_dictionaries = iterative_binary_search(canopen, index << 16 | sub_index);

	/* Error */
	if(canopen->object_dictionaries == NULL)
	    return OD_STATUS_BINARY_SEARCH_ERROR; /* Binary search error */

	/* Check if we have write access */
    if(canopen->object_dictionaries->access & OD_ACCESS_WRITE){
    	canopen->object_dictionaries->value = value;
    	return OD_STATUS_OK; /* The value is set */
    }

    return OD_STATUS_NOT_PERMITTED; /* The value could not be set */
}

/* Change dictionary object value - Don't take account on the writing rights */
OD_STATUS CANopen_OD_set_force_dictionary_object_value(CANopen* canopen, uint16_t index, uint8_t sub_index, uint32_t value){
    /* Get selected */
	canopen->object_dictionaries = iterative_binary_search(canopen, index << 16 | sub_index);

	/* Error */
	if(canopen->object_dictionaries == NULL)
	    return OD_STATUS_BINARY_SEARCH_ERROR; /* Binary search error */

	/* Set the value */
    canopen->object_dictionaries->value = value;
   	return OD_STATUS_OK; /* The value is set */
}

static struct Object_dictionary* iterative_binary_search(CANopen* canopen, uint32_t key){
   /* Important to remember the pointer beginning */
   struct Object_dictionary* beginning = canopen->object_dictionaries;

   /* Perform binary search */
   uint16_t start_index = 0;
   uint16_t end_index = canopen->length_object_dictionaries - 1;
   while (start_index <= end_index){
       /* Go to beginning */
	   canopen->object_dictionaries = beginning;

      /* Find the middle index */
      uint16_t middle = start_index + (end_index - start_index ) / 2;

      /* Set the index by moving the pointer address */
      canopen->object_dictionaries += middle;

      /* Check if that's correct key value */
      if (canopen->object_dictionaries->key == key)
         return canopen->object_dictionaries;
      if (canopen->object_dictionaries->key < key)
         start_index = middle + 1;
      else
         end_index = middle - 1;
   }
   return NULL;
}
