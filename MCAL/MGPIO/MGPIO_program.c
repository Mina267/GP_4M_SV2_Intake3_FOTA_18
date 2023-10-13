/*****************************************************************/
/* Author  : Mina Magdy                                               */
/* Layer   : MCAL                                                */
/* SWC     : MGPIO                                               */
/* Version : 1.0                                                 */
/* Date    : 09 Sep 2023                                         */
/*****************************************************************/


#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"
#include "../include/MGPIO_interface.h"
#include "../include/MGPIO_config.h"
#include "../include/MGPIO_private.h"



/* initialization of GPIO Ports
 * Should Enable Clock of GPIO peripheral from RCC First
 */
void MGPIO_Init(void)
{
#if (GPIOA_PORT_INIT_ENABLE == GPIO_ENABLE)
	u8 Local_u8Pinb_offset;
	/* initialization Of PORT A */
	for (u16 PinIndex = 0; PinIndex < GPIOA_PINS_MAX; PinIndex++)
	{
		/* Set Pin operating mode */
		SetPinMode(PORTA, PinIndex, GPIOA_Pins_Array[PinIndex]);
	}
#endif

#if (GPIOB_PORT_INIT_ENABLE == GPIO_ENABLE)
	/* initialization Of PORT B */
	for (u16 PinIndex = 0; PinIndex < GPIOB_PINS_MAX; PinIndex++)
	{
		/* Check for Debugging pins offset in Configuration Array */
		if (PinIndex >= PORTB_DEBUG_PINS)
		{
			Local_u8Pinb_offset = PinIndex + PORTB_PINS_OFFSET;
		}
		else
		{
			Local_u8Pinb_offset = PinIndex;
		}
		/* Set Pin operating mode */
		SetPinMode(PORTB, Local_u8Pinb_offset, GPIOB_Pins_Array[PinIndex]);
	}
#endif

#if (GPIOC_PORT_INIT_ENABLE == GPIO_ENABLE)

	/* initialization Of PORT C */
	for (u16 PinIndex = PORTC_PIN13; PinIndex < PORTC_PIN15; PinIndex++)
	{
		/* Set Pin operating mode */
		SetPinMode(PORTC, PinIndex, GPIOB_Pins_Array[PinIndex]);
	}

#endif

}

/* Set Pins Operation Mode */
void MGPIO_SetMode(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinMode_t Copy_enuMode)
{
	/* Ignore Debugging Pins of MCU */
	if ((Copy_enuPort == PORTA) && ((Copy_enuPin == PIN13) || (Copy_enuPin == PIN14) || (Copy_enuPin == PIN15)))
	{
		/* Return Error */
	}
	else if ((Copy_enuPort == PORTB) && ((Copy_enuPin == PIN3) || (Copy_enuPin == PIN4)))
	{
		/* Return Error */
	}
	else
	{
		/* Switching on PORTS to Set Pin Mode */
		switch(Copy_enuPort)
		{
		case PORTA:
			GPIOA->MODER &= ~(GPIO_MODE_MASK << (Copy_enuPin * 2)); /* Clear Mode Bits */
			GPIOA->MODER |= (Copy_enuMode) << (Copy_enuPin * 2);	/* Set Mode Bits Value */
			break;

		case PORTB:
			GPIOB->MODER &= ~(GPIO_MODE_MASK << (Copy_enuPin * 2));  /* Clear Mode Bits */
			GPIOB->MODER |= (Copy_enuMode) << (Copy_enuPin * 2);     /* Set Mode Bits Value */
			break;

		case PORTC:
			GPIOC->MODER &= ~(GPIO_MODE_MASK << (Copy_enuPin * 2));  /* Clear Mode Bits */
			GPIOC->MODER |= (Copy_enuMode) << (Copy_enuPin * 2);     /* Set Mode Bits Value */
			break;

		default:
			break;
		}
	}

}


