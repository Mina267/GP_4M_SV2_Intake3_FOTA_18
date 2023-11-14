/*
 * UDS.c
 *
 *  Created on: Oct 23, 2023
 *      Author: mina2
 */
/* Library's */
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

/* MCAL */
#include "../include/MRCC_interface.h"
#include "../include/MGPIO_interface.h"     	/* For debugging */
#include "../include/MSYSTICK_Interface.h"		/* For debugging */
#include "../include/MNVIC_Interface.h"
#include "../include/MFDI_Interface.h"
#include "../include/FEE_Interface.h"

/* Services */
#include "../include/BCM.h"

/* UDS Files */
#include "../include/UDS_Interface.h"
#include "../include/UDS_Private.h"
#include "../include/UDS_Config.h"

/* Frame received from Tester */
static u8 Receive_Frame[255];
/* Data Length of frame received */
static u8 Req_Len;
/* Request frame received from Tester */
static u8 *Req_Frame;
/* Service ID of current frame received */
static u8 ServiceID;
/* Service Sub Function of current frame received */
static u8 Service_SF;

static u32 GeneratedKey;

/* Session that now operating in diagnostic */
UDS_ControlSession_t CurrentSession = DEFAULT_SESSION;

/* Security level one status indicate if it locked or unlocked */
UDS_Seecurity_status_t SecurityLVLOneStatus = SECURITY_LOCKED;

/* Count number of attempt of Security access send key */
static u8 Security_SendKeyAttemptsCnt = 0;
/* Indicate if UDs send seed and expected flag or not */
static bool_t Security_RequestSeed_Flag = FALSE;

/* Position of Flashing Address */
static u32 DownLoad_AddressPosition;
/* Starting address requested to download */
static u32 StartAddress;

/* Event Synchronization between Request download and Transfer Data */
static bool_t RequestDownload_Flag = FALSE;



/* Data (flags) save in Flash */
static UDS_Data_t UDS_Data;

UDS_SeriveFunction UDS_Array[3][SID_NUM] =
{
	/* Default */		{
							SID_SessionControl,   		/* Session control          */
							NOT_IN_SESSION, 	   		/* Reset                    */
							NOT_IN_SESSION, 	   		/* Security Access          */
							NOT_IN_SESSION,	       		/* Routine Control          */
							NOT_IN_SESSION,		   		/* Request Download         */
							NOT_IN_SESSION,		   		/* Transfer Data    		*/
							NOT_IN_SESSION,		   		/* Request TransferExit    	*/
						},
	/* Programming*/	{
							SID_SessionControl,     	/* Session control         	*/
							SID_Reset,              	/* Reset                   	*/
							SID_SecurityAccess,     	/* Security Access         	*/
							SID_RoutineControl,     	/* Routine Control         	*/
							SID_RequestDownload,    	/* Request Download        	*/
							SID_TransferData,       	/* Transfer Data           	*/
							SID_RequestTransferExit,    /* Request TransferExit    	*/
						},
	/*Extended*/		{
							SID_SessionControl,     	/* Session control          */
							SID_Reset,              	/* Reset                    */
							NOT_IN_SESSION,         	/* Security Access          */
							NOT_IN_SESSION,         	/* Routine Control          */
							NOT_IN_SESSION,         	/* Request Download         */
							NOT_IN_SESSION,         	/* Transfer Data            */
							NOT_IN_SESSION,         	/* Request TransferExit     */
						},
};


static Function_t addr_to_call = 0;



void UDS_voidInit(void)
{
	/* Initialization */

	/* Initialization of Receiving requests */
	BCM_FrameReceive_Init();
	/* Initialization of Send response */
	BCM_SendFrmaeInit();

	/* Get UDS Data From FEE */
	UDS_Data.Data = FEE_u16GetData();


	UDS_StartConfiguration();


}

UDS_REQ_t Local_enuReqType = UDS_REQ_NOT_SPURRTED;

