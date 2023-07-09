/*
 * Enum_Command_Specifier_Codes.h
 *
 *  Created on: 9 okt. 2021
 *      Author: Daniel Mårtensson
 */

#ifndef CANOPEN_ENUMS_ENUM_CS_CODES_H_
#define CANOPEN_ENUMS_ENUM_CS_CODES_H_

enum {
	/* Client request bytes from server */
	CS_SDO_INITIATE_UPLOAD_REQUEST = 0x2,											/* Client request server for bytes */
	CS_SDO_INITIATE_UPLOAD_RESPONSE = 0x2,											/* Server response client with bytes or byte length */
	CS_SDO_SEGMENT_UPLOAD_REQUEST = 0x3,											/* Client request server for segment bytes */
	CS_SDO_SEGMENT_UPLOAD_RESPONSE = 0x0,											/* Server response client with segment bytes */

	/* Client transmit bytes to server */
	CS_SDO_INITIATE_DOWNLOAD_REQUEST = 0x1,											/* Client transmit server with bytes or byte length */
	CS_SDO_INITIATE_DOWNLOAD_RESPONSE = 0x3,										/* Server response client with an OK or request for segment bytes */
	CS_SDO_SEGMENT_DOWNLOAD_REQUEST = 0x0,											/* Client transmit server with segment bytes */
	CS_SDO_SEGMENT_DOWNLOAD_RESPONSE = 0x1,											/* Server request client for segment bytes */

	/*Abort SDO Transfer (Client or Server)*/
	CS_SDO_ABORT_SDO_TRANSFER = 0x4,

	/* NMT commands */
	CS_NMT_SERVICE_START_REMOTE_NODE = 0x1,
	CS_NMT_SERVICE_STOP_REMOTE_NODE = 0x2,
	CS_NMT_SERVICE_ENTER_PRE_OPERATIONAL = 0x80,
	CS_NMT_SERVICE_RESET_NODE = 0x81,
	CS_NMT_SERVICE_RESET_COMMUNICATION = 0x82,

	/* Enable or disable the LSS service */
	CS_LSS_SWITCH_MODE_GLOBAL = 0x4,

	/* Set the identification values */
	CS_LSS_SWITCH_MODE_SELECTIVE_VENDOR_ID = 0x40,
	CS_LSS_SWITCH_MODE_SELECTIVE_PRODUCT_CODE = 0x41,
	CS_LSS_SWITCH_MODE_SELECTIVE_REVISION_NUMBER = 0x42,
	CS_LSS_SWITCH_MODE_SELECTIVE_SERIAL_NUMBER = 0x43,
	CS_LSS_SWITCH_MODE_SELECTIVE_RESPONSE = 0x44,

	/* Let the node itself find identify it self */
	CS_LSS_IDENTIFY_REMOTE_SLAVE_VENDOR_ID = 0x46,
	CS_LSS_IDENTIFY_REMOTE_SLAVE_PRODUCT_CODE = 0x47,
	CS_LSS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_LOW = 0x48,
	CS_LSS_IDENTIFY_REMOTE_SLAVE_REVISION_NUMBER_HIGH = 0x49,
	CS_LSS_IDENTIFY_REMOTE_SLAVE_SERIAL_NUMBER_LOW = 0x4A,
	CS_LSS_IDENTIFY_REMOTE_SLAVE_SERIAL_NUMBER_HIGH = 0x4B,
	CS_LSS_IDENTIFY_REMOTE_SLAVE_CONFIGURED_RESPONSE = 0x4F,

	/* Check if there are nodes on the error address */
	CS_LSS_IDENTIFY_REMOTE_SLAVE_NON_CONFIGURED = 0x4C,
	CS_LSS_IDENTIFY_REMOTE_SLAVE_NON_CONFIGURED_RESPONSE = 0x50,

	/* Set the node address */
	CS_LSS_CONFIGURE_NODE_ID = 0x11,

	/* Baud rate */
	CS_LSS_CONFIGURE_BIT_TIMING_PARAMETERS = 0x13,
	CS_LSS_ACTIVATE_BIT_TIMING_PARAMETERS = 0x15,

	/* Store the identification values */
	CS_LSS_STORE_CONFIGURATION_PROTOCOL = 0x17,

	/* Ask for a identification value */
	CS_LSS_INQUIRE_IDENTITY_VENDOR_ID = 0x5A,
	CS_LSS_INQUIRE_IDENTITY_PRODUCT_CODE = 0x5B,
	CS_LSS_INQUIRE_IDENTITY_REVISION_NUMBER = 0x5C,
	CS_LSS_INQUIRE_IDENTITY_SERIAL_NUMBER = 0x5D,
	CS_LSS_INQUIRE_IDENTITY_NODE_ID = 0x5F
};

#endif /* CANOPEN_ENUMS_ENUM_CS_CODES_H_ */
