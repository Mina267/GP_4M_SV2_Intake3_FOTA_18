/*
 * UDS_Private.h
 *
 *  Created on: Oct 24, 2023
 *      Author: mina2
 */

#ifndef UDS_PRIVATE_H_
#define UDS_PRIVATE_H_


typedef void (* UDS_SeriveFunction)(void);
typedef void (*Function_t)(void);

#define NOT_IN_SESSION		((void*)0)




/********************************************************************/
/************************  Private Macros ***************************/
/********************************************************************/
#define UDS_SID								(0)
#define UDS_SF								(1)


/************************** Security Access *************************/
#define SECURITY_SEED_RES_FRAME_SIZE		(7)
#define SECURITY_START_OF_KEY				(2)
#define SECURITY_KEY_NOT_MATCH				(0)
#define SECURITY_KEY_MATCH					(1)


/************************** Routine Control *************************/
#define START_ROUTINE						(01)
#define ROUTINE_TYPE_1_						(2)
#define ROUTINE_TYPE_2_						(3)
#define ROUTINE_SECTOR_TO_ERASE				(4)
#define ROUTINE_BANK_TO_JMP					(4)
#define ROUTINE_MAX_NUM_OF_SECTORS			(6)
#define ROUTINE_SELECT_BANK1				(1)
#define ROUTINE_SELECT_BANK2				(0)

/************************ Request Download  *************************/
#define REQ_DOWNLOAD_ADDRESS_1_BTYE_		(4)
#define REQ_DOWNLOAD_ADDRESS_2_BTYE_		(3)
#define REQ_DOWNLOAD_ADDRESS_3_BTYE_		(2)
#define REQ_DOWNLOAD_ADDRESS_4_BTYE_		(1)

#define REQ_DOWNLOAD_SIZE_1_BTYE_			(4)
#define REQ_DOWNLOAD_SIZE_2_BTYE_			(3)
#define REQ_DOWNLOAD_SIZE_3_BTYE_			(2)
#define REQ_DOWNLOAD_SIZE_4_BTYE_			(1)

/************************* Negative response ************************/
#define NEGATIVE_RES_FRAME_SIZE				(0x03)


/***************** Initialization (start) of UDS ********************/

#define UDS_FLAG_SET				(1)
#define UDS_BANK1_ACTIVE			(1)
#define UDS_BANK2_ACTIVE			(2)
#define UDS_NO_VALID_BANK			(3)

#define START_OF_BANK_1				(0x08010000)
#define START_OF_BANK_2				(0x08020000)
#define RESET_HANDLER_ISR_BANK1		(0x08010004)
#define RESET_HANDLER_ISR_BANK2		(0x08020004)
#define MAX_BANK_SIZE				((u32)64000)

#define BOOTLOADER_APP				(0)
#define NORMAL_APP					(1)

#define PRE_EXTENDED_SESSION		(1)
#define PRE_DEFAULT_SESSION			(0)
#define UDS_NO_VALID_APP			(0)


/********************************************************************/
/************************  Private Enums ****************************/
/********************************************************************/

/* Negative Response NRC */
typedef enum
{
	GENERAL_REJECT = 0x10,
	SERVICE_NOT_SUPPORTED = 0x11,
	SF_NOT_SUPPORTED = 0x12,
	INVALID_MESSAGE_LENGTH_OR_FORMAT = 0x13,
	FAILURE_PREVENTS_EXECUTION_OF_REQUESTED_ACTION = 0x26,
	REQUEST_OUT_OF_RANGE = 0x31,
	SECURITY_ACCESS_DENIED = 0x33,
	INVALID_KEY = 0x35,
	EXCEEDED_NUMBER_OF_ATTEMPTS = 0x36,
	UPLOAD_DOWNLOAD_NOT_ACCEPTED = 0x70,
	PROGRAMMING_FAILURE = 0x72,
	SF_NOT_SUPPORTED_IN_ACTIVE_SESSION = 0x7E,
	SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION = 0x7F

}UDS_NRC_t;


