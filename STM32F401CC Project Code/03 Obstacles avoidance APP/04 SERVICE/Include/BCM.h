

#ifndef BCM_H_
#define BCM_H_


/************************ Send String *********************************/
typedef enum
{
	STR_TAKE,
	STR_NTAKE,
}BCM_status_t;

/************************ Receive String ******************************/
typedef enum
{
	BCM_STR_RECEVIED,
	BCM_NO_STR_TORECIVE,
	BCM_STR_READED
}BCM_RecStr_status_t;
/************************ Receive Frame *******************************/
typedef enum
{
	FRAME_RECEIVED,
	NO_FRAME_TORECIVE,
}UART_Rec_status_t;


/****************************************************************************************************/
/****************************************** BCM API's ***********************************************/
/****************************************************************************************************/


/****************************************************************************************************/
/********************************* Receive Strings from UART ****************************************/
/****************************************************************************************************/


/* Initialization of BCM receive string asynchronous 
 * Set call back function
 * Enable Receiver interrupt
 * Set first End pattern
 * set second end pattern if any */
void BCM_ReceiveStringAshync_Init(void);
/* 55 us */
/* Take data from receive Queue by value */
BCM_RecStr_status_t BCM_Getter_ReceiveStringAshync(s8* str);



/****************************************************************************************************/
/********************************* Receive frames from UART *****************************************/
/****************************************************************************************************/

/* Initialization of BCM receive Frame asynchronous 
 * Set call back function
 * Enable Receiver interrupt */
void BCM_FrameReceive_Init(void);
/* If there is Frame to receive from Queue Return FRAME_RECEIVED else return NO_FRAME_TORECIVE
 * Take data from receive Queue by value */
UART_Rec_status_t BCM_FrameReceive_GetterFrameAshync(u8* Frame);


/****************************************************************************************************/
/*********************************** Send Strings from UART *****************************************/
/****************************************************************************************************/

/* Initialization of BCM Send strings
 * Set call back function
 * Enable transmitter interrupt */
void BCM_SendStringInit(void);

/* Set string to send In BCM Queue */
BCM_status_t BCM_SendStringSetter(s8* str);
/* Running of BCM send string send one char at time
 * then interrupt of transmitter synchronize with function to send another char */
void BCM_SendStringRunnable(void);
/* Enable Send strings */
void BCM_SendString_Enable(void);
/* Disable Send strings */
void BCM_SendString_Disable(void);


/****************************************************************************************************/
/************************************ Send Frames from UART *****************************************/
/****************************************************************************************************/

/* Initialization of BCM Send strings 
 * Set call back function 
 * Enable transmitter interrupt */
void BCM_SendFrmaeInit(void);
/* Set string to send In BCM Queue */
BCM_status_t BCM_SendFrameSetter(u8* str);
/* Running of BCM send Frame & strings send one char at time 
 * then interrupt of transmitter synchronize with function to send another char */
void BCM_SendFrameRunnable(void);
/* Enable Send strings */
void BCM_SendFrame_Enable(void);
/* Disable Send strings */
void BCM_SendFrame_Disable(void);


#endif /* BCM_H_ */
