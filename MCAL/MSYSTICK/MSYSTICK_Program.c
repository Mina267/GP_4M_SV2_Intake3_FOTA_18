/*****************************************************************/
/* Author  : Mina2                                               */
/* Layer   : MCAL                                                */
/* SWC     : MSYSTICK                                            */
/* Version : 1.0                                                 */
/* Date    : 12 Sep 2023                                         */
/*****************************************************************/
#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"
#include "../include/MSYSTICK_Interface.h"
#include "../include/MSYSTICK_Private.h"
#include "../include/MSYSTICK_Config.h"



/* Define Callback Global Variable */
static void(*MSTK_CallBack)(void);

/* Define Variable for interval mode */
static volatile u8 MSTK_u8ModeOfInterval;

static volatile u16 MSTK_u16NumberOfOverFlow;
static volatile bool_t MSTK_BusyFlag = FALSE;

/* Define Callback Interval Functions */
static void(*Interval_CallBack)(void);

volatile bool_t IntervalFinsih = TRUE;



/* Initialization of SYSTICK clock source */
void MSYSTICK_voidInit(void)
{

	STK->CTRL = 0x00000000;
#if (MSTK_CLK_SRC == MSTK_SRC_AHB)
	SET_BIT(STK->CTRL, 2);
#elif (MSTK_CLK_SRC == MSTK_SRC_AHB_DIV_8)
	CLR_BIT(STK->CTRL, 2);
#endif
}

/* Enable Timer and Load ticks to load register */
void MSYSTICK_voidStart(u32 Copy_u32Loadvalue)
{

	/* Load ticks to load register */
	STK->LOAD = Copy_u32Loadvalue;
	/* clear Value register */
	STK->VAL  = 0;
	/* Enable Timer */
	SET_BIT(STK->CTRL, CTRL_ENABLE);
}

/* Disable Timer, clear load register and clear Value register */
void MSYSTICK_voidStop(void)
{
	/* Disable Timer */
	SET_BIT(STK->CTRL, 0);
	/* clear load register */
	STK->LOAD = 0;
	/* clear Value register */
	STK->VAL  = 0;
}




/* Delay in milli second Max 1048 ms */
void MSYSTICK_voidW8DelayMs(u32 Copy_u32DelayValue)
{

	/* Assuming input clock is AHB clock 16 MHz */
#if (MSTK_CLK_SRC == MSTK_SRC_AHB)

	MSYSTICK_u8ReadCountFlag();											/* Clear interrupt flag */
	MSYSTICK_voidStart(MILLI_SEC_FACTOR_AHB * Copy_u32DelayValue);		/* Start Timer */
	while(MSYSTICK_u8ReadCountFlag() == 0);								/* Wait till flag is raised */
	MSYSTICK_voidStop();												/* Stop Timer */

	/* Assuming input clock is AHB / 2 clock 16 / 2 = 2 MHz */
#elif (MSTK_CLK_SRC == MSTK_SRC_AHB_DIV_8)

	MSYSTICK_u8ReadCountFlag();												/* Clear interrupt flag */
	MSYSTICK_voidStart(MILLI_SEC_FACTOR_AHB_8 * Copy_u32DelayValue);		/* Start Timer */
	while(MSYSTICK_u8ReadCountFlag() == 0)									/* Wait till flag is raised */
	{
		if (STK->LOAD == 0	&& STK->VAL  == 0)
		{
			break;
		}
	}
	MSYSTICK_voidStop();													/* Stop Timer */

#endif

}



/* Delay in micro second Max 1048 ms */
void MSYSTICK_voidW8DelayUs(u32 Copy_u32DelayValue)
{
	/* Assuming input clock is AHB clock 16 MHz */
#if (MSTK_CLK_SRC == MSTK_SRC_AHB)


	MSYSTICK_u8ReadCountFlag();											/* Clear interrupt flag */
	MSYSTICK_voidStart(MICRO_SEC_FACTOR_AHB * Copy_u32DelayValue);		/* Start Timer */
	while(MSYSTICK_u8ReadCountFlag() == 0);								/* Wait till flag is raised */
	MSYSTICK_voidStop();												/* Stop Timer */

#elif (MSTK_CLK_SRC == MSTK_SRC_AHB_DIV_8)

	MSYSTICK_u8ReadCountFlag();											/* Clear interrupt flag */
	MSYSTICK_voidStart(MICRO_SEC_FACTOR_AHB_8 * Copy_u32DelayValue);	/* Start Timer */
	while(MSYSTICK_u8ReadCountFlag() == 0)								/* Wait till flag is raised */
	{
		if (STK->LOAD == 0	&& STK->VAL  == 0)
		{
			break;
		}
	}
	MSYSTICK_voidStop();												/* Stop Timer */

#endif

}

