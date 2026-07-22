/*
 * CO_TIME_conversion.c
 * 
 * This file provides the time conversion utilities function.
 * 
 *  Created on: 7 July. 2026
 *      Author: Ali Ünsal
 */

#include "Utilities/CANopen_TIME/co_time_conversion.h"
#include "Easy_CANopen/Easy_CANopen_Structs.h"
#include <stdbool.h>

/* Time validation parameters */
#define VALID_YEAR_YY   2026U  // Works after 2026 only if DeLorean's flux capacitor is active.
#define VALID_MONTH_MIN 1U
#define VALID_MONTH_MAX 12U
#define VALID_DAY_MIN   1U
#define VALID_DAY_MAX   31U
#define VALID_HOUR_MAX  23U
#define VALID_MIN_MAX   59U
#define VALID_SEC_MAX   59U

/* Time conversion coeffiecient  */
#define CF_HOUR_TO_MS   3600000UL
#define CF_MIN_TO_MS    60000UL
#define CF_SEC_TO_MS    1000UL

/* Time base */
#define REF_YEAR_CO_TIME    1984U   /**< Reference year of the CANOpen TimeObject */

static bool is_leap_year(uint16_t year)
{
    return ((year % 4U == 0U) && ((year % 100U != 0U) || (year % 400U == 0U)));
}

static uint8_t get_days(const uint16_t year, const uint8_t month)
{
    static const uint8_t DAYS_TABLE[] =
        { 0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U };

    uint8_t days = 0U;

    if ((month >= VALID_MONTH_MIN) && (month <= VALID_MONTH_MAX))
    {
        days = DAYS_TABLE[month];

        if ((month == 2U) && (is_leap_year(year)))
        {
            days = 29U;
        }
    }

    return days;
}

static bool dt_is_valid(const datetime_t * const dt)
{
    const bool year_is_ok   = (dt->year >= VALID_YEAR_YY);
    const bool month_is_ok  = (dt->month >= VALID_MONTH_MIN) && (dt->month <= VALID_MONTH_MIN);
    const bool day_is_ok    = (dt->day >= VALID_DAY_MIN) && (dt->day <= VALID_DAY_MAX);
    const bool hour_is_ok   = (dt->hour <= VALID_HOUR_MAX);
    const bool min_is_ok    = (dt->minute <= VALID_MIN_MAX);
    const bool sec_is_ok    = (dt->second <= VALID_SEC_MAX);

    return (year_is_ok && month_is_ok && day_is_ok && hour_is_ok && min_is_ok && sec_is_ok);
}

bool co_time_dt_to_cotime(const datetime_t * const dt, TIME * const co_to)
{
    bool success = false;   // Fail-safe initialisation

    if ((dt != NULL) && (co_to != NULL) && (dt_is_valid(dt)))
    {
        uint32_t total_days = 0U;
        uint16_t    y;
        uint8_t     m;

        co_to->milliseconds_since_midnight = ((uint32_t)dt->hour   * CF_HOUR_TO_MS) +
                                            ((uint32_t)dt->minute  * CF_MIN_TO_MS) +
                                            ((uint32_t)dt->second  * CF_SEC_TO_MS);

        /* Calculate total days since 1984 epoch year */
        for (y = REF_YEAR_CO_TIME; y < dt->year; y++)
        {
            total_days += (is_leap_year(y)) ? 366UL : 365UL;
        }

        for (m = VALID_MONTH_MIN; m < dt->month; m++)
        {
            total_days += (uint32_t) get_days(dt->year, m);
        }

        total_days += (uint32_t)dt->day - 1UL;

        co_to->days_since_1_janunary_1984 = (uint16_t) total_days;
        success = true;
    }

    return success; // Single exit point
}