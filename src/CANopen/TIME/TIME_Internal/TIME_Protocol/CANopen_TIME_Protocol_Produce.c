/*
 * CANopen_TIME_Protocol_Produce.c
 *
 *  Created on: 6 nov. 2021
 *      Author: Daniel Mårtensson
 */

#include "TIME_Protocol.h"

/* Layers */
#include "../../../../Hardware/Hardware.h"

void CANopen_TIME_Protocol_Produce_Clock(CANopen *canopen){
	/* Get the real time clock */
	uint8_t date, month, hour, minute, second;
	uint16_t year;
	Hardware_Time_Get_RTC(&date, &month, &year, &hour, &minute, &second);

	/* Compute total milliseconds since clock 00:00 */
	uint32_t milliseconds_since_midnight = second*1000 + minute*60000 + hour*3600000;

	/* Start counting days that have pass since 1 January 1984 */
	uint16_t days_since_1_januari_1984 = 0;
	for(uint16_t y = 1984; y < year; y++)
		days_since_1_januari_1984 += (y % 4 == 0) || (y % 400 == 0) ? 366 : 365; /* Leap year, not leap year */
	for(uint8_t m = 1; m < month; m++)
		if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
			days_since_1_januari_1984 += 31;
		else if(m == 2)
			days_since_1_januari_1984 += 28; /* February */
		else
			days_since_1_januari_1984 += 30;
	days_since_1_januari_1984 += date - 1; /* Days since, does not includes this day */

	/* Set data */
	uint8_t data[8] = {0};
	data[0] = milliseconds_since_midnight;
	data[1] = milliseconds_since_midnight >> 8;
	data[2] = milliseconds_since_midnight >> 16;
	data[3] = milliseconds_since_midnight >> 24;
	data[4] = days_since_1_januari_1984;
	data[5] = days_since_1_januari_1984 >> 8;

	/* Create the COB ID */
	uint32_t COB_ID = FUNCTION_CODE_TIME << 7;	/* Only the master node send out this message */

	/* Send the message to client */
	Hardware_CAN_Send_Message(COB_ID, data);
}
