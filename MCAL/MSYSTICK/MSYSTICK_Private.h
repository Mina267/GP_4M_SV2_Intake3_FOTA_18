/*****************************************************************/
/* Author  : Mina2                                               */
/* Layer   : MCAL                                                */
/* SWC     : MSYSTICK                                            */
/* Version : 1.0                                                 */
/* Date    : 12 Sep 2023                                         */
/*****************************************************************/
#ifndef MSYSTICK_PRIVATE_H_
#define MSYSTICK_PRIVATE_H_

/* SYSTICK Start Base address */
#define STK_BASE_ADDRSS					(0xE000E010)

/* SYSTICK register map */
typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;
}STK_t;

/* pointer to struct of type NVIC_t point to Base address of SYSTICK Peripheral */
#define     STK    						((volatile STK_t*)STK_BASE_ADDRSS)


#define MSTK_SRC_AHB_DIV_8       	  	(0)
#define MSTK_SRC_AHB      				(1)

#define CTRL_ENABLE						(0)
#define CTRL_TICKINT					(1)
#define CTRL_CLKSOURCE					(2)
#define CTRL_COUNTFLAG					(16)



#define MSTK_NO_INTERVAL				(0)
#define MSTK_SINGLE_INTERVAL			(1)
#define MSTK_PERIOD_INTERVAL			(2)


#define MICRO_SEC_FACTOR_AHB_8			(2)
#define MICRO_SEC_FACTOR_AHB			(16)
#define MILLI_SEC_FACTOR_AHB_8			(2000)
#define MILLI_SEC_FACTOR_AHB			(16000)

#define MAX_CNT_OF_STK					(16777216)
#define FULL_STK_LOAD_REG				(0xFFFFFF)

/* Count number of SYSTICK overflow */
static void CountOverFlow(void);

static void IntervalCallBackFunction(void);


#endif