/* Set GPIO Pin outPut Mode and Pin Speed */
void MGPIO_SetOutPutPinMode(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinOutMode_t Copy_enuOutMode, GPIO_PinSpeed_t Copy_enuSpeed)
{
	/* Ignore Debugging Pins of MCU */
	if ((Copy_enuPort == PORTA) && ((Copy_enuPin == PIN13) || (Copy_enuPin == PIN14) || (Copy_enuPin == PIN15)))
	{

	}
	else if ((Copy_enuPort == PORTB) && ((Copy_enuPin == PIN3) || (Copy_enuPin == PIN4)))
	{

	}
	else
	{
		/* Switching on PORTS to Set Pin out Put Mode and Pin Speed */
		switch(Copy_enuPort)
		{
		case PORTA:
			GPIOA->OTYPER &= ~(GPIO_OTYPE_MASK << (Copy_enuPin));		/* Clear outPut Mode Bit */
			GPIOA->OTYPER |= (Copy_enuOutMode << (Copy_enuPin));        /* Set outPut Mode Bit Value */
			GPIOA->OSPEEDR &= ~(GPIO_MODE_MASK << (Copy_enuPin * 2));   /* Clear outPut Speed Bits */
			GPIOA->OSPEEDR |= (Copy_enuSpeed) << (Copy_enuPin * 2);     /* Set outPut speed Bits Value */
			break;

		case PORTB:
			GPIOB->OTYPER &= ~(1 << (Copy_enuPin));                     /* Clear outPut Mode Bit */
			GPIOB->OTYPER |= (Copy_enuOutMode << (Copy_enuPin));        /* Set outPut Mode Bit Value */
			GPIOB->OSPEEDR &= ~(GPIO_MODE_MASK << (Copy_enuPin * 2));   /* Clear outPut Speed Bits */
			GPIOB->OSPEEDR |= (Copy_enuSpeed) << (Copy_enuPin * 2);     /* Set outPut speed Bits Value */
			break;

		case PORTC:
			GPIOC->OTYPER &= ~(1 << (Copy_enuPin));                     /* Clear outPut Mode Bit */
			GPIOC->OTYPER |= (Copy_enuOutMode << (Copy_enuPin));        /* Set outPut Mode Bit Value */
			GPIOC->OSPEEDR &= ~(GPIO_MODE_MASK << (Copy_enuPin * 2));   /* Clear outPut Speed Bits */
			GPIOC->OSPEEDR |= (Copy_enuSpeed) << (Copy_enuPin * 2);     /* Set outPut speed Bits Value */
			break;

		default:
			break;
		}
	}

}

/* Set GPIO Pin Input Mode */
void MGPIO_SetInputPinMode(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinInputMode_t Copy_enuInPutMode)
{
	/* Ignore Debugging Pins of MCU */
	if ((Copy_enuPort == PORTA) && ((Copy_enuPin == PIN13) || (Copy_enuPin == PIN14) || (Copy_enuPin == PIN15)))
	{
		/* Return Error */
	}
	else if ((Copy_enuPort == PORTB) && ((Copy_enuPin == PIN3) || (Copy_enuPin == PIN4)))
	{
		/* Return Error */
	}
	else
	{
		/* Switching on PORTS to Set Pin Input Mode */
		switch(Copy_enuPort)
		{
		case PORTA:
			GPIOA->PUPDR &= ~(GPIO_MODE_MASK << (Copy_enuPin * 2));      /* Clear Input Mode Bit */
			GPIOA->PUPDR |= (Copy_enuInPutMode) << (Copy_enuPin * 2);    /* Set Input Mode Bit Value */
			break;

		case PORTB:
			GPIOB->PUPDR &= ~(GPIO_MODE_MASK << (Copy_enuPin * 2));      /* Clear Input Mode Bit */
			GPIOB->PUPDR |= (Copy_enuInPutMode) << (Copy_enuPin * 2);    /* Set Input Mode Bit Value */
			break;

		case PORTC:
			GPIOC->PUPDR &= ~(GPIO_MODE_MASK << (Copy_enuPin * 2));      /* Clear Input Mode Bit */
			GPIOC->PUPDR |= (Copy_enuInPutMode) << (Copy_enuPin * 2);    /* Set Input Mode Bit Value */
			break;

		default:
			break;
		}
	}

}

