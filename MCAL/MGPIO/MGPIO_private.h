/*****************************************************************/
/* Author  : Mina Magdy                                               */
/* Layer   : MCAL                                                */
/* SWC     : MGPIO                                               */
/* Version : 1.0                                                 */
/* Date    : 09 Sep 2023                                         */
/*****************************************************************/
#ifndef MGPIO_PRIVATE_H_
#define MGPIO_PRIVATE_H_




/* GPIO Start Base address */
#define GPIOA_BASE_ADDRSS					(0x40020000)
#define GPIOB_BASE_ADDRSS					(0x40020400)
#define GPIOC_BASE_ADDRSS					(0x40020800)

/* GPIO register map */
typedef struct
{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIOX_t;




/* pointer to struct of type RCC_t point to Base address of RCC Peripheral */
#define GPIOA								((volatile GPIOX_t*)GPIOA_BASE_ADDRSS)
#define GPIOB								((volatile GPIOX_t*)GPIOB_BASE_ADDRSS)
#define GPIOC								((volatile GPIOX_t*)GPIOC_BASE_ADDRSS)

/* GPIO Mask For Configuration */
#define GPIO_MODE_MASK						((u32)0b11)
#define GPIO_OTYPE_MASK						((u32)0b1)
#define ALTERNATIVE_MASK					((u32)0b1111)


#define  OPENDRAIN_ENU_OFFSET				4
#define PORTB_DEBUG_PINS					3
#define PORTB_PINS_OFFSET					2
#define PORTC_PIN13							13
#define PORTC_PIN15							15

/* Private Function For initialization of GPIO Pin */
static void SetPinMode(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinOperateMode_t Copy_enuOperateMode);

/* Configuration Array for Ports initialization */
extern const GPIO_PinOperateMode_t GPIOA_Pins_Array[GPIOA_PINS_MAX];
extern const GPIO_PinOperateMode_t GPIOB_Pins_Array[GPIOB_PINS_MAX];
extern const GPIO_PinOperateMode_t GPIOC_Pins_Array[GPIOC_PINS_MAX];


#define GPIO_DISABLE						0
#define GPIO_ENABLE							1

#endif
