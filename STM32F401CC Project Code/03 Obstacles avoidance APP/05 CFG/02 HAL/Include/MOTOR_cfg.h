
#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_


#define  NUMBER_MOTORS   4

/******************PIN config ***********************************/


#define   M1_IN1_PIN		PIN13
#define   M1_IN1_PORT		PORTB
#define   M1_IN2_PIN        PIN14
#define   M1_IN2_PORT       PORTB
#define   M1_EN_PIN			PIN0
#define   M1_EN_PORT        PORTA

#define   M2_IN1_PIN		PIN12
#define   M2_IN1_PORT       PORTB
#define   M2_IN2_PIN		PIN2
#define   M2_IN2_PORT       PORTA
#define   M2_EN_PIN			PIN0
#define   M2_EN_PORT        PORTA

#define   M3_IN1_PIN		PIN0
#define   M3_IN1_PORT       PORTA
#define   M3_IN2_PIN		PIN0
#define   M3_IN2_PORT       PORTA
#define   M3_EN_PIN			PIN0
#define   M3_EN_PORT        PORTA

#define   M4_IN1_PIN		PIN0
#define   M4_IN1_PORT       PORTA
#define   M4_IN2_PIN		PIN0
#define   M4_IN2_PORT       PORTA
#define   M4_EN_PIN			PIN0
#define   M4_EN_PORT        PORTA





#define M1_PWM_CHANNEL		TIM5_CHANNEL_1
#define M2_PWM_CHANNEL 		TIM5_CHANNEL_2
#define M3_PWM_CHANNEL 		TIM5_CHANNEL_3
#define M4_PWM_CHANNEL 		TIM5_CHANNEL_4



#endif /* MOTOR_CFG_H_ */