/* Get GPIO Pin Value */
void MGPIO_GetPinValue2(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinValue_t *Copy_enuValue)
{
	/* Ignore Debugging Pins of MCU */
	if ((Copy_enuPort == PORTA) && ((Copy_enuPin == PIN13) || (Copy_enuPin == PIN14) || (Copy_enuPin == PIN15)))
	{
		/* Return Error */
	}
	else if ((Copy_enuPort == PORTB) && ((Copy_enuPin == PIN3) || (Copy_enuPin == PIN4)))
	{
		/* Return Error */
	}
	else
	{
		/* Switching on PORTS to Get Pin Mode */
		switch(Copy_enuPort)
		{
		case PORTA:
			*Copy_enuValue = GET_BIT(GPIOA->IDR, Copy_enuPin);	/* Get Pin Status value Bit from PORTA */
			break;

		case PORTB:
			*Copy_enuValue = GET_BIT(GPIOB->IDR, Copy_enuPin);  /* Get Pin Status value Bit from PORTB */
			break;

		case PORTC:
			*Copy_enuValue = GET_BIT(GPIOC->IDR, Copy_enuPin);	/* Get Pin Status value Bit from PORTC */
			break;

		default:
			break;
		}
	}
}


/* Get GPIO Pin Value */
GPIO_PinValue_t MGPIO_GetPinValue(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin)
{
	GPIO_PinValue_t Local_enuValue = LOW;

	/* Ignore Debugging Pins of MCU */
	if ((Copy_enuPort == PORTA) && ((Copy_enuPin == PIN13) || (Copy_enuPin == PIN14) || (Copy_enuPin == PIN15)))
	{
		/* Return Error */
	}
	else if ((Copy_enuPort == PORTB) && ((Copy_enuPin == PIN3) || (Copy_enuPin == PIN4)))
	{
		/* Return Error */
	}
	else
	{
		/* Switching on PORTS to Get Pin Mode */
		switch(Copy_enuPort)
		{
		case PORTA:
			Local_enuValue = GET_BIT(GPIOA->IDR, Copy_enuPin);	/* Get Pin Status value Bit from PORTA */
			break;

		case PORTB:
			Local_enuValue = GET_BIT(GPIOB->IDR, Copy_enuPin);  /* Get Pin Status value Bit from PORTB */
			break;

		case PORTC:
			Local_enuValue = GET_BIT(GPIOC->IDR, Copy_enuPin);	/* Get Pin Status value Bit from PORTC */
			break;

		default:
			break;
		}
	}

	return Local_enuValue;
}

/* Set GPIO OutPut Pin to HIGH or LOW */
void MGPIO_SetPinValue(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinValue_t Copy_enuValue)
{
	/* Ignore Debugging Pins of MCU */
	if ((Copy_enuPort == PORTA) && ((Copy_enuPin == PIN13) || (Copy_enuPin == PIN14) || (Copy_enuPin == PIN15)))
	{
		/* Return Error */
	}
	else if ((Copy_enuPort == PORTB) && ((Copy_enuPin == PIN3) || (Copy_enuPin == PIN4)))
	{
		/* Return Error */
	}
	else
	{
		/* Switching on PORTS to Set Pin value */
		switch(Copy_enuPort)
		{
		case PORTA:
			WRITE_BIT(GPIOA->ODR, Copy_enuPin, Copy_enuValue);	/* write on pin high or low as Input argument */

			break;

		case PORTB:
			WRITE_BIT(GPIOB->ODR, Copy_enuPin, Copy_enuValue);	/* write on pin high or low as Input argument */
			break;

		case PORTC:
			WRITE_BIT(GPIOC->ODR, Copy_enuPin, Copy_enuValue);	/* write on pin high or low as Input argument */
			break;

		default:
			break;
		}
	}
}

