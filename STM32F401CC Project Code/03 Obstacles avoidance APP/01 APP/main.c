
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


#define THERE_OBSTACLE					LOW
#define THERE_NO_OBSTACLE				HIGH


/* Configuration */
/* Start Speed of Car */
#define OBSTACLE_DEFAULT_CAR_SPEED		20
/* Minimum distance to stop in cm */
#define MIN_DIS_TO_STOP					25


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

/* Private Variables */
static volatile f32 Distance;
GPIO_PinValue_t Right_IR_Status;
GPIO_PinValue_t Left_IR_Status;
GPIO_PinValue_t RightFront_IR_Status;
GPIO_PinValue_t LeftFront_IR_Status;

/* Car mode try to avoid obstacles user can stop and start car operation only */
static void AvoidObstaclesRead_task_handler(void*parameters)
{
	portTickType xLastWakeTime;
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();

	while(1)
	{

		/* Trigger UltraSonic for read */
		HUltraSonicTriger();

		/* Read status of IR sensor read */
		Right_IR_Status =  MGPIO_GetPinValue(PORTA, PIN5);
		Left_IR_Status =  MGPIO_GetPinValue(PORTB, PIN5);
		RightFront_IR_Status =  MGPIO_GetPinValue(PORTA, PIN7);
		LeftFront_IR_Status =  MGPIO_GetPinValue(PORTA, PIN6);

		/* Read  Distance from UltraSonic sensor */
		Distance = HUltrasonicReturnDistance();

		vTaskDelayUntil(&xLastWakeTime, 20);
	}
}
/* Car mode try to avoid obstacles user can stop and start car operation only */
static void AvoidObstacles_task_handler(void*parameters)
{
	portTickType xLastWakeTime;
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	static u8 data;
	static u8 flag = 1;
	u8 speed = OBSTACLE_DEFAULT_CAR_SPEED;
	while(1)
	{

		/* Continuous move will receive frame from UART neither that stop
		 * Check for request receive for direction of car will move */
		data = MUART6_u8ReciveNoBlock();

		if (data == BLU_RUN_REQ)
		{
			flag = 1;
		}
		else if (data == BLU_STOP_REQ)
		{
			flag = 0;
			CarStop();
		}
		else if (data == BLU_INC_SPEED_REQ || data == BLU_FOWARD_DIR_REQ)
		{
			speed += 5;
		}
		else if (data == BLU_DEC_SPEED_REQ || data == BLU_BACKWARD_DIR_REQ)
		{
			speed -= 5;
		}

		if (flag)
		{
			if (THERE_OBSTACLE ==  RightFront_IR_Status || THERE_OBSTACLE == LeftFront_IR_Status)
			{
				CarStop();
				vTaskDelayUntil(&xLastWakeTime, 2000);

				/* see the left IR if no obstacle move backward and return left */
				if (THERE_NO_OBSTACLE == LeftFront_IR_Status)
				{
					MoveLeft(40);
					vTaskDelayUntil(&xLastWakeTime, 300);
				}
				/* see the right IR if no obstacle move backward and return right */
				else if (THERE_NO_OBSTACLE == RightFront_IR_Status)
				{
					MoveRight(40);
					vTaskDelayUntil(&xLastWakeTime, 300);
				}
				/* Obstacle in both ways return 180 degree */
				else
				{


					if (THERE_NO_OBSTACLE == Left_IR_Status)
					{
						MoveLeft(40);
						vTaskDelayUntil(&xLastWakeTime, 300);
					}
					/* see the right IR if no obstacle move backward and return right */
					else if (THERE_NO_OBSTACLE == Right_IR_Status)
					{
						MoveRight(40);
						vTaskDelayUntil(&xLastWakeTime, 300);
					}
					/* Obstacle in both ways return 180 degree */
					else
					{
						MoveLeft(40);
						vTaskDelayUntil(&xLastWakeTime, 800);
					}
				}
				CarStop();
				vTaskDelayUntil(&xLastWakeTime, 500);
			}



			/* there is no OBSTACLE in front of the car */
			if (MIN_DIS_TO_STOP <= Distance)
			{
				MoveForward(speed);
			}

			else
			{
				CarStop();
				vTaskDelayUntil(&xLastWakeTime, 2000);
				/* see the left IR if no obstacle move backward and return left */
				if (THERE_NO_OBSTACLE == Left_IR_Status)
				{
					MoveLeft(40);
					vTaskDelayUntil(&xLastWakeTime, 300);
				}
				/* see the right IR if no obstacle move backward and return right */
				else if (THERE_NO_OBSTACLE == Right_IR_Status)
				{
					MoveRight(40);
					vTaskDelayUntil(&xLastWakeTime, 300);
				}
				/* Obstacle in both ways return 180 degree */
				else
				{
					MoveLeft(40);
					vTaskDelayUntil(&xLastWakeTime, 800);
				}

				CarStop();
				vTaskDelayUntil(&xLastWakeTime, 500);
			}
		}


		vTaskDelayUntil(&xLastWakeTime, 20);

	}
}




/* RGB ShowRoom task */
static void RGB_task_handler(void*parameters)
{
	portTickType xLastWakeTime;
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	RGB_Color_type Color = RED + 1;
	RGB_Color_type Prev_Color = RED;
	RGB_Status status;
	while(1)
	{
		/* Get status for RGB */
		status =  RGB_ShowRoomStatus();
		/* If it done start new colors */
		if (status == RGB_DONE)
		{
			RGB_ShowRoomSetColors(Prev_Color, Color);
			Prev_Color = Color;
			Color++;
		}


		RGB_ShowRoom_Runnable();

		/* If color Ends start again */
		if (Color == COLOR_NUM)
		{
			Color = 0;
		}


		vTaskDelayUntil(&xLastWakeTime, 20);
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

	/* Initialization of UDS */
	UDS_voidInit();

	/* Status of creating task */
	BaseType_t status;

	/* Create the task, storing the handle. */

	/* UDS Task */
	status = xTaskCreate(UDS_task_handler, NULL, 2000, NULL, 4, NULL);
	configASSERT(status == pdPASS);

	/* RGB ShowRoom task */
	status = xTaskCreate(RGB_task_handler, NULL, 500, NULL, 3, NULL);
	configASSERT(status == pdPASS);

	/* Obstacle avoidance Operating task */
	status = xTaskCreate(AvoidObstacles_task_handler, NULL, 500, NULL, 2, NULL);
	configASSERT(status == pdPASS);

	/* Obstacle avoidance Read update from sensor task */
	status = xTaskCreate(AvoidObstaclesRead_task_handler, NULL, 500, NULL, 1, NULL);
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
	MOTOR_Speed_dir(M1, Copy_u8Speed , M_CCW);
	MOTOR_Speed_dir(M2, Copy_u8Speed , M_CCW);

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




/* For Debugging */
static void WriteNumber_4D(u32 num)
{
	//LCD_WriteChar(((num%100000)/10000)+'0');
	MUART6_voidTransmitSynch(((num%10000)/1000)+'0');
	MUART6_voidTransmitSynch(((num%1000)/100)+'0');
	MUART6_voidTransmitSynch(((num%100)/10)+'0');
	MUART6_voidTransmitSynch(((num%10)/1)+'0');
	MUART6_voidTransmitSynch('\n');
}




