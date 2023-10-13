/*****************************************************************/
/* Author  : Mina2                                               */
/* Layer   : MCAL                                                */
/* SWC     : MSYSTICK                                            */
/* Version : 1.0                                                 */
/* Date    : 12 Sep 2023                                         */
/*****************************************************************/
#ifndef MSYSTICK_INTERFACE_H_
#define MSYSTICK_INTERFACE_H_

/* Status of SYSTICK */
typedef enum
{
	STK_DISABLE,
	STK_ENABLE
}SYSTICKState;

/* Initialization of SYSTICK clock source */
void MSYSTICK_voidInit(void);
/* Enable Timer and Load ticks to load register */
void MSYSTICK_voidStart(u32 Copy_u32Loadvalue);
/* Disable Timer, clear load register and clear Value register */
void MSYSTICK_voidStop(void);
/* Delay in Milli second No Limit */
void MSYSTICK_voidDelayMs(u32 Copy_u32DelayValue);
/* Delay in micro second No Limit */
void MSYSTICK_voidDelayUs(u32 Copy_u32DelayValue);
/* Delay in Milli second Max 1048 ms */
void MSYSTICK_voidW8DelayMs(u32 Copy_u32DelayValue);
/* Delay in micro second Max 1048 ms */
void MSYSTICK_voidW8DelayUs(u32 Copy_u32DelayValue);
/* Clear interrupt flag */
u8   MSYSTICK_u8ReadCountFlag(void);
/* Enable/Disable SYSTICK interrupt */
void MSYSTICK_voidCtrlIntState(SYSTICKState Copy_enuState);
/* Get From SYSTICK registers Elapsed Time */
u32  MSYSTICK_u32GetElapsedTime(void);
/* Get From SYSTICK registers Remaining Time */
u32  MSYSTICK_u32GetRemainingTime(void);
/* Set system tick as interval of time single times */
void MSYSTICK_voidSetIntervalSingle  (u32 Copy_u32Ticks, void (*Copy_ptr)(void));
/* Set system tick as interval of time Periodic times */
void MSYSTICK_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void (*Copy_ptr)(void));
/* stop system tick as interval */
void MSYSTICK_voidStopInterval(void);

void MSTK_voidSetBusyWait( u32 Copy_u32Ticks );

#endif