/* Delay in Milli second No Limit */
void MSYSTICK_voidDelayMs(u32 Copy_u32DelayValue)
{
	/* Assuming input clock is AHB clock 16 MHz */
#if (MSTK_CLK_SRC == MSTK_SRC_AHB)
	MSYSTICK_u8ReadCountFlag();							/* Clear interrupt flag */
	MSYSTICK_voidCtrlIntState(STK_ENABLE);				/* Enable STK Interrupt */
	MSYSTICK_voidStart(MILLI_SEC_FACTOR_AHB - 1);		/* Start Timer */
	MSTK_u16NumberOfOverFlow = Copy_u32DelayValue;		/* Set Number of overFlow */
	MSTK_CallBack = CountOverFlow;						/* Set callBack Function */
	while(!MSTK_BusyFlag);								/* Wait till flag is raised */
	MSYSTICK_voidCtrlIntState(STK_DISABLE);				/* Disable STK Interrupt */
	MSYSTICK_voidStop();								/* Stop Timer */
	MSTK_CallBack = NULLPTR;							/* Clear CallBack */
	MSTK_BusyFlag = FALSE;								/* synchronization Clear Flag */
	MSTK_u16NumberOfOverFlow = NULL;					/* reset counter */

#elif (MSTK_CLK_SRC == MSTK_SRC_AHB_DIV_8)
	MSYSTICK_u8ReadCountFlag();							/* Clear interrupt flag */
	MSYSTICK_voidCtrlIntState(STK_ENABLE);				/* Enable STK Interrupt */
	MSYSTICK_voidStart(MILLI_SEC_FACTOR_AHB_8 - 1);		/* Start Timer */
	MSTK_u16NumberOfOverFlow = Copy_u32DelayValue;		/* Set Number of overFlow */
	MSTK_CallBack = CountOverFlow;						/* Set callBack Function */
	while(!MSTK_BusyFlag);								/* Wait till flag is raised */
	MSYSTICK_voidCtrlIntState(STK_DISABLE);				/* Disable STK Interrupt */
	MSYSTICK_voidStop();								/* Stop Timer */
	MSTK_CallBack = NULLPTR;							/* Clear CallBack */
	MSTK_BusyFlag = FALSE;								/* synchronization Clear Flag */
	MSTK_u16NumberOfOverFlow = NULL;					/* reset counter */
#endif
}

/* Delay in micro second No Limit */
void MSYSTICK_voidDelayUs(u32 Copy_u32DelayValue)
{
	/* Assuming input clock is AHB clock 16 MHz */
#if (MSTK_CLK_SRC == MSTK_SRC_AHB)
	MSYSTICK_u8ReadCountFlag();							/* Clear interrupt flag */
	MSYSTICK_voidCtrlIntState(STK_ENABLE);				/* Enable STK Interrupt */
	MSYSTICK_voidStart(MICRO_SEC_FACTOR_AHB - 1);		/* Start Timer */
	MSTK_u16NumberOfOverFlow = Copy_u32DelayValue;		/* Set Number of overFlow */
	MSTK_CallBack = CountOverFlow;						/* Set callBack Function */
	while(!MSTK_BusyFlag);								/* Wait till flag is raised */
	MSYSTICK_voidCtrlIntState(STK_DISABLE);				/* Disable STK Interrupt */
	MSYSTICK_voidStop();								/* Stop Timer */
	MSTK_CallBack = NULLPTR;							/* Clear CallBack */
	MSTK_BusyFlag = FALSE;								/* synchronization Clear Flag */
	MSTK_u16NumberOfOverFlow = NULL;					/* reset counter */

#elif (MSTK_CLK_SRC == MSTK_SRC_AHB_DIV_8)
	MSYSTICK_u8ReadCountFlag();							/* Clear interrupt flag */
	MSYSTICK_voidCtrlIntState(STK_ENABLE);				/* Enable STK Interrupt */
	MSYSTICK_voidStart(MICRO_SEC_FACTOR_AHB_8 - 1);		/* Start Timer */
	MSTK_u16NumberOfOverFlow = Copy_u32DelayValue;		/* Set Number of overFlow */
	MSTK_CallBack = CountOverFlow;						/* Set callBack Function */
	while(!MSTK_BusyFlag);								/* Wait till flag is raised */
	MSYSTICK_voidCtrlIntState(STK_DISABLE);				/* Disable STK Interrupt */
	MSYSTICK_voidStop();								/* Stop Timer */
	MSTK_CallBack = NULLPTR;							/* Clear CallBack */
	MSTK_BusyFlag = FALSE;								/* synchronization Clear Flag */
	MSTK_u16NumberOfOverFlow = NULL;					/* reset counter */
#endif
}