void UDS_voidRunnable(void)
{
	/**`*********************** Function Local Variables *********************************/

	UDS_SeriveFunction ServiceFunction = NOT_IN_SESSION;
	/* @note Diagnostic Frame receive from UART  */
	UART_Rec_status_t Local_enuRec = BCM_FrameReceive_GetterFrameAshync((u8*)Receive_Frame);

	/* Sending responses */
	BCM_SendFrameRunnable();

	if (Local_enuRec == FRAME_RECEIVED)
	{
		/* Length of Receiving tester frame */
		Req_Len = Receive_Frame[0];
		/* Receiving tester frame */
		Req_Frame = &Receive_Frame[1] ;
		/* Service ID of Request received */
		ServiceID = Req_Frame[UDS_SID];
		/* Service ID of Request received */
		Service_SF = Req_Frame[UDS_SF];



		/***************************** Session control ***************************************/
		if (SID_SESSION_CONTROL == ServiceID)
		{
			Local_enuReqType = UDS_REQ_SESSION_CONTROL;
		}
		/******************************** SID Reset ******************************************/
		else if (SID_RESET == ServiceID)
		{
			Local_enuReqType = UDS_REQ_RESET;
		}
		/******************************** Security Access ************************************/
		else if (SID_SECURITYACCESS == ServiceID)
		{
			Local_enuReqType = UDS_REQ_SECURITY_ACCESS;
		}
		/****************************** Routine control  *************************************/
		else if (SID_ROUTINECONTROL  == ServiceID)
		{
			Local_enuReqType = UDS_REQ_ROUTINE_CONTROL;
		}

		/******************************** Request download ***********************************/
		else if (SID_REQUESTDOWNLOAD == ServiceID)
		{
			Local_enuReqType = UDS_REQ_DOWNLOAD;
		}
		/******************************** Data Transfer **************************************/
		else if (SID_TRANSFER_DATA == ServiceID)
		{
			Local_enuReqType = UDS_REQ_TRANSFER_DATA;
		}
		/**************************** Request TransferExit ***********************************/
		else if (SID_REQUEST_TRANSFEREXIT == ServiceID)
		{
			Local_enuReqType = UDS_REQ_TRANSFEREXIT;
		}

		if (Local_enuReqType != UDS_REQ_NOT_SPURRTED)
		{
			ServiceFunction = UDS_Array[CurrentSession - 1][Local_enuReqType];
			if (0 != ServiceFunction)
			{
				ServiceFunction();
			}
			else
			{
				/* Send To tester Negative response */
				SendNegativeResponse(SID_SESSION_CONTROL, SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION);
			}
		}
		else
		{
			/* Send To tester Negative response */
			SendNegativeResponse(SID_SESSION_CONTROL, SERVICE_NOT_SUPPORTED);
		}
	}
}



/* Check if Reset is requested programming session
 * Check if reset is only requested soft reset
 * If there is reprogramming request and MCU in Default or extended session Jump to application
 * This function Will Call in BootLoader Application Only */
static void UDS_StartConfiguration(void)
{
#if (UDS_CURRENT_RUNNING_APP == BOOTLOADER_APP)
	/* Check if Reset is requested programming session */
	if ((UDS_NO_VALID_APP == UDS_Data.ValidityMarker))
	{
		/* Convert UDS session to Programming Session */
		CurrentSession = PROGRAMMING_SESSION;
		MGPIO_SetPinValue(PORTB, PIN0, HIGH);
	}
	else if ((UDS_FLAG_SET == UDS_Data.SoftResetRequest) && (UDS_FLAG_SET == UDS_Data.ReprogrammingMarker))
	{
		/* Set soft reset marker */
		UDS_Data.SoftResetRequest = 0;
		/* Set soft Reprogramming Marker */
		UDS_Data.ReprogrammingMarker = 0;
		/* Write Data to FEE */
		FEE_voidSetData(UDS_Data.Data);

		/* Convert UDS session to Programming Session */
		CurrentSession = PROGRAMMING_SESSION;

		/* Send To tester Positive response */
		u8 Postive_Frame[2] = {0x10, 0x02};
		SendPostiveResponse(Postive_Frame, 2);


	}
	/* If there is reprogramming request and MCU in Default or extended session Jump to application */
	if ((UDS_FLAG_SET == UDS_Data.ValidityMarker) && (CurrentSession != PROGRAMMING_SESSION))
	{
		/* Decide which Application active now to jump for */
		if(UDS_BANK1_ACTIVE == UDS_Data.ActiveBank)
		{
			/* Reallocate of vector table */
			MNVIC_SetVectorTable(START_OF_BANK_1);
			/* Jump to application */
			addr_to_call = *(Function_t*)(RESET_HANDLER_ISR_BANK1);
			addr_to_call();
		}
		else if (UDS_BANK2_ACTIVE == UDS_Data.ActiveBank)
		{
			/* Reallocate of vector table */
			MNVIC_SetVectorTable(START_OF_BANK_2);
			/* Jump to application */
			addr_to_call = *(Function_t*)(RESET_HANDLER_ISR_BANK2);
			addr_to_call();
		}
	}
#elif (UDS_CURRENT_RUNNING_APP == NORMAL_APP)

	if ((UDS_FLAG_SET == UDS_Data.SoftResetRequest) && (PRE_DEFAULT_SESSION == UDS_Data.PreSession))
	{
		/* Set soft reset marker */
		UDS_Data.SoftResetRequest = 0;
		/* Write Data to FEE */
		FEE_voidSetData(UDS_Data.Data);

		/* Send To tester Positive response */
		u8 Postive_Frame[2] = {0x10, 0x01};
		SendPostiveResponse(Postive_Frame, 2);

	}
	else if ((UDS_FLAG_SET == UDS_Data.SoftResetRequest) && (PRE_EXTENDED_SESSION == UDS_Data.PreSession))
	{
		/* Set soft reset marker */
		UDS_Data.SoftResetRequest = 0;
		/* Write Data to FEE */
		FEE_voidSetData(UDS_Data.Data);

		/* Send To tester Positive response */
		u8 Postive_Frame[2] = {0x10, 0x03};
		SendPostiveResponse(Postive_Frame, 2);

	}
	/* Check if reset is only requested soft reset */
	else if (UDS_FLAG_SET == UDS_Data.SoftResetRequest)
	{
		/* Set soft reset marker */
		UDS_Data.SoftResetRequest = 0;
		/* Write Data to FEE */
		FEE_voidSetData(UDS_Data.Data);

		/* Send To tester Positive response */
		u8 Postive_Frame[2] = {0x11, 0x03};
		SendPostiveResponse(Postive_Frame, 2);

	}
#endif

}



