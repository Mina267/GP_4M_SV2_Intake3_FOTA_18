/*****************************************************************/
/* Author  : Mina Magdy                                          */
/* Layer   : MCAL                                                */
/* SWC     : MRCC                                                */
/* Version : 2.0                                                 */
/* Date    : 09 Sep 2023                                         */
/*****************************************************************/
 #ifndef MRCC_INTERFACE_H_
#define MRCC_INTERFACE_H_

/* Buses */

#define RCC_APB1			0
#define RCC_APB2			1
#define RCC_AHB1			2
#define RCC_AHB2			3


/************************ APB1 ******************************/

/* Register Bits */
#define RCC_APB1_TIM2		0
#define RCC_APB1_TIM3		1
#define RCC_APB1_TIM4		2
#define RCC_APB1_TIN5		3
#define RCC_APB1_WWDG		11
#define RCC_APB1_SPI2		14
#define RCC_APB1_SPI3		15
#define RCC_APB1_USART2		17
#define RCC_APB1_12C1		21
#define RCC_APB1_12C2		22
#define RCC_APB1_12C3		23
#define RCC_APB1_PWR		28

/************************ APB2 ******************************/

/* Register Bits */
#define RCC_APB2_TIM1		0
#define RCC_APB2_USART1		4
#define RCC_APB2_USART6		5
#define RCC_APB2_ADC1		8
#define RCC_APB2_SDIO		11
#define RCC_APB2_SPI1		12
#define RCC_APB2_SPI4		13
#define RCC_APB2_SYSCFG		14
#define RCC_APB2_TIM9		16
#define RCC_APB2_TIM10		17
#define RCC_APB2_TIM11		18

/************************ AHB1 ******************************/

/* Register Bits */
#define RCC_AHB1_GPIOA		0
#define RCC_AHB1_GPIOB		1
#define RCC_AHB1_GPIOC		2
#define RCC_AHB1_GPIOD		3
#define RCC_AHB1_GPIOE		4
#define RCC_AHB1_GPIOH		7
#define RCC_AHB1_CRCRST		12
#define RCC_AHB1_DMA1		21
#define RCC_AHB1_DMA2		22


/************************ AHB2 ******************************/

/* Register Bits */
#define RCC_AHB2_OTGFS		7

typedef enum
{
	MRCC_HSI,
	MRCC_HSE
}MRCC_PLLSource_t;

/* Initialization
 * Select which clock system will operate with HSI, HSE, or PLL
 * ON/OFF HSI, HSE, PLL
 * For Selection PLL Choose PLL Source -> HSI OR HSE
 * And Choosing The Multiplication Factor For PLL
 * For HSE Enable/Disable bypass the oscillator with an external clock.
 * AHB clock prescaler factor.
 * APB Low-speed prescaler.
 * APB high-speed prescaler.
 * Enable/Disable Microcontroller clock output at MCO pins.
 * Enable/Disable Clock Security System
 * choose Provide an additional user-programmable trimming value that is added to the
 */
void MRCC_voidInit( void );

/* Peripheral Clock Enable
 * Take as an argument Bus and Peripheral want to enable a clock on it
 */
void MRCC_voidEnable_Peripheral(u32 Copy_u32Address_Bus ,u32 Copy_u32Peripheral);

/* Peripheral Clock Enable
 * Take as an argument Bus and Peripheral want to enable a clock on it
 */
void MRCC_voidDisable_Peripheral(u32 Copy_u32Address_Bus ,u32 Copy_u32Peripheral);
/*
 * Convert to PLL Source in Running time.
 * Select if source is HSE or HSI.
 * f(VCO clock) = (f(VCO clock) / PLLP) * (PLLN / PLLM)
 */
void MRCC_voidStartOfPLL(MRCC_PLLSource_t Copy_enuInputClock, u16 Copy_u8PLLP, u16 Copy_u8PLLN, u16 Copy_u8PLLM);
/*
 * Convert to HSE Source in Running time as system clock source.
 * Operate for RCC or crystal as configuration.
 */
void MRCC_voidStartOfHSE(void);
/*
 * Convert to HSI Source in Running time as system clock source.
 */
void MRCC_voidStartOfHSI(void);
#endif

















