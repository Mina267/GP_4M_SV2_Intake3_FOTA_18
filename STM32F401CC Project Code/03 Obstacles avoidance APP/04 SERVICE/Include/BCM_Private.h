

#ifndef BCM_PRIVATE_H_
#define BCM_PRIVATE_H_

/************* Send *****************/
typedef enum{
	Q_EMPTY,
	Q_FULL = 0,
	Q_DONE,
}Queue_status_t;

/************* Receive *****************/

typedef enum{
	Q_REC_EMPTY = 0,
	Q_REC_FULL = 0,
	Q_REC_DONE,
}Queue_Rec_status_t;

/************* Send String ********************/
#define IN_START					0
#define OUT_START					0


/************* Send Frames *****************/
#define SEND_VAR_FRAME				2
#define SEND_FIXED_FRAME			1
#define SEND_STRING					0


/************* Receive String *****************/
#define NOT_SEND_LAST_PATTEN		0
#define SEND_LAST_PATTEN			1
#define SEND_SEC_LAST_PATTERN		2

/************* Receive Frame *****************/
#define REC_FRAME_FIXED_SIZE		0
#define REC_FRAME_NO_FIXED_SIZE		1


/******************************************************* Send Strings from UART ********************************************************/

/* Pass new string by reference to Queue */ 
static Queue_status_t Queue_In (s8 *str);
/* Take string by reference from Queue */
static Queue_status_t Queue_Out (s8 **str);
/* Call Back function of UART transmitter */
static void BCM_func_tx(void);

/******************************************************* Receive Strings from UART ******************************************************/
/* Get Frame from Queue */
static Queue_Rec_status_t Queue_RecStr_Out (s8 *str);
/* Put frame in Queue by value in Receiver ISR */
static Queue_Rec_status_t Queue_RecStr_In (s8 *str);
static void Rx_Func(void);

/******************************************************* Receive frames from UART ******************************************************/
/* Put frame in Queue by value in Receiver ISR */
static void func_Rx_Qin (void);
/* Get Frame from Queue */
static Queue_Rec_status_t Queue_Rec_Out (u8 *str);



/******************************************************* Send frames from UART **********************************************************/
/* Put frame in Queue by value in Receiver from setter */
static Queue_status_t QueueFrmae_In (u8 *Frame);
/* Get Frame from Queue */
static Queue_status_t QueueFrmae_Out (u8 *Frame);

#endif /* BCM_PRIVATE_H_ */
