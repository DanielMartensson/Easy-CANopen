/*
 * Startup_Node.c
 *
 *  Created on: 6 okt. 2021
 *      Author: Daniel Mårtensson
 */

#include "Easy_CANopen.h"

/* Every time you startup your node, then this function must be run, or else, all settings will be zero */
bool Easy_CANopen_Startup_Node(CANopen *canopen){
	return 0;
}
