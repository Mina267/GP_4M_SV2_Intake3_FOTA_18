/*****************************************************************/
/* Author  : Mina Magdy                                          */
/* Layer   : MCAL                                                */
/* SWC     : MNVIC                                               */
/* Version : 1.0                                                 */
/* Date    : 11 Sep 2023                                         */
/*****************************************************************/
#ifndef MNVIC_INTERFACE_H_
#define MNVIC_INTERFACE_H_


/* Group Selection */
typedef enum
{
	GROUP16_SUB0 = 3,
	GROUP8_SUB2,
	GROUP4_SUB4,
	GROUP2_SUB8,
	GROUP0_SUB16

}MNVIC_Group_t;


/* Enable/Disable Selection */
typedef enum
{
	NVIC_DISABLE,
	NVIC_ENABLE,
	NVIC_RESERVED

}MNVIC_Enable_t;

typedef enum
{
	NVIC_WWDG               = 0,
	NVIC_EXTI16             = 1,
	NVIC_EXTI21             = 2,
	NVIC_EXTI22             = 3,
	NVIC_FLASH              = 4,
	NVIC_RCC                = 5,
	NVIC_EXTI0              = 6,
	NVIC_EXTI1              = 7,
	NVIC_EXTI2              = 8,
	NVIC_EXTI3              = 9,
	NVIC_EXTI4              = 10,
	NVIC_DMA1_Stream0       = 11,
	NVIC_DMA1_Stream1       = 12,
	NVIC_DMA1_Stream2       = 13,
	NVIC_DMA1_Stream3       = 14,
	NVIC_DMA1_Stream4       = 15,
	NVIC_DMA1_Stream5       = 16,
	NVIC_DMA1_Stream6       = 17,
	NVIC_ADC                = 18,
	NVIC_EXTI9_5            = 23,
	NVIC_TIM1_BRK_TIM9      = 24,
	NVIC_TIM1_UP_TIM10      = 25,
	NVIC_TIM1_TRG_COM_TIM11 = 26,
	NVIC_TIM1_CC            = 27,
	NVIC_TIM2               = 28,
	NVIC_TIM3               = 29,
	NVIC_TIM4               = 30,
	NVIC_I2C1_EV            = 31,
	NVIC_I2C1_ER            = 32,
	NVIC_I2C2_EV            = 33,
	NVIC_I2C2_ER            = 34,
	NVIC_SPI1               = 35,
	NVIC_SPI2               = 36,
	NVIC_USART1             = 37,
	NVIC_USART2             = 38,
	NVIC_EXTI15_10          = 40,
	NVIC_EXTI17             = 41,
	NVIC_EXTI18             = 42,
	NVIC_DMA1_Stream7       = 47,
	NVIC_SDIO               = 49,
	NVIC_TIM5               = 50,
	NVIC_SPI3               = 51,
	NVIC_DMA2_Stream0       = 56,
	NVIC_DMA2_Stream1       = 57,
	NVIC_DMA2_Stream2       = 58,
	NVIC_DMA2_Stream3       = 59,
	NVIC_DMA2_Stream4       = 60,
	NVIC_OTG_FS             = 67,
	NVIC_DMA2_Stream5       = 68,
	NVIC_DMA2_Stream6       = 69,
	NVIC_DMA2_Stream7       = 70,
	NVIC_USART6             = 71,
	NVIC_I2C3_EV            = 72,
	NVIC_I2C3_ER            = 73,
	NVIC_FPU                = 81,
	NVIC_SPI4               = 84
}NVIC_Position_t;

/* Initialization of NVIC
 * Enable of Configuration interrupts
 */
void MNVIC_voidInit(void);
/* Enable interrupt of Selected Peripheral */
void MNVIC_voidEnableInterrupt(u8 Copy_u8IntPos);
/* Disable interrupt of Selected Peripheral */
void MNVIC_voidDisableInterrupt(u8 Copy_u8IntPos);
/* Enable of Pending Flag on Selected Peripheral */
void MNVIC_voidEnableInterruptPending(u8 Copy_u8IntPos);
/* Disable of Pending Flag on Selected Peripheral */
void MNVIC_voidDisableInterruptPending(u8 Copy_u8IntPos);
/* Read Active Flag for selected peripheral */
void MNVIC_voidIsInterruptAvtive(u8 Copy_u8IntPos, u8* Copy_pu8Read);
/* Select which grouping mode system NVIC priority will operate */
void MVIC_voidSetInterruptGroupMode(MNVIC_Group_t Copy_enuGroupMode);
/* Set to external peripheral Group and sub group priority */
void MVIC_voidSetInterruptGroupMode(MNVIC_Group_t Copy_enuGroupMode);
/* Set to external peripheral Group and sub group priority */
void MVIC_voidSetInterruptPriorty(u8 Copy_u8IntPos, u8 Copy_u8GroupnNum, u8 Copy_u8SubGroupnNum);

#endif