static void SID_SessionControl(void)
{

	/*************************************************************************************/
	/******************************** Session Control ************************************/
	/*************************************************************************************/
	if (SID_SESSION_CONTROL == ServiceID)
	{
		/* Check for requested session */
		if (CurrentSession == Req_Frame[UDS_SF])
		{
			SendNegativeResponse(SID_SESSION_CONTROL, GENERAL_REJECT);
		}
		else if (DEFAULT_SESSION == Req_Frame[UDS_SF])
		{
			if (PROGRAMMING_SESSION == CurrentSession)
			{
				/* Set soft reset marker */
				UDS_Data.SoftResetRequest = 1;
				/* Mark Which Session requested from programming Session */
				UDS_Data.PreSession = PRE_DEFAULT_SESSION;

				/* Write Data to FEE */
				FEE_voidSetData(UDS_Data.Data);

				/* DeInitialization of System */
				System_DeInit();
				/* Soft reset of ECU */
				MNVIC_SystemReset();

			}
			else
			{
				/* Convert UDS session to Default Session */
				CurrentSession = DEFAULT_SESSION;
				/* Locked security level during session transaction */
				SecurityLVLOneStatus = SECURITY_LOCKED;
				/* Send To tester Positive response */
				SendPostiveResponse(Req_Frame, 2);
			}
		}
		else if (PROGRAMMING_SESSION == Req_Frame[UDS_SF])
		{
			/* Programming session can access only from
			 * Extended session cannot access from
			 * default session
			 */
			if (EXTENDED_SESSION == CurrentSession)
			{
				/* Set soft reset marker */
				UDS_Data.SoftResetRequest = 1;
				/* Set soft Reprogramming Marker */
				UDS_Data.ReprogrammingMarker = 1;
				/* Write Data to FEE */
				FEE_voidSetData(UDS_Data.Data);
				/* DeInitialization of System */
				System_DeInit();
				/* Soft reset of ECU */
				MNVIC_SystemReset();
			}
			else
			{
				/* Send To tester Negative response */
				SendNegativeResponse(SID_SESSION_CONTROL, SF_NOT_SUPPORTED_IN_ACTIVE_SESSION);
			}

		}


		else if (EXTENDED_SESSION == Req_Frame[UDS_SF])
		{

			if (PROGRAMMING_SESSION == CurrentSession)
			{
				/* Set soft reset marker */
				UDS_Data.SoftResetRequest = 1;
				/* Mark Which Session requested from programming Session */
				UDS_Data.PreSession = PRE_EXTENDED_SESSION;

				/* Write Data to FEE */
				FEE_voidSetData(UDS_Data.Data);

				/* DeInitialization of System */
				System_DeInit();
				/* Soft reset of ECU */
				MNVIC_SystemReset();

			}
			else
			{
				/* Convert UDS session to Extended Session */
				CurrentSession = EXTENDED_SESSION;
				/* Locked security level during session transaction */
				SecurityLVLOneStatus = SECURITY_LOCKED;
				/* Send To tester Positive response */
				SendPostiveResponse(Req_Frame, 2);
			}

		}
		else
		{
			/* Send To tester Negative response */
			SendNegativeResponse(SID_SESSION_CONTROL, SF_NOT_SUPPORTED);
		}
	}
}


