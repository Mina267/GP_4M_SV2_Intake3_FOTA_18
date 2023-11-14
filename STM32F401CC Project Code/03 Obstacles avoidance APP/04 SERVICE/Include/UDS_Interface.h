/*
 * UDS_Interface.h
 *
 *  Created on: Oct 24, 2023
 *      Author: mina2
 */

#ifndef UDS_INTERFACE_H_
#define UDS_INTERFACE_H_

/* @Note Data transfer from Most significant byte to least significant bit
 *
 */



/* UDS Serive's SID */
#define SID_SESSION_CONTROL					0x10
#define SID_RESET							0x11
#define SID_SECURITYACCESS					0x27
#define SID_ROUTINECONTROL					0x31
#define SID_REQUESTDOWNLOAD					0x34
#define SID_TRANSFER_DATA					0x36
#define SID_REQUEST_TRANSFEREXIT			0x37



/* Initialization of UDS Service Application */
void UDS_voidInit(void);
/* Runnable of UDS Service Application
 * Run in While one or as RTOS task
 */
void UDS_voidRunnable(void);




#endif /* UDS_INTERFACE_H_ */
