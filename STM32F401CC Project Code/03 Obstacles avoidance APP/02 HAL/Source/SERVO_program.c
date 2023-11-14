/************************************************************************/
/*	Author		:	Mina Magdy		                                    */
/* 	Version		:	V01													*/
/*	Date		: 	20 oct 2023	 		     							*/
/************************************************************************/
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"
#include "../include/SERVO_interface.h"
#include "../include/SERVO_private.h"
#include "../include/SERVO_config.h"

#include "../include/TIM_interface.h"
#include "../include/TIM_config.h"
#include "../include/TIM_private.h"


void HSERVO_viodSetServoAngle(u8 Copy_u8Angle , u8 Copy_u8Channel )
{
	/* this equation comes from manual calibrating */
	f32 Local_f32DutyCycle = (Copy_u8Angle / 18.0) + 2.5 ;

	MTIM4_voidSetPWM( SERVO_PERIOD , Local_f32DutyCycle , Copy_u8Channel );
}


void HSERVO_viodSetServoAngleHighResolution(u32 Copy_u8Angle , u8 Copy_u8Channel )
{
	/* this equation comes from manual calibrating */
	f32 Local_f32DutyCycle = (Copy_u8Angle / 180.0) + 2.5 ;

	MTIM4_voidSetPWM( SERVO_PERIOD , Local_f32DutyCycle , Copy_u8Channel );
}