/* SubFunctions of Session Control */
typedef enum
{
	DEFAULT_SESSION = 0x01,
	PROGRAMMING_SESSION = 0x02,
	EXTENDED_SESSION = 0x03

}UDS_ControlSession_t;

/* SubFunctions of Reset */
typedef enum
{
	HARD_RESET = 0x01,
	KEY_OFF_ON_RESET = 0x02,
	SOFT_RESET = 0x03,
}UDS_Reset_t;


/* DID of Routine control */
typedef enum
{
	ERASE_ROUTINE = 0xFF00,
	BANK_CHANGE_ROUTINE = 0x5500,
}UDS_DID_RoutineControl_t;

/* SubFunctions of Security Access */
typedef enum
{
	SECURITY_LVL_1_REQ_SEED = 0x01,
	SECURITY_LVL_1_SEND_KEY	= 0x02,
	SECURITY_LVL_2_REQ_SEED = 0x03,
	SECURITY_LVL_2_SEND_KEY	= 0x04,
	SECURITY_LVL_3_REQ_SEED = 0x05,
	SECURITY_LVL_3_SEND_KEY	= 0x06,

}UDS_SecurityAccess_t;

/* Status of Security Access */
typedef enum
{
	SECURITY_LOCKED,
	SECURITY_UNLOCKED
}UDS_Seecurity_status_t;


/* UDS SID Mapping */
typedef enum
{
	UDS_REQ_SESSION_CONTROL,
	UDS_REQ_RESET,
	UDS_REQ_SECURITY_ACCESS,
	UDS_REQ_ROUTINE_CONTROL,
	UDS_REQ_DOWNLOAD,
	UDS_REQ_TRANSFER_DATA,
	UDS_REQ_TRANSFEREXIT,
	UDS_REQ_NOT_SPURRTED,

}UDS_REQ_t;



typedef union
{
	u8 DataBuffer[2];
	u16 Data;
	struct
	{
		u32 ValidityMarker : 1;
		u32 ActiveBank : 2;
		u32 ReprogrammingMarker: 1;
		u32 PreSession: 1;
		u32 SoftResetRequest : 1;
		u32 RESERVED1 : 1;
		u32 RESERVED2 : 1;
		u8 RESERVED_byte2;
	};
}UDS_Data_t;


/********************************************************************/
/**********************  Private Functions **************************/
/********************************************************************/

/* Send To tester Negative response */
static void SendNegativeResponse(u8 Copy_u8SID, UDS_NRC_t Copy_enuNRC);
/* Send To tester Positive response */
static void SendPostiveResponse(u8 *Copy_pu8Frame ,u8 Copy_u8Size);
/* Generate response frame when tester request seed for security level 1 */
static void GenerateSeedReponseLVL1(void);
/* Compare tester send key With Local Generated key */
static u8 CompareSecurityLVL1Key(u8 *Local_pu8TesterKey);
/* Provides SubFunction operation of Session Control */
static void SID_SessionControl(void);
/* Provides SubFunction operation of Security Access */
static void SID_SecurityAccess(void);
/* Provides SubFunction operation of Reset */
static void SID_Reset(void);
/* Provides Routine operation of Routine Control */
static void SID_RoutineControl(void);
/* Provides SubFunction operation of Request Download */
static void SID_RequestDownload(void);
/* Provides SubFunction operation of Transfer Data */
static void SID_TransferData(void);
/* Provides SubFunction operation of Request TransferExit  */
static void SID_RequestTransferExit (void);
/* Check if Reset is requested programming session
 * Check if reset is only requested soft reset
 * If there is reprogramming request and MCU in Default or extended session Jump to application
 * This function Will Call in BootLoader Application Only */
static void UDS_StartConfiguration(void);
/* DeInitialization of System */
static void System_DeInit(void);
/* Switch active Bank */
static void ValidNewBank(void);
/* Invalid bank that erased */
static void ValidBankAfterErase(u8 Local_u8Sector);






#endif /* UDS_PRIVATE_H_ */