/*************************************************************************************/
/***************************** Routine control ***************************************/
/*************************************************************************************/
static void SID_RoutineControl(void)
{
	/************************* Function Local Variables *********************************/
	u16 Local_u16Routine_type;
	u8 Local_u8Sector;
	u8 Local_u8Bank;

	/* Check for requested session */
	if (START_ROUTINE == Req_Frame[UDS_SF])
	{

		/* Check for sub routine */
		Local_u16Routine_type = (u16)((((u32)Req_Frame[ROUTINE_TYPE_1_]) << 8) | Req_Frame[ROUTINE_TYPE_2_]);

		if (SecurityLVLOneStatus == SECURITY_UNLOCKED)
		{
			if (ERASE_ROUTINE == Local_u16Routine_type)
			{
				Local_u8Sector = Req_Frame[ROUTINE_SECTOR_TO_ERASE];
				if (ROUTINE_MAX_NUM_OF_SECTORS >= Local_u8Sector)
				{
					/* Erase Requested Sector */
					MFDI_voidSectorErase(Local_u8Sector);
					/* Send To tester Positive response */
					SendPostiveResponse(Req_Frame, 4);
					ValidBankAfterErase(Local_u8Sector);
				}
				else
				{
					/* Send To tester Negative response */
					SendNegativeResponse(SID_SESSION_CONTROL, PROGRAMMING_FAILURE);
				}
			}
			else if (BANK_CHANGE_ROUTINE == Local_u16Routine_type)
			{
				Local_u8Bank = Req_Frame[ROUTINE_BANK_TO_JMP];
				if (Local_u8Bank == ROUTINE_SELECT_BANK1)
				{
					UDS_Data.ActiveBank = UDS_BANK1_ACTIVE;
					FEE_voidSetData(UDS_Data.Data);
				}
				if (Local_u8Bank == ROUTINE_SELECT_BANK2)
				{
					UDS_Data.ActiveBank = UDS_BANK2_ACTIVE;
					FEE_voidSetData(UDS_Data.Data);
				}
				else
				{
					/* Send To tester Negative response */
					SendNegativeResponse(SID_SESSION_CONTROL, GENERAL_REJECT);
				}
			}
			else
			{
				/* Send To tester Negative response */
				SendNegativeResponse(SID_SESSION_CONTROL, REQUEST_OUT_OF_RANGE);
			}
		}
		else
		{
			/* Send To tester Negative response */
			SendNegativeResponse(SID_SESSION_CONTROL, SECURITY_ACCESS_DENIED);
		}

	}
}



/*************************************************************************************/
/******************************** SID Reset ******************************************/
/*************************************************************************************/
static void SID_Reset(void)
{
	/************************* Function Local Variables *********************************/



	/* Check for requested session */
	if (SOFT_RESET == Req_Frame[UDS_SF])
	{
		/* Set soft reset marker */
		UDS_Data.SoftResetRequest = 1;
		/* Write Data to FEE */
		FEE_voidSetData(UDS_Data.Data);

		/* DeInitialization of System */
		System_DeInit();
		/* Soft reset of ECU */
		MNVIC_SystemReset();
	}
	else
	{
		/* Send To tester Negative response */
		SendNegativeResponse(SID_SESSION_CONTROL, SF_NOT_SUPPORTED);
	}
}

/*************************************************************************************/
/******************************* Request Download ************************************/
/*************************************************************************************/


