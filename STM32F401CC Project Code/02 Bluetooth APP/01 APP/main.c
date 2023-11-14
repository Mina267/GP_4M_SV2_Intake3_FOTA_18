/* LIB */
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

/* MCAL */
#include "../include/MGPIO_interface.h"
#include "../include/MRCC_interface.h"
#include "../include/MSYSTICK_Interface.h"
#include "../include/MDMA_Interface.h"
#include "../include/MNVIC_Interface.h"
#include "../include/MUART_Interface.h"
#include "../include/TIM_interface.h"

/* HAL */
#include "../include/SERVO_interface.h"
#include "../include/HC_05_Interface.h"
#include "../include/ULTRASONIC_interface.h"
#include "../include/RGB_Interface.h"
#include "../include/MOTOR_interface.h"


/* Service */
#include "../include/BCM.h"
#include "../include/UDS_Interface.h"

/* FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"





static void WriteNumber_4D(u32 num);



/* Operate all car motors in CW direction */
static void MoveForward(u8 Copy_u8Speed);
/* Operate all car motors in CCW direction */
static void MoveBackword(u8 Copy_u8Speed);
/* Operate two right car motors in CW direction
 * Operate two left car motors in CCW direction */
static void MoveRight(u8 Copy_u8Speed);
/* Operate two right car motors in CCW direction
 * Operate two left car motors in CW direction */
static void MoveLeft(u8 Copy_u8Speed);
/* Stop all car motors */
static void CarStop(void);





typedef enum
{
	BLU_FOWARD_DIR_REQ  = 'F',
	BLU_BACKWARD_DIR_REQ = 'B',
	BLU_RIGHT_DIR_REQ = 'R',
	BLU_LEFT_DIR_REQ = 'L',
	BLU_INC_SPEED_REQ = 'W',
	BLU_DEC_SPEED_REQ = 'U',
	BLU_STOP_REQ = 'S',
	BLU_RUN_REQ = 'O',
}RecFrameStatus_t;




/* Control RC car from order received from Bluetooth */
static void BluetoothFreeRun_task_handler(void*parameters)
{
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	u8 data;
	u8 speed = 60;

	while(1)
	{

		/* Continuous move will receive frame from UART neither that stop
		 * Check for request receive for direction of car will move */
		data = MUART6_u8ReciveNoBlock();

		/* Operate car motor to move in forward direction */
		if (data == BLU_FOWARD_DIR_REQ)
		{
			MoveForward(speed);
		}
		else if (data == BLU_BACKWARD_DIR_REQ)
		{
			/* Operate car motor to move in backward direction */
			MoveBackword(speed);
		}
		else if (data == BLU_RIGHT_DIR_REQ)
		{
			/* Operate car motor to move in right direction */
			MoveRight(speed);

		}
		else if (data == BLU_LEFT_DIR_REQ)
		{
			/* Operate car motor to move in left direction */
			MoveLeft(speed);
		}
		else if (data == BLU_INC_SPEED_REQ)
		{
			if (speed <= 90)
			{

				speed = speed + 5;
			}
		}

		else if (data == BLU_DEC_SPEED_REQ)
		{
			if (speed >= 10)
			{
				speed = speed - 5;
			}
		}

		else if (data == 'M')
		{
			MNVIC_SystemReset();
		}


		else
		{
			/* If there is no frame received stop car */
			CarStop();
		}


		vTaskDelayUntil(&xLastWakeTime, 200);
	}
}

/* RGB Set color task */
static void RGB_task_handler(void*parameters)
{
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	RGB_Color_type Color = RED;

	while(1)
	{
		/* Set new color of RGB */
		RGB_LedColor(Color);
		Color++;
		/* If color Ends start again */
		if (Color == COLOR_NUM)
		{
			Color = 0;
		}

		vTaskDelayUntil(&xLastWakeTime, 200);
	}
}

/* UDS Task */
static void UDS_task_handler(void*parameters)
{
	while(1)
	{
		UDS_voidRunnable();
		vTaskDelay(50);

	}
}