/* Toggle OutPut Pin from HIGH to LOW and vis versa */
void MGPIO_TogglePin(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin)
{
	/* Ignore Debugging Pins of MCU */
	if ((Copy_enuPort == PORTA) && ((Copy_enuPin == PIN13) || (Copy_enuPin == PIN14) || (Copy_enuPin == PIN15)))
	{
		/* Return Error */
	}
	else if ((Copy_enuPort == PORTB) && ((Copy_enuPin == PIN3) || (Copy_enuPin == PIN4)))
	{
		/* Return Error */
	}
	else
	{
		/* Switching on PORTS to toggle Pin */
		switch(Copy_enuPort)
		{
		case PORTA:
			TOG_BIT(GPIOA->ODR, Copy_enuPin);	/* Toggle on pin from high to low and vis versa */

			break;

		case PORTB:
			TOG_BIT(GPIOB->ODR, Copy_enuPin);	/* Toggle on pin from high to low and vis versa */
			break;

		case PORTC:
			TOG_BIT(GPIOC->ODR, Copy_enuPin);	/* Toggle on pin from high to low and vis versa */
			break;

		default:
			break;
		}
	}
}

/* Set and Reset Pin Value to high and Low with atomic Access */
void MGPIO_SetResetValue(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinValue_t Copy_enuValue)
{
	/* Ignore Debugging Pins of MCU */
	if ((Copy_enuPort == PORTA) && ((Copy_enuPin == PIN13) || (Copy_enuPin == PIN14) || (Copy_enuPin == PIN15)))
	{
		/* Return Error */
	}
	else if ((Copy_enuPort == PORTB) && ((Copy_enuPin == PIN3) || (Copy_enuPin == PIN4)))
	{
		/* Return Error */
	}
	else
	{
		if (Copy_enuValue == HIGH)
		{
			/* Switching on PORTS to Set Pin High */
			switch(Copy_enuPort)
			{
			case PORTA:
				GPIOA->BSRR = 1 << Copy_enuPin;		/* Set output pin to high */
				break;

			case PORTB:
				GPIOB->BSRR = 1 << Copy_enuPin;		/* Set output pin to high */
				break;

			case PORTC:
				GPIOC->BSRR = 1 << Copy_enuPin;		/* Set output pin to high */
				break;

			default:
				break;
			}
		}
		else if (Copy_enuValue == LOW)
		{
			Copy_enuPin += 16;
			/* Switching on PORTS to Set Pin low */
			switch(Copy_enuPort)
			{
			case PORTA:
				GPIOA->BSRR = 1 << Copy_enuPin; 	/* Set output pin to low */
				break;

			case PORTB:
				GPIOB->BSRR = 1 << Copy_enuPin;		/* Set output pin to low */
				break;

			case PORTC:
				GPIOC->BSRR = 1 << Copy_enuPin;		/* Set output pin to low */
				break;

			default:
				break;
			}
		}
		else
		{
			/* Return Error */
		}

	}

}



/* Private Function For initialization of GPIO Pin */
static void SetPinMode(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_PinOperateMode_t Copy_enuOperateMode)
{
	/* Check if Pin is Input Or OutPut */
	if (Copy_enuOperateMode <= AF_OPENDRAIN_180MHZ_)
	{
		if (Copy_enuOperateMode <= OUT_OPENDRAIN_180MHZ_)
		{
			/* Set PIN As output */
			MGPIO_SetMode(Copy_enuPort, Copy_enuPin, OUTPUT);
			/* Check if PIN Push pull or open drain */
			if (Copy_enuOperateMode <= OUT_PUSHPULL_180MHZ_)
			{
				MGPIO_SetOutPutPinMode(Copy_enuPort, Copy_enuPin, PUSHPULL, Copy_enuOperateMode);
			}
			else if (Copy_enuOperateMode <= OUT_OPENDRAIN_180MHZ_)
			{
				MGPIO_SetOutPutPinMode(Copy_enuPort, Copy_enuPin, OPENDRAIN, Copy_enuOperateMode - OPENDRAIN_ENU_OFFSET);
			}
		}
		else
		{
			/* Set PIN As output */
			MGPIO_SetMode(Copy_enuPort, Copy_enuPin, AT_FUNC);
			/* Check if PIN Push pull or open drain */
			if (Copy_enuOperateMode <= AF_PUSHPULL_180MHZ_)
			{
				MGPIO_SetOutPutPinMode(Copy_enuPort, Copy_enuPin, PUSHPULL, Copy_enuOperateMode - 8);
			}
			else if (Copy_enuOperateMode <= AF_OPENDRAIN_180MHZ_)
			{
				MGPIO_SetOutPutPinMode(Copy_enuPort, Copy_enuPin, OPENDRAIN, Copy_enuOperateMode - OPENDRAIN_ENU_OFFSET - 12);
			}
		}

	}
	else
	{
		/* Set PIN As Input */
		if (Copy_enuOperateMode <= IN_PULLDOWN)
		{
			MGPIO_SetMode(Copy_enuPort, Copy_enuPin, INPUT);
		}
		/* Set PIN As Alternative Function */
		else
		{
			MGPIO_SetMode(Copy_enuPort, Copy_enuPin, AT_FUNC);
		}

		/* Switch or witch mode of output */
		switch (Copy_enuOperateMode)
		{
		case IN_FREE:
			MGPIO_SetInputPinMode(Copy_enuPort, Copy_enuPin, INFREE);
			break;

		case IN_PULLUP:
			MGPIO_SetInputPinMode(Copy_enuPort, Copy_enuPin, PULLUP);
			break;

		case IN_PULLDOWN:
			MGPIO_SetInputPinMode(Copy_enuPort, Copy_enuPin, PULLDOWN);
			break;
		default:
			/* Return Error */
			break;
		}
	}
}