/* Count number of SYSTICK overflow */
static void CountOverFlow(void)
{
	MSTK_u16NumberOfOverFlow--;
#include "../include/MGPIO_interface.h"
	MGPIO_TogglePin(PORTA, PIN3);
	if (MSTK_u16NumberOfOverFlow == NULL)
	{
		MSTK_BusyFlag = TRUE;
	}

}

/* Clear interrupt flag */
u8 MSYSTICK_u8ReadCountFlag(void)
{
	return GET_BIT(STK->CTRL, CTRL_COUNTFLAG);
}

/* Enable/Disable SYSTICK interrupt */
void MSYSTICK_voidCtrlIntState(SYSTICKState Copy_enuState)
{
	switch (Copy_enuState)
	{
	case STK_ENABLE:
		SET_BIT(STK->CTRL, CTRL_TICKINT);
		break;
	case STK_DISABLE:
		CLR_BIT(STK->CTRL, CTRL_TICKINT);
		break;
	default:
		break;
	}
}

/* Get From SYSTICK registers Elapsed Time */
u32 MSYSTICK_u32GetElapsedTime(void)
{
	return (STK->LOAD - STK->VAL);
}
/* Get From SYSTICK registers Remaining Time */
u32 MSYSTICK_u32GetRemainingTime(void)
{
	return (STK->VAL);
}




/* Set system tick as interval of time single times */
void MSYSTICK_voidSetIntervalSingle(u32 Copy_u32Ticks, void (*Copy_ptr)(void))
{

	MSYSTICK_voidStopInterval();
	MSYSTICK_u8ReadCountFlag();							/* Clear interrupt flag */
	MSYSTICK_voidStart(Copy_u32Ticks);					/* Start Timer */
	MSTK_CallBack = IntervalCallBackFunction;			/* Set callBack Function */
	Interval_CallBack = Copy_ptr;						/* Set Interval callBack Function */
	MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL;		/* Set Mode to Single */
	MSYSTICK_voidCtrlIntState(STK_ENABLE);				/* Enable STK Interrupt */


}

/* Set system tick as interval of time Periodic times */
void MSYSTICK_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void (*Copy_ptr)(void))
{

	if (IntervalFinsih == TRUE)
	{
		MSYSTICK_voidStopInterval();
		MSYSTICK_u8ReadCountFlag();							/* Clear interrupt flag */
		MSYSTICK_voidCtrlIntState(STK_ENABLE);				/* Enable STK Interrupt */
		MSYSTICK_voidStart(Copy_u32Ticks);					/* Start Timer */
		MSTK_CallBack = IntervalCallBackFunction;			/* Set callBack Function */
		Interval_CallBack = Copy_ptr;						/* Set Interval callBack Function */
		MSTK_u8ModeOfInterval = MSTK_PERIOD_INTERVAL;		/* Set Mode to Single */
		IntervalFinsih = FALSE;
	}

}

/* Interval callBack */
static void IntervalCallBackFunction(void)
{
	if (MSTK_u8ModeOfInterval == MSTK_SINGLE_INTERVAL)
	{
		MSYSTICK_voidStopInterval();
	}

	Interval_CallBack();


}
/* stop system tick as interval */
void MSYSTICK_voidStopInterval(void)
{
	MSYSTICK_voidCtrlIntState(STK_DISABLE);				/* Disable STK Interrupt */
	MSYSTICK_voidStop();								/* Stop Timer */
	MSTK_CallBack = NULLPTR;							/* Remove CallBack */
	IntervalFinsih = TRUE;
}


/* SYSTICK handler */
void SysTick_Handler(void)
{
	u8 Local_u8Temp;
	/* Callback notification */
	if (MSTK_CallBack != NULLPTR)
	{
		MSTK_CallBack();
	}



	/* Clear interrupt flag */
	Local_u8Temp = GET_BIT(STK->CTRL, CTRL_COUNTFLAG);
}




void MSTK_voidSetBusyWait( u32 Copy_u32Ticks )
{
	/* Load ticks to load register */
	STK -> VAL  = 0;
	STK -> LOAD = Copy_u32Ticks;



	/* Start Timer */
	SET_BIT(STK->CTRL, 0);

	/* Wait till flag is raised */
	while(GET_BIT(STK->CTRL,16) == 0);

	/* Stop Timer */
	CLR_BIT(STK->CTRL, 0);
	STK -> LOAD = 0;
	STK -> VAL  = 0;

}
