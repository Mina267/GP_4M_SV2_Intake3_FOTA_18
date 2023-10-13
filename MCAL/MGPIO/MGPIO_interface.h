/*****************************************************************/
/* Author  : Mina Magdy                                               */
/* Layer   : MCAL                                                */
/* SWC     : MGPIO                                               */
/* Version : 1.0                                                 */
/* Date    : 09 Sep 2023                                         */
/*****************************************************************/
#ifndef MGPIO_INTERFACE_H_
#define MGPIO_INTERFACE_H_

typedef enum
{
	PORTA = 0,
	PORTB,
	PORTC
}GPIO_Port_t;


typedef enum
{
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,
}GPIO_Pin_t;

typedef enum
{
	INPUT = 0,
	OUTPUT,
	AT_FUNC,
	ANALOG
}GPIO_PinMode_t;

typedef enum
{
	PUSHPULL = 0,
	OPENDRAIN
}GPIO_PinOutMode_t;

typedef enum
{
	LOW_SPEED_8MHZ_ = 0,
	MEDIUM_SPEED_50MHZ_,
	HIGH_SPEED_80MHZ,
	VERY_HIGH_SPEED_180MHZ
}GPIO_PinSpeed_t;

typedef enum
{
	INFREE = 0,
	PULLUP,
	PULLDOWN
}GPIO_PinInputMode_t;


typedef enum
{
	LOW,
	HIGH
}GPIO_PinValue_t;

/* initialization Ports Enum */
typedef enum
{
	OUT_PUSHPULL_8MHZ_ = 0,
	OUT_PUSHPULL_50MHZ_,
	OUT_PUSHPULL_80MHZ_,
	OUT_PUSHPULL_180MHZ_,
	OUT_OPENDRAIN_8MHZ,
	OUT_OPENDRAIN_50MHZ_,
	OUT_OPENDRAIN_80MHZ_,
	OUT_OPENDRAIN_180MHZ_,
	AF_PUSHPULL_8MHZ_,
	AF_PUSHPULL_50MHZ_,
	AF_PUSHPULL_80MHZ_,
	AF_PUSHPULL_180MHZ_,
	AF_OPENDRAIN_8MHZ,
	AF_OPENDRAIN_50MHZ_,
	AF_OPENDRAIN_80MHZ_,
	AF_OPENDRAIN_180MHZ_,
	IN_FREE,
	IN_PULLUP,
	IN_PULLDOWN,
	AF_FREE,
	AF_PULLUP,
	AF_PULLDOWN
}GPIO_PinOperateMode_t;



typedef enum
{
	SYSTEM		= 0b0000,
	TIM1_TIM2,
	TIM3_5,
	TIM9_11,
	I2C1_3,
	SPI1_4,
	SPI3,
	USART1_2,
	USART6,
	I2C2_3,
	OTG_FS,
	GPIO_RES1,
	SDIO,
	GPIO_RES2,
	GPIO_RES3,
	EVENTOUT
}GPIO_AF_t;

/* initialization of GPIO Ports
 * Should Enable Clock of GPIO peripheral from RCC First
 */
void MGPIO_Init(void);
/* Set Pins Operation Mode */
void MGPIO_SetMode(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinMode_t Copy_enuMode);
/* Set GPIO Pin outPut Mode and Pin Speed */
void MGPIO_SetOutPutPinMode(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinOutMode_t Copy_enuOutMode, GPIO_PinSpeed_t Copy_enuSpeed);
/* Set GPIO Pin Input Mode */
void MGPIO_SetInputPinMode(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinInputMode_t Copy_enuInPutMode);
/* Toggle OutPut Pin from HIGH to LOW and vis versa */
void MGPIO_TogglePin(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin);
/* Get GPIO Pin Value */
GPIO_PinValue_t MGPIO_GetPinValue(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin);
/* Get GPIO Pin Value */
void MGPIO_GetPinValue2(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinValue_t *Copy_enuValue);
/* Set GPIO OutPut Pin to HIGH or LOW */
GPIO_PinValue_t MGPIO_GetPinValue(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin);
/* Set and Reset Pin Value to high and Low with atomic Access */
void MGPIO_SetResetValue(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinValue_t Copy_enuValue);

#include "../include/STD_Types.h"

void MGPIO_SetGroupValue(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuStartPin, GPIO_Pin_t Copy_enuEndPin, u32 Copy_u32Value);

void MGPIO_SetAlternativeFuncPin(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_AF_t Copy_enuData);

void MGPIO_SetPinValue(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinValue_t Copy_enuValue);





#endif
