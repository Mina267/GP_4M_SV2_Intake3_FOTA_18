/************************************************************************/
/*	Author		:	Abanoub Kamal                                       */
/* 	Version		:	V01													*/
/*	Date		: 	4 April 2021										*/
/************************************************************************/
#ifndef TIM_CONFIG_H
#define TIM_CONFIG_H


/* 	to control in counter Clock (CNT_CLK) of TIM3
 * this timer used for execute a function after a specific time,
 * get elapsed time, get remaining time... (for apps used the forground system (interrupts) )
 * so that the value of TIM3_PRESCALER will affect the max and min time used in these functions.
 * 	CNT_CLK  = TIMx_CLK / TIM3_PRESCALER
 * 	TIMx_CLK = APB1_CLK 		if (APBx_PRESCALER  = 1)
 * 	TIMx_CLK = APB1_CLK *2		if (APBx_PRESCALER != 1)
 *
	options	:		1 ~ 65535								*/
#define TIM3_PRESCALER			16000



/*	to choose between generation or read PWM by TIM4
 * options	:		TIM4_READ_PWM
 * 					TIM4_GENERATE_PWM						*/
#define TIM4_USAGE				TIM4_GENERATE_PWM


/* 	to control in counter Clock (CNT_CLK) of TIM4
 * 	CNT_CLK  = TIMx_CLK / TIM4_PRESCALER
 * 	TIMx_CLK = APBx_CLK 		if (APBx_PRESCALER  = 1)
 * 	TIMx_CLK = APBx_CLK *2		if (APBx_PRESCALER != 1)
 * 																*/
#if   TIM4_USAGE == TIM4_READ_PWM
	/*	options	:		1 ~ 65535
	 * 															*/
	#define TIM4_PRESCALER			5000
	/*	options :		calculate as shown in upper notation
	 * 															*/
	#define TIM4_CNT_CLK			1600

#elif TIM4_USAGE == TIM4_GENERATE_PWM
	/*	options	:		1 ~ 65535
	 * 															*/
	#define TIM4_PRESCALER			80								// for CNT_CLK = 10 KHz
	/*	options :		calculate as shown in upper notation
	 * 															*/
	#define TIM4_CNT_CLK			100000

#endif




/* 	to control in counter Clock (CNT_CLK) of TIM1
 * 	CNT_CLK  = TIMx_CLK / TIM4_PRESCALER
 * 	TIMx_CLK = APB2_CLK 		if (APBx_PRESCALER  = 1)
 * 	TIMx_CLK = APB2_CLK *2		if (APBx_PRESCALER != 1)
 *
	options	:		1 ~ 65535								*/
#define TIM1_PRESCALER			5000

/*	options :		calculate as shown in upper notation 	*/
#define TIM1_CNT_CLK			1600


#endif