/* Provides SubFunction operation of Request Download */
static void SID_RequestDownload(void)
{
	/************************* Function Local Variables *********************************/
	/* Data size requested to download */
	u32 Local_u8DataSize;

	if (SecurityLVLOneStatus == SECURITY_UNLOCKED)
	{
		/* Operate if there is Previous request */
		if (RequestDownload_Flag == FALSE)
		{
			/* Receive Start address of tester wanted to flash */
			StartAddress =		  		((((u32)Req_Frame[REQ_DOWNLOAD_ADDRESS_4_BTYE_]) << 24) & (0xFF000000))
										| 	((((u32)Req_Frame[REQ_DOWNLOAD_ADDRESS_3_BTYE_]) << 16) & (0x00FF0000))
										| 	((((u32)Req_Frame[REQ_DOWNLOAD_ADDRESS_2_BTYE_]) << 8)  & (0x0000FF00))
										| 	((((u32)Req_Frame[REQ_DOWNLOAD_ADDRESS_1_BTYE_]) << 0)  & (0x000000FF));
			/* Receive Start size of data of tester wanted to flash */
			Local_u8DataSize =   			((((u32)Req_Frame[REQ_DOWNLOAD_SIZE_4_BTYE_]) << 24) & (0xFF000000))
										| 	((((u32)Req_Frame[REQ_DOWNLOAD_SIZE_3_BTYE_]) << 16) & (0x00FF0000))
										| 	((((u32)Req_Frame[REQ_DOWNLOAD_SIZE_2_BTYE_]) << 8)  & (0x0000FF00))
										| 	((((u32)Req_Frame[REQ_DOWNLOAD_SIZE_1_BTYE_]) << 0)  & (0x000000FF));

			DownLoad_AddressPosition = StartAddress;

			/*Size Valid and Address Valid*/
			if (((START_OF_BANK_1 == StartAddress) && ((UDS_BANK2_ACTIVE == UDS_Data.ActiveBank) || (UDS_NO_VALID_BANK == UDS_Data.ActiveBank)))
				|| ((START_OF_BANK_2 == StartAddress) && (UDS_BANK1_ACTIVE == UDS_Data.ActiveBank)))
			{
				if (MAX_BANK_SIZE <= Local_u8DataSize)
				{
					RequestDownload_Flag = TRUE;
					/* Send To tester Positive response */
					SendPostiveResponse(Req_Frame, 2);
				}
				else
				{
					/* Send To tester Negative response */
					SendNegativeResponse(SID_SESSION_CONTROL, UPLOAD_DOWNLOAD_NOT_ACCEPTED);
				}
			}
			/* Wrong Bank to flash in */
			else
			{
				/* Send To tester Negative response */
				SendNegativeResponse(SID_SESSION_CONTROL, REQUEST_OUT_OF_RANGE);
			}
		}
		else
		{
			/* Send To tester Negative response */
			SendNegativeResponse(SID_SESSION_CONTROL, UPLOAD_DOWNLOAD_NOT_ACCEPTED);
		}

	}
	else
	{
		/* Send To tester Negative response */
		SendNegativeResponse(SID_SESSION_CONTROL, SECURITY_ACCESS_DENIED);
	}
}


/*************************************************************************************/
/******************************* Transfer Data ***************************************/
/*************************************************************************************/

/* Provides SubFunction operation of Transfer Data */
static void SID_TransferData(void)
{
	/************************* Function Local Variables *********************************/
	u16 *DataBuffer = (u16*)&Req_Frame[3];
	u8 DataLen = Req_Len - 3;

	if (SecurityLVLOneStatus == SECURITY_UNLOCKED)
	{
		if (RequestDownload_Flag)
		{
			DownLoad_AddressPosition = StartAddress & 0xFFFF0000;
			DownLoad_AddressPosition = DownLoad_AddressPosition + (Req_Frame[1] << 8) + (Req_Frame[2]);

			MFDI_voidFlashWrite(DownLoad_AddressPosition, DataBuffer, (DataLen / 2));
			/* Send To tester Positive response */
			SendPostiveResponse(Req_Frame, 3);

			DownLoad_AddressPosition = DownLoad_AddressPosition + DataLen;
		}
	}
	else
	{
		/* Send To tester Negative response */
		SendNegativeResponse(SID_SESSION_CONTROL, SECURITY_ACCESS_DENIED);
	}

}
/*************************************************************************************/
/**************************** Request TransferExit  **********************************/
/*************************************************************************************/