void MGPIO_SetGroupValue(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuStartPin, GPIO_Pin_t Copy_enuEndPin, u32 Copy_u32Value)
{
	u8 Index = 0;
	for (u8 PIN_Index = Copy_enuStartPin; PIN_Index <= Copy_enuEndPin; PIN_Index++)
	{
		MGPIO_SetResetValue(Copy_enuPort, PIN_Index, GET_BIT(Copy_u32Value, Index));
		Index++;
	}
}



void MGPIO_SetAlternativeFuncPin(GPIO_Port_t Copy_enuPort, GPIO_Pin_t Copy_enuPin, GPIO_AF_t Copy_enuData)
{
	if(Copy_enuPort == PORTA && (Copy_enuPin == PIN13 || Copy_enuPin == 14 || Copy_enuPin == 15))
	{
		/* Do Nothing */
	}
	else if(Copy_enuPort == PORTB && (Copy_enuPin == PIN3 || Copy_enuPin == 4))
	{
		/* Do Nothing */
	}
	else
	{
		switch (Copy_enuPort) {
		case PORTA:
			if(Copy_enuPin <= 7)
			{
				GPIOA->AFRL &= ~(ALTERNATIVE_MASK << (Copy_enuPin * 4));
				GPIOA->AFRL |= (Copy_enuData << (Copy_enuPin * 4));
			}
			else
			{
				GPIOA->AFRH &= ~(ALTERNATIVE_MASK << ((Copy_enuPin - 8) * 4));
				GPIOA->AFRH |= (Copy_enuData << ((Copy_enuPin-8) * 4));
			}
			break;
		case PORTB:
			if(Copy_enuPin<=7)
			{
				GPIOB->AFRL &= ~(ALTERNATIVE_MASK<< (Copy_enuPin * 4));
				GPIOB->AFRL |= (Copy_enuData << (Copy_enuPin * 4));
			}
			else
			{
				GPIOB->AFRH &= ~(ALTERNATIVE_MASK << ((Copy_enuPin - 8) * 4));
				GPIOB->AFRH |= (Copy_enuData << ((Copy_enuPin - 8) * 4));
			}
			break;
		case PORTC:
			if(Copy_enuPin<=7)
			{
				GPIOC->AFRL &= ~(ALTERNATIVE_MASK << (Copy_enuPin*4));
				GPIOC->AFRL |= (Copy_enuData << (Copy_enuPin * 4));
			}
			else
			{
				GPIOC->AFRH &= ~(ALTERNATIVE_MASK << ((Copy_enuPin-8) * 4));
				GPIOC->AFRH |= (Copy_enuData << ((Copy_enuPin - 8) * 4));
			}
			break;
		default:
			break;
		}
	}
}

