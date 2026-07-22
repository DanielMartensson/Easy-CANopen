/*
 * CO_TIME_conversion.h
 * 
 * This file provides the time conversion utilities function.
 * 
 *  Created on: 7 nov. 2021
 *      Author: Ali Ünsal
 */

#include <stdbool.h>
#include <stdint.h>
#include "Easy_CANopen/Easy_CANopen_Structs.h"

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} datetime_t;


/**
 * @brief This function converts the datetime to CANOpen TimeObject.
 * 
 * @param dt Datetime, source of the time to convert TO (TimeObject)
 * @param co_to Converted TimeObject.
 * @return true     Conversion is succesfull
 * @return false    Conversion is fail: 
 *                  NULL pointer or,
 *                  Invalid datetime
 * 
 * @see co_time_conversion.c for time validation metrics. 
 */
bool co_time_dt_to_cotime(const datetime_t * dt, TIME * co_to);