/* Provides SubFunction operation of Request TransferExit  */
static void SID_RequestTransferExit (void)
{
	if (SecurityLVLOneStatus == SECURITY_UNLOCKED)
	{
		/* If there is no download request send from start */
		if (RequestDownload_Flag)
		{
			RequestDownload_Flag = FALSE;
			SendPostiveResponse(Req_Frame, 1);

			ValidNewBank();
		}
		else
		{
			/* Send To tester Negative response */
			SendNegativeResponse(SID_SESSION_CONTROL, REQUEST_OUT_OF_RANGE);
		}
	}
	else
	{
		/* Send To tester Negative response */
		SendNegativeResponse(SID_SESSION_CONTROL, SECURITY_ACCESS_DENIED);
	}
}


/*************************************************************************************/
/******************************** Security Access ************************************/
/*************************************************************************************/

/* Provides SubFunction operation of Security Access */
static void SID_SecurityAccess(void)
{
	/************************* Function Local Variables *********************************/
	/* Result of Key compare in security access */
	u8 Local_u8KeyCompareResult;

	if (SECURITY_LVL_1_REQ_SEED == Req_Frame[UDS_SF])
	{
		/* Generate response frame when tester request seed for security level 1 */
		GenerateSeedReponseLVL1();
		/* Indicate that tester request seed and have 5 attempts to successfully send correct Key */
		Security_RequestSeed_Flag = TRUE ;
		/* Reset number of attempts */
		Security_SendKeyAttemptsCnt = 0;
	}
	else if (SECURITY_LVL_1_SEND_KEY == Req_Frame[UDS_SF])
	{
		if (Security_RequestSeed_Flag)
		{
			/* Compare tester send key With Local Generated key */
			Local_u8KeyCompareResult = CompareSecurityLVL1Key(&Req_Frame[SECURITY_START_OF_KEY]);

			/* Check if Key match or not */
			if (SECURITY_KEY_MATCH == Local_u8KeyCompareResult)
			{
				SecurityLVLOneStatus = SECURITY_UNLOCKED;
				/* Send To tester Positive response */
				SendPostiveResponse(Req_Frame, 2);

				Security_RequestSeed_Flag = FALSE;
			}
			else
			{
				if (SECUITY_MAX_NUM_OF_ATTEMPTS >= Security_SendKeyAttemptsCnt)
				{
					/* Send To tester Negative response */
					SendNegativeResponse(SID_SESSION_CONTROL, INVALID_KEY);
					/* Increment number of attempts */
					Security_SendKeyAttemptsCnt++;
				}
				else
				{
					/* Tester Failed to send correct Key For Max number of try's
					 * Should requests seed again
					 */
					/* Send To tester Negative response */
					SendNegativeResponse(SID_SESSION_CONTROL, EXCEEDED_NUMBER_OF_ATTEMPTS);
				}
			}
		}
		else
		{
			/* Send To tester Negative response */
			SendNegativeResponse(SID_SESSION_CONTROL, FAILURE_PREVENTS_EXECUTION_OF_REQUESTED_ACTION);
		}
	}
	else
	{
		/* Send To tester Negative response */
		SendNegativeResponse(SID_SESSION_CONTROL, SF_NOT_SUPPORTED);
	}
}


/* Generate response frame when tester request seed for security level 1 */
static void GenerateSeedReponseLVL1(void)
{
	u8 Response_SeedFrame[SECURITY_SEED_RES_FRAME_SIZE];
	u16 SeedValue;
	/* Set in response SID and SF */
	Response_SeedFrame[UDS_SID] = Req_Frame[UDS_SID];
	Response_SeedFrame[UDS_SF] = Req_Frame[UDS_SF];

	/* Required random number from system tick timer */
	SeedValue = (u16)MSYSTICK_u32GetRemainingTime();
	Response_SeedFrame[2] =  (u8)SeedValue;
	Response_SeedFrame[3] =  (u8)(SeedValue >> 8);
	SeedValue = (u16)MSYSTICK_u32GetRemainingTime();
	Response_SeedFrame[4] =  (u8)SeedValue;
	Response_SeedFrame[5] =  (u8)(SeedValue >> 8);
	SeedValue = (u16)MSYSTICK_u32GetRemainingTime();
	Response_SeedFrame[6] =  (u8)SeedValue;

	/* Generate key to be compare with that will receive from tester */
	GeneratedKey = ((  Response_SeedFrame[2] + Response_SeedFrame[3]
					  + Response_SeedFrame[4] + Response_SeedFrame[5]
					  + Response_SeedFrame[6]) * 2) / 4;
	/************* Debug ****************/
//	u8 str[3];
//	str[0] = 0x02;
//	str[1] = GeneratedKey>> 8;
//	str[2] = GeneratedKey;
//	BCM_SendFrameSetter(str);
	/************* Debug ****************/

	/* Send To tester Positive response */
	SendPostiveResponse(Response_SeedFrame, SECURITY_SEED_RES_FRAME_SIZE);
}



