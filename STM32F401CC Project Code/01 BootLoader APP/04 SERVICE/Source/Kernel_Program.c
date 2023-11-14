#include "StdTypes.h"
#include "MemMap.h"
#include "Timers.h"
#include "Timers_Services.h"
#include "Kernel_Interface.h"
#include "Kernel_Private.h"
#include "Kernel_Cfg.h"




typedef struct
{
	u16 periodicity;
	void (*TaskFunc) (void);
	Task_Status_t status;
	u16 FirstDelay;
	}Task_t;


static Task_t SystemsTasks[RTOS_TASK_NUM] = {{NULL}};


void RTOS_voidStart(void)
{
	MSYSTICK_voidSetIntervalPeriodic(1, Schedular);
	
	sei();
} 

Error_type RTOS_Error_typeCreateTask(u8 LocalPriority, void (*Local_PTaskFunc)(void), u16 Localperiodicity, u16 localFirstDelay)
{
	Error_type ErrorState = OK;
	if (Local_PTaskFunc != NULLPTR)
	{
		/*check if the given priority is available or not*/
		if (SystemsTasks[LocalPriority].TaskFunc == NULLPTR)
		{
			SystemsTasks[LocalPriority].TaskFunc = Local_PTaskFunc;
			SystemsTasks[LocalPriority].periodicity = Localperiodicity;
			SystemsTasks[LocalPriority].status = RESUME;
			SystemsTasks[LocalPriority].FirstDelay = localFirstDelay;
		}
		else
		{
			ErrorState = ERROR;
		}
	} 
	else
	{
		ErrorState = NULL_POINTER;
	}
	return ErrorState;
}

void RTOS_voidSuspendTask(u8 LocalPriority)
{
	SystemsTasks[LocalPriority].status = SUSPENDED;
}

void RTOS_voidResumeTask(u8 LocalPriority)
{
	SystemsTasks[LocalPriority].status = RESUME;
}

void RTOS_voidDeleteTask(u8 LocalPriority)
{
	SystemsTasks[LocalPriority].TaskFunc = NULLPTR;
}



static void Schedular(void)
{
	u8 TaskIndex;

	for (TaskIndex = 0; TaskIndex < RTOS_TASK_NUM; TaskIndex++)
	{
		if (SystemsTasks[TaskIndex].status == RESUME)
		{
			/* Invoke the task function if it is not NULL */
			if (SystemsTasks[TaskIndex].FirstDelay == 0)
			{
				if (SystemsTasks[TaskIndex].TaskFunc != NULLPTR)
				{
					SystemsTasks[TaskIndex].TaskFunc();
				}
				/* Make 1st delay equal to periodicity - 1*/
				SystemsTasks[TaskIndex].FirstDelay = SystemsTasks[TaskIndex].periodicity - 1;
			}
			else
			{
				/* 1st delay is not zero, so decrement the 1st delay */
				(SystemsTasks[TaskIndex].FirstDelay)--;
			}
		}
		else
		{
			/* Task suspended, Do nothing */
		}
	}
	
} 