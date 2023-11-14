/*
 * UDS_Config.h
 *
 *  Created on: Oct 27, 2023
 *      Author: mina2
 */

#ifndef UDS_CONFIG_H_
#define UDS_CONFIG_H_


/********************************************************************/
/************************** configurations **************************/
/********************************************************************/

/* Max number of attempt from tester to send correct key */
#define SECUITY_MAX_NUM_OF_ATTEMPTS			5

/* Max Number SubFunction service provided by UDS */
#define SID_NUM			7
#define SF_NUM			10

/* Select if UDS used in BootLooder Application or not
 * Option : BOOTLOADER_APP
 * 			NORMAL_APP
 */

#define UDS_CURRENT_RUNNING_APP		NORMAL_APP

#endif /* UDS_CONFIG_H_ */