int main(void)
{
	/* Initialization of RCC */
	MRCC_voidInit();
	/* Enable clock for GPIOA peripheral */
	MRCC_voidEnable_Peripheral(RCC_AHB1, RCC_AHB1_GPIOA);
	/* Enable clock for GPIOB peripheral */
	MRCC_voidEnable_Peripheral(RCC_AHB1, RCC_AHB1_GPIOB);
	/* Enable clock for Flash driver peripheral */
	MRCC_voidEnable_Peripheral(RCC_AHB1LP, RCC_AHB1PL_FLITF);
	/* Enable clock for timer 1 peripheral for ICU to UltraSonic */
	MRCC_voidEnable_Peripheral(RCC_APB2, RCC_APB2_TIM1);
	/* Enable clock for timer 2 For UltrSonic trigger Delay*/
	MRCC_voidEnable_Peripheral(RCC_APB1, RCC_APB1_TIM2);
	/* Enable clock for timer 2 For UltrSonic trigger Delay*/
	MRCC_voidEnable_Peripheral(RCC_APB1, RCC_APB1_TIM3);
	/* Enable clock for timer 4 For ServoMotor and RGB*/
	MRCC_voidEnable_Peripheral(RCC_APB1, RCC_APB1_TIM4);
	/* Enable clock for timer 5 For Motors Speed control*/
	MRCC_voidEnable_Peripheral(RCC_APB1, RCC_APB1_TIM5);
	/* Enable clock for UART 6 For BlueTooth module HC-05 */
	MRCC_voidEnable_Peripheral(RCC_APB2, RCC_APB2_USART6);


	/* Channel 4 For ServoMotor */
	MGPIO_SetAlternativeFuncPin(PORTB, PIN9, TIM3_5);

	/* Initialization of GPIO */
	MGPIO_Init();


	/* Initialization of NVIC */
	MNVIC_voidInit();

	/* Initialization of UltrSonic */
	HUltrasonicInti();

	/* Initialization of RGB */
	RGB_Init();

	/* Initialization of MOTOR */
	MOTOR_Init();

	/* Initialization of BlueTooth module HC-05 */
	HC_05_voidInit();

	/* Initialization of UDS */
	UDS_voidInit();

	/* Status of creating task */
	BaseType_t status;

	/* Create the task, storing the handle. */

	/* UDS Task */
	status = xTaskCreate(UDS_task_handler, NULL, 5000, NULL, 5, NULL);
	configASSERT(status == pdPASS);

	/* BlueTooth Control Task */
	status = xTaskCreate(BluetoothFreeRun_task_handler, NULL, 2000, NULL, 1, NULL);
	configASSERT(status == pdPASS);

	/* RGB Set color task */
	status = xTaskCreate(RGB_task_handler, NULL, 100, NULL, 2, NULL);
	configASSERT(status == pdPASS);

	/* Start Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}
	return 0;
}


















/* Operate all car motors in CW direction */
static void MoveForward(u8 Copy_u8Speed)
{
	MOTOR_Speed_dir(M1, Copy_u8Speed , M_CW);
	MOTOR_Speed_dir(M2, Copy_u8Speed , M_CW);

}

/* Operate all car motors in CCW direction */
static void MoveBackword(u8 Copy_u8Speed)
{

	MOTOR_Speed_dir(M1, Copy_u8Speed , M_CCW);
	MOTOR_Speed_dir(M2, Copy_u8Speed , M_CCW);
}

/* Operate two right car motors in CW direction
 * Operate two left car motors in CCW direction */
static void MoveRight(u8 Copy_u8Speed)
{
	MOTOR_Speed_dir(M1, Copy_u8Speed , M_CW);
	MOTOR_Speed_dir(M2, Copy_u8Speed , M_CCW);
}

/* Operate two right car motors in CCW direction
 * Operate two left car motors in CW direction */
static void MoveLeft(u8 Copy_u8Speed)
{
	MOTOR_Speed_dir(M1, Copy_u8Speed , M_CCW);
	MOTOR_Speed_dir(M2, Copy_u8Speed , M_CW);

}

/* Stop all car motors */
static void CarStop(void)
{
	MOTOR_Speed_dir(M1, 0 , M_STOP);
	MOTOR_Speed_dir(M2, 0 , M_STOP);
}





static void WriteNumber_4D(u32 num)
{
	//LCD_WriteChar(((num%100000)/10000)+'0');
	MUART6_voidTransmitSynch(((num%10000)/1000)+'0');
	MUART6_voidTransmitSynch(((num%1000)/100)+'0');
	MUART6_voidTransmitSynch(((num%100)/10)+'0');
	MUART6_voidTransmitSynch(((num%10)/1)+'0');
	MUART6_voidTransmitSynch('\n');
}




