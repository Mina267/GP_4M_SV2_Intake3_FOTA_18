/************************************************************************************/
/*	Author		:	Abanoub Kamal                                       			*/
/* 	Version		:	V01																*/
/*	Date		: 	4 April 2021													*/
/* 	Notes		:	# all our timers are 16 bits counter
					# we use TIM2 for busy wait, and our calculation is depend on
					  AHB CLK =8MHz and so APB CLK = 8MHz
					# we use TIM3 for Asynchronous functions
					  (execute a function after a specific time only once,
					   execute a function periodically every a specific time,
					    )
					# we use TIM4 for generate PWM and read PWM
					# we use TIM1 for read Ton Period (specially used for UltraSonic)

					# TIM1 No remap (ETR/PA12, CH1/PA8, CH2/PA9, CH3/PA10, CH4/PA11, BKIN/PB12,
					  	  	  	  	  CH1N/PB13, CH2N/PB14, CH3N/PB15)
					# TIM2 No remap (CH1/ETR/PA0, CH2/PA1, CH3/PA2, CH4/PA3)
					# TIM3 No remap (CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1)
					# TIM4 No remap (TIM4_CH1/PB6, TIM4_CH2/PB7, TIM4_CH3/PB8, TIM4_CH4/PB9)
					*/
/************************************************************************************/
#ifndef TIM_INTERFACE_H
#define TIM_INTERFACE_H


/* Macros */
#define TIM4_CHANNEL_1		0
#define TIM4_CHANNEL_2		1
#define TIM4_CHANNEL_3		2
#define TIM4_CHANNEL_4		3


/***********************************************************************
 * Description: synchronous function. using TIM2.
 *				stuck the processor for time equal number of ms.
 *
 * Inputs     :	Copy_u32MsNumber		range		: 1 ~ (2^32)
 *										description : number of ms
 * return     :	void
 * scope      :	public
 **********************************************************************/
void MTIM2_voidSetBusyWaitMs(u32 Copy_u32MsNumber);

/***********************************************************************
 * Description: synchronous function. using TIM2.
 *				stuck the processor for time equal number of ms.
 *				this function give accurate delay with ms
 *
 * Inputs     :	Copy_u32MsNumber		range		: 1 ~ 8000
 *										description : number of ms
 * return     :	void
 * scope      :	public
 **********************************************************************/
void MTIM2_voidSetBusyWaitAccurateMs(u32 Copy_u32MsNumber);

/***********************************************************************
 * Description: synchronous function. using TIM2.
 *				stuck the processor for time equal number of us.
 *
 * Inputs     :	Copy_u32UsNumber		range		: 1 ~ 30000
 *										description : number of us
 * return     :	void
 * scope      :	public
 **********************************************************************/
void MTIM2_voidSetBusyWaitUs(u32 Copy_u32UsNumber);

/***********************************************************************
 * Description: Asynchronous function. using TIM3.
 *				this function take function name to execute it after a time
 *				interval equal (tick time * time of one tick)
 *
 * Inputs     :	Copy_32Ticks				range		: 0 ~ (65535)
 *											description : number of ticks
 *
 * 				void (*Copy_ptr)(void)		value	: function name
 * return     :	void
 * scope      :	public
 **********************************************************************/
void MTIM3_voidSetIntervalSingle(u16 Copy_16Ticks , void (*Copy_ptr)(void) );

/***********************************************************************
 * Description: Asynchronous function. using TIM3.
 *				this function take function name to execute it after a time
 *				interval equal (tick time * time of one tick) periodically.
 *
 * Inputs     :	Copy_32Ticks				range		: 0 ~ (65535)
 *											description : number of ticks
 *
 * 				void (*Copy_ptr)(void)		value	: function name
 * return     :	void
 * scope      :	public
 **********************************************************************/
void MTIM3_voidSetIntervalPeriodic(u16 Copy_16Ticks , void (*Copy_ptr)(void) );

/***********************************************************************
 * Description: to fined the time consumed since the timer 3 start counting
 *				using TIM3.
 *
 * Inputs     :	void
 * return     :	u16							description : number of ticks counted
 * 														  after the timer started
 * scope      :	public
 **********************************************************************/
u16 MTIM3_u16GetElapsedTime(void);

/***********************************************************************
 * Description: to find the time remaining till the timer 3 firing interrupt
 *				and do something. using TIM3.
 *
 * Inputs     :	void
 * return     :	u16							description : number of ticks to be counted
 * 														  till the timer firing interrupt
 * scope      :	public
 **********************************************************************/
u16 MTIM3_u16GetRemainingTime(void);

/***********************************************************************
 * Description: this function to stop the timer 3
 *				and lock its interrupt. using TIM3.
 *				
 * Inputs     :	void
 * return     :	void
 * scope      :	public
 **********************************************************************/
void MTIM3_voidStopInterval(void);

/***********************************************************************
 * Description: #these two functions to measure the Time On signal
 * 				#we use the first one in initialization part from the code before while(1),
 * 				 and the second one used inside the app ( inside while(1) ).
 * 				#the first return ( from MTIM1_f32Ch1Ch2MeasureTonPeriod ) is not correct.
 * 				but after first return it will return correct Time.
 *
 * 				#HardWare connection ----> PA8
 *
 * Inputs     :	void
 * return     :	f32
 * scope      :	public
 **********************************************************************/
void MTIM1_f32Ch1Ch2InitMeasureTonPeriod(void);
f32 MTIM1_f32Ch1Ch2MeasureTonPeriod(void);

/***********************************************************************
 * Description: #these two functions to measure the frequency of PWM signal
 * 				#we use the first one in initialization part from the code before while(1),
 * 				 and the second one used inside the app ( inside while(1) ).
 * 				#the first return ( from MTIM4_f32Ch1MeasurePWM ) is not correct as
 * 				 the timer counter start count in initialization part and we call it
 * 				 after a time. but after first return it will return correct frequency.
 *
 * Inputs     :	void
 * return     :	f32
 * scope      :	public
 **********************************************************************/
void MTIM4_f32Ch1InitMeasurePWM(void);
f32 MTIM4_f32Ch1MeasurePWM(void);

/***********************************************************************
 * Description: # this function use TIM4 to generate PWM on its channels
 *				# TIM4 No remap (TIM4_CH1/PB6, TIM4_CH2/PB7, TIM4_CH3/PB8, TIM4_CH4/PB9)
 *
 * Inputs     :	Copy_f32Period				range		: you must take care for that expression:
 * 														  >>>>>>> (Copy_f32Period * TIM4_CNT_CLK) < 65535 <<<<<<
 * 														  TIM4_CNT_CLK exist in config file
 *
 *
 * 				Copy_f32DutySycle			value		: if   you want to enter 5%
 * 														  then value = 5
 *
 * 				Copy_u8Channel				options		: TIM4_CHANNEL_1
 * 														  TIM4_CHANNEL_2
 * 														  TIM4_CHANNEL_3
 * 														  TIM4_CHANNEL_4
 * return     :	void
 * scope      :	public
 **********************************************************************/
void MTIM4_voidSetPWM(f32 Copy_f32Period , f32 Copy_f32DutySycle , u8 Copy_u8Channel);



#endif
