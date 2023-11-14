/************************************************************************/
/*	Author		:	Mina Magdy		                                    */
/* 	Version		:	V01													*/
/*	Date		: 	20 oct 2023	 		     							*/
/************************************************************************/


#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_


#define TIM4_CHANNEL_1			0
#define TIM4_CHANNEL_2			1
#define TIM4_CHANNEL_3			2
#define TIM4_CHANNEL_4			3

/* Macros */
#define SERVO_CHANNEL_1				TIM4_CHANNEL_1
#define SERVO_CHANNEL_2 			TIM4_CHANNEL_2
#define SERVO_CHANNEL_3 			TIM4_CHANNEL_3
#define SERVO_CHANNEL_4 			TIM4_CHANNEL_4

/***************************************************************************
 * 						HardWare connection
 *
 * 	TIM4 No remap (
 * 					SERVO_CHANNEL_1  -----> TIM4_CHANNEL_1 ( PB6 ),
 * 					SERVO_CHANNEL_2  -----> TIM4_CHANNEL_2 ( PB7 ),
 * 					SERVO_CHANNEL_3  -----> TIM4_CHANNEL_3 ( PB8 ),
 * 					SERVO_CHANNEL_4  -----> TIM4_CHANNEL_4 ( PB9 )
 */
/***************************************************************************
						steps needed in main
	
	1) enable clock of the processor
	2) enable clock of PORTB
	3) enable clock of alternative function
	4) enable clock of timer4 for PWM
	5) set the pin configuration as AFIO (alternative function)
	6) Enable the INT for TIM4
	7) setup the priority of TIM4
	
*/
/***************************************************************************
 * Description: # this function use TIM4 to generate PWM on its channels (we can use 4 Channels)
 * 					to control on servomotor angele
 *				# periodecity of this function mustn't exceed 20ms
					means you can not call this function more than one time every 20ms
 *
 * Inputs     :	Copy_u8Angle				value		: 0 ~ 180
 *
 * 				Copy_u8Channel				options		: SERVO_CHANNEL_1
 * 														  SERVO_CHANNEL_2
 * 														  SERVO_CHANNEL_3
 * 														  SERVO_CHANNEL_4
 * return     :	void
 * scope      :	public
 **********************************************************************/
void HSERVO_viodSetServoAngle(u8 Copy_u8Angle , u8 Copy_u8Channel );

void HSERVO_viodSetServoAngleHighResolution(u32 Copy_u8Angle , u8 Copy_u8Channel );

#endif /* SERVOMOTOR_INTERFACE_H_ */