/* Compare tester send key With Local Generated key */
static u8 CompareSecurityLVL1Key(u8 *Local_pu8TesterKey)
{
	u32 Local_u32TesterKey;
	u8 Local_u8CompareResult = SECURITY_KEY_NOT_MATCH;

	Local_u32TesterKey = 			(((u32)Local_pu8TesterKey[0] << 24) 		& 0xFF000000)
									| (((u32)(Local_pu8TesterKey[1] << 16) ) 	& 0x00FF0000)
									| (((u32)(Local_pu8TesterKey[2] << 8)) 		& 0x0000FF00)
									| (((u32)(Local_pu8TesterKey[3])) 			& 0x000000FF);
	/* Compare Tester Key with UDS Key */
	if (Local_u32TesterKey == 0xFF)
	{
		Local_u8CompareResult = SECURITY_KEY_MATCH;
	}
	return Local_u8CompareResult;
}


/*************************************************************************************/
/********************************* Response ******************************************/
/*************************************************************************************/

/* Send To tester Negative response */
static void SendNegativeResponse(u8 Copy_u8SID, UDS_NRC_t Copy_enuNRC)
{
	/* Create negative response frame start with size then 0x7F that indicate negative response */
	u8 NegativeRes_Frame[4] = {NEGATIVE_RES_FRAME_SIZE, 0x7F};
	/* Followed by service ID that Send e for */
	NegativeRes_Frame[2] = Copy_u8SID;
	/* Last the reason of negative response */
	NegativeRes_Frame[3] = Copy_enuNRC;
	/* Set data to BCM to transmit it */
	BCM_SendFrameSetter(NegativeRes_Frame);
}

/* Send To tester Positive response */
static void SendPostiveResponse(u8 *Copy_pu8Frame ,u8 Copy_u8Size)
{

	u8 PostiveRes_Frame[10];
	PostiveRes_Frame[0] = Copy_u8Size;

	/* Add 0x40 to declare positive response send to tester */
	Copy_pu8Frame[UDS_SID] += 0x40;

	/* Add size of Frame to send to tester */
	for (u8 FrameIndex = 1; FrameIndex <= Copy_u8Size; FrameIndex++)
	{
		PostiveRes_Frame[FrameIndex] =  Copy_pu8Frame[FrameIndex - 1];
	}

	/* Set Frame that will send to tester to BCM */
	BCM_SendFrameSetter(PostiveRes_Frame);
}


/* Switch active Bank */
static void ValidNewBank(void)
{
	UDS_Data.ValidityMarker = 1;
	if (UDS_NO_VALID_BANK == UDS_Data.ActiveBank)
	{
		UDS_Data.ActiveBank = UDS_BANK1_ACTIVE;
	}
	else if (UDS_BANK1_ACTIVE == UDS_Data.ActiveBank)
	{
		UDS_Data.ActiveBank = UDS_BANK2_ACTIVE;
	}
	else if (UDS_BANK2_ACTIVE == UDS_Data.ActiveBank)
	{
		UDS_Data.ActiveBank = UDS_BANK1_ACTIVE;
	}

	FEE_voidSetData(UDS_Data.Data);
}

/* DeInitialization of System */
static void System_DeInit(void)
{
	/* DeInitialization of System timer */
	//MSYSTICK_voidStopInterval();
	/* DeInitialization of RCC */
	//MRCC_voidDeInit();
	/* DeInitialization of NVIC */
	//MNVIC_voidDeInit();
}

/* Invalid bank that erased */
static void ValidBankAfterErase(u8 Local_u8Sector)
{
	if ((Local_u8Sector == 4) && (UDS_BANK1_ACTIVE == UDS_Data.ActiveBank))
	{
		UDS_Data.ActiveBank = UDS_NO_VALID_BANK;
	}
	else if ((Local_u8Sector == 5) && (UDS_BANK2_ACTIVE == UDS_Data.ActiveBank))
	{
		UDS_Data.ActiveBank = UDS_NO_VALID_BANK;
	}
	FEE_voidSetData(UDS_Data.Data);
}
