#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/MGPIO_interface.h"
#include "../include/TIM_interface.h"


#include "../include/MOTOR_interface.h"
#include "../include/MOTOR_cfg.h"
#include "../include/MOTOR_private.h"


void MOTOR_Init(void)
{
	//MGPIO_SetPinValue(MotorPinsArray[M1][EN], HIGH);
	//MGPIO_SetPinValue(MotorPinsArray[M2][EN], HIGH);
	//MGPIO_SetPinValue(MotorPinsArray[M3][EN], HIGH);
	//MGPIO_SetPinValue(MotorPinsArray[M4][EN], HIGH);
	/* Channel 1*/
	MGPIO_SetAlternativeFuncPin(PORTA, PIN0, TIM3_5);
	/* Channel 2*/
	MGPIO_SetAlternativeFuncPin(PORTA, PIN1, TIM3_5);

}



Error_type MOTOR_Stop(MOTOR_type motor)
{
	Error_type ErrorStatus = OK;
	if (motor > NUMBER_MOTORS)
	{
		ErrorStatus = OUT_OF_RANGE;
	}
	else
	{
		MGPIO_SetPinValue(MotorPinsArray[motor][IN1][M_PORT], MotorPinsArray[motor][IN1][M_PIN], LOW);
		MGPIO_SetPinValue(MotorPinsArray[motor][IN2][M_PORT], MotorPinsArray[motor][IN2][M_PIN], LOW);
	}
	return ErrorStatus;
}

Error_type MOTOR_CW(MOTOR_type motor)
{
	Error_type ErrorStatus = OK;
	if (motor > NUMBER_MOTORS)
	{
		ErrorStatus = OUT_OF_RANGE;
	}
	else
	{
		MGPIO_SetPinValue(MotorPinsArray[motor][IN1][M_PORT], MotorPinsArray[motor][IN1][M_PIN], HIGH);
		MGPIO_SetPinValue(MotorPinsArray[motor][IN2][M_PORT], MotorPinsArray[motor][IN2][M_PIN], LOW);
	}
	return ErrorStatus;


}
Error_type MOTOR_CCW(MOTOR_type motor)
{
	Error_type ErrorStatus = OK;
	if (motor > NUMBER_MOTORS)
	{
		ErrorStatus = OUT_OF_RANGE;
	}
	else
	{
		MGPIO_SetPinValue(MotorPinsArray[motor][IN1][M_PORT], MotorPinsArray[motor][IN1][M_PIN], LOW);
		MGPIO_SetPinValue(MotorPinsArray[motor][IN2][M_PORT], MotorPinsArray[motor][IN2][M_PIN], HIGH);
	}
	return ErrorStatus;
}

/*  speed from 0 to 100  %**/
void MOTOR_Speed(MOTOR_type motor,u8 speed)
{
	switch (motor)
	{
	case M1:
		MTIM5_voidSetPWM(M_FREQ, speed, M1_PWM_CHANNEL);
		break;

	case M2:
		MTIM5_voidSetPWM(M_FREQ, speed, M2_PWM_CHANNEL);
		break;

	case M3:
		MTIM5_voidSetPWM(M_FREQ, speed, M3_PWM_CHANNEL);
		break;

	case M4:
		MTIM5_voidSetPWM(M_FREQ, speed, M4_PWM_CHANNEL);
		break;
	}

}
#include "../include/MGPIO_interface.h"

void MOTOR_Speed_dir(MOTOR_type motor,u8 speed , Direction_status status)
{

	switch (motor)
	{
	case M1:
		MTIM5_voidSetPWM(M_FREQ, speed, M1_PWM_CHANNEL);
		break;

	case M2:
		MTIM5_voidSetPWM(M_FREQ, speed, M2_PWM_CHANNEL);
		break;

	case M3:
		MTIM5_voidSetPWM(M_FREQ, speed, M3_PWM_CHANNEL);
		break;

	case M4:
		MTIM5_voidSetPWM(M_FREQ, speed, M4_PWM_CHANNEL);
		break;
	}


	switch (status)
	{
	case M_CW:


		MGPIO_SetPinValue(MotorPinsArray[motor][IN1][M_PORT], MotorPinsArray[motor][IN1][M_PIN], HIGH);
		MGPIO_SetPinValue(MotorPinsArray[motor][IN2][M_PORT], MotorPinsArray[motor][IN2][M_PIN], LOW);

		break;
	case M_CCW:
		MGPIO_SetPinValue(MotorPinsArray[motor][IN1][M_PORT], MotorPinsArray[motor][IN1][M_PIN], LOW);
		MGPIO_SetPinValue(MotorPinsArray[motor][IN2][M_PORT], MotorPinsArray[motor][IN2][M_PIN], HIGH);
		break;
	case M_STOP:
		MGPIO_SetPinValue(MotorPinsArray[motor][IN1][M_PORT], MotorPinsArray[motor][IN1][M_PIN], LOW);
		MGPIO_SetPinValue(MotorPinsArray[motor][IN2][M_PORT], MotorPinsArray[motor][IN2][M_PIN], LOW);
		break;
	}


}


void MOTOR_dir(MOTOR_type motor, Direction_status status)
{
	switch (status)
	{
	case M_CW:
		MGPIO_SetPinValue(MotorPinsArray[motor][IN1][M_PORT], MotorPinsArray[motor][IN1][M_PIN], HIGH);
		MGPIO_SetPinValue(MotorPinsArray[motor][IN2][M_PORT], MotorPinsArray[motor][IN2][M_PIN], LOW);
		break;
	case M_CCW:
		MGPIO_SetPinValue(MotorPinsArray[motor][IN1][M_PORT], MotorPinsArray[motor][IN1][M_PIN], LOW);
		MGPIO_SetPinValue(MotorPinsArray[motor][IN2][M_PORT], MotorPinsArray[motor][IN2][M_PIN], HIGH);
		break;
	case M_STOP:
		MGPIO_SetPinValue(MotorPinsArray[motor][IN1][M_PORT], MotorPinsArray[motor][IN1][M_PIN], LOW);
		MGPIO_SetPinValue(MotorPinsArray[motor][IN2][M_PORT], MotorPinsArray[motor][IN2][M_PIN], LOW);
		break;
	}
}
