/*****************************************************************/
/* Author  : Mina2                                               */
/* Layer   : MCAL                                                */
/* SWC     : MUART                                               */
/* Version : 1.0                                                 */
/* Date    : 19 Sep 2023                                         */
/*****************************************************************/
#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"
#include "../include/MUART_Interface.h"
#include "../include/MUART_Private.h"
#include "../include/MUART_Config.h"


static void (*MUART1_ptr)(void) = NULLPTR;
static void (*MUART2_ptr)(void) = NULLPTR;
static void (*MUART6_ptr)(void) = NULLPTR;



void MUART1_voidInit(UART_BaudRate_t Copy_enuBaudRate)
{
	/* HSI --> 16MHz  Baud Rate --> 9600 */
	UART_1->BRR = Copy_enuBaudRate;
	/* over sampling --> 16 */
	UART_1->CR1.OVER8 = 0;
	/* word length 8 Bit */
	UART_1->CR1.M = 0;

	/* Parity */
	UART_1->CR1.PCE = GET_BIT(UART1_PARTY, 1);
	UART_1->CR1.PS = GET_BIT(UART1_PARTY, 0);;


	/* Stop bits */


	(UART_1->CR2) &= STOP_BIT_MASK;
	(UART_1->CR2) |= (UART1_STOP << 12) ;


}





void MUART1_voidTransmitFrameSynch(u8 *Copy_u8Data,u8 Copy_u8Length)
{
	u8 Copy_u8Counter;
	for(Copy_u8Counter = 0;Copy_u8Counter < Copy_u8Length; Copy_u8Counter++)
	{
		UART_1->DR =Copy_u8Data[Copy_u8Counter];
		while(UART_1->SR_B.TC == 0);
	}
}



void MUART1_voidTransmitSynch(u8 Copy_u8Data)
{
	while (UART_1->SR_B.TC == 0);
	UART_1->DR = Copy_u8Data;


}


u8 MUART1_u8ReceiveSynch(void)
{
	while(UART_1->SR_B.RXNE == 0);
	return (u8)UART_1->DR;
}


void MUART1_voidTransmitNoBlock(u8 Copy_u8Data)
{
	UART_1->DR = Copy_u8Data;

}


u8 MUART1_u8ReciveNoBlock(void)
{
	return (u8)UART_1->DR;
}






void MUART1_EnableTX(void)
{
	// Enable transmit
	UART_1->CR1.TE = 1;
}

void MUART1_EnableRX(void)
{
	// Enable receive
	UART_1->CR1.RE = 1;
}

void MUART1_voidEnable(void)
{
	UART_1->CR1.UE = 1;
}
void MUART1_voidDisable(void)
{
	UART_1->CR1.UE = 0;
}




void MUART1_voidRxInterruptEnable(void)
{
	/* Receive interrupt enable */
	UART_1->CR1.RXNEIE = 1;
	UART_1->SR = 0;
}


void MUART1_voidTxInterruptEnable(void)
{
	/* Transmitter interrupt enable */
	UART_1->CR1.TCIE = 1;
	UART_1->SR = 0;
}



void MUART1_voidRxInterruptDisable(void)
{
	/* Receive interrupt Disable */
	UART_1->CR1.RXNEIE = 0;

}


void MUART1_voidTxInterruptDisable(void)
{
	/* Transmitter interrupt Disable */
	UART_1->CR1.TCIE = 0;

}







void MUART1_voidCallBack(void(*ptr)(void))
{
	if(ptr != NULLPTR)
	{
		MUART1_ptr = ptr;
	}
	else
	{
		/* Do Nothing */
	}
}



void USART1_IRQHandler(void)
{
	UART_1->SR = 0;
	if(MUART1_ptr !=NULLPTR)
	{
		MUART1_ptr();
	}
	else
	{
		/* Do Nothing */
	}



}

/*********************************************************************************************/
/************************************ UART 2 *************************************************/
/*********************************************************************************************/



void MUART2_voidInit(UART_BaudRate_t Copy_enuBaudRate)
{
	/* HSI --> 16MHz  Baud Rate --> 9600 */
	UART_2->BRR = Copy_enuBaudRate;
	/* over sampling --> 16 */
	UART_2->CR1.OVER8 = 0;
	/* word length 8 Bit */
	UART_2->CR1.M = 0;

	/* Parity */
	UART_2->CR1.PCE = GET_BIT(UART2_PARTY, 1);
	UART_2->CR1.PS = GET_BIT(UART2_PARTY, 0);


	/* Stop bits */
	(UART_2->CR2) &= STOP_BIT_MASK;
	(UART_2->CR2) |= (UART2_STOP << 12) ;

}



void MUART2_EnableTX(void)
{
	// Enable transmit
	UART_2->CR1.TE = 1;
}

void MUART2_EnableRX(void)
{
	// Enable receive
	UART_2->CR1.RE = 1;
}


void MUART2_voidTransmitFrameSynch(u8 *Copy_u8Data,u8 Copy_u8Length)
{
	u8 Copy_u8Counter;
	for(Copy_u8Counter = 0;Copy_u8Counter < Copy_u8Length; Copy_u8Counter++)
	{
		UART_2->DR =Copy_u8Data[Copy_u8Counter];
		while(UART_2->SR_B.TC == 0);
	}
}



void MUART2_voidTransmitSynch(u8 Copy_u8Data)
{
	while (UART_2->SR_B.TC == 0);
	UART_2->DR = Copy_u8Data;


}


u8 MUART2_u8ReceiveSynch(void)
{
	while(UART_2->SR_B.RXNE == 0);
	return (u8)UART_2->DR;
}


void MUART2_voidTransmitNoBlock(u8 Copy_u8Data)
{
	UART_2->DR = Copy_u8Data;

}


u8 MUART2_u8ReciveNoBlock(void)
{
	return (u8)UART_2->DR;
}




void MUART2_voidEnable(void)
{
	UART_2->CR1.UE = 1;
}
void MUART2_voidDisable(void)
{
	UART_2->CR1.UE = 0;
}


void MUART2_voidRxInterruptEnable(void)
{
	/* Receive interrupt enable */
	UART_2->CR1.RXNEIE = 1;
	UART_2->SR = 0;
}

void MUART2_voidTxInterruptEnable(void)
{
	/* Transmitter interrupt enable */
	UART_2->CR1.TCIE = 1;
	UART_2->SR = 0;
}



void MUART2_voidRxInterruptDisable(void)
{
	/* Receive interrupt Disable */
	UART_2->CR1.RXNEIE = 0;
}


void MUART2_voidTxInterruptDisable(void)
{
	/* Transmitter interrupt Disable */
	UART_2->CR1.TCIE = 0;
}

void MUART2_voidCallBack(void(*ptr)(void))
{
	if(ptr != NULLPTR)
	{
		MUART2_ptr = ptr;
	}
	else
	{
		/* Do Nothing */
	}
}

void USART2_IRQHandler(void)
{
	UART_2->SR = 0;
	if(MUART2_ptr !=NULLPTR)
	{
		MUART2_ptr();
	}
	else
	{
		/* Do Nothing */
	}



}




/*********************************************************************************************/
/************************************ UART 6 *************************************************/
/*********************************************************************************************/

void MUART6_voidInit(UART_BaudRate_t Copy_enuBaudRate)
{
	/* HSI --> 16MHz  Baud Rate --> 9600 */
	UART_6->BRR = Copy_enuBaudRate;
	/* over sampling --> 16 */
	UART_6->CR1.OVER8 = 0;
	/* word length 8 Bit */
	UART_6->CR1.M = 0;

	/* Parity */
	UART_6->CR1.PCE = GET_BIT(UART1_PARTY, 1);
	UART_6->CR1.PS = GET_BIT(UART1_PARTY, 0);;


	/* Stop bits */


	(UART_6->CR2) &= STOP_BIT_MASK;
	(UART_6->CR2) |= (UART1_STOP << 12) ;


}





void MUART6_voidTransmitFrameSynch(u8 *Copy_u8Data,u8 Copy_u8Length)
{
	u8 Copy_u8Counter;
	for(Copy_u8Counter = 0;Copy_u8Counter < Copy_u8Length; Copy_u8Counter++)
	{
		UART_6->DR =Copy_u8Data[Copy_u8Counter];
		while(UART_6->SR_B.TC == 0);
	}
}



void MUART6_voidTransmitSynch(u8 Copy_u8Data)
{
	while (UART_6->SR_B.TC == 0);
	UART_6->DR = Copy_u8Data;


}


u8 MUART6_u8ReceiveSynch(void)
{
	while(UART_6->SR_B.RXNE == 0);
	return (u8)UART_6->DR;
}


void MUART6_voidTransmitNoBlock(u8 Copy_u8Data)
{
	UART_6->DR = Copy_u8Data;

}


u8 MUART6_u8ReciveNoBlock(void)
{
	if (UART_6->SR_B.RXNE == 1)
	{
		return (u8)UART_6->DR;
	}
	else
	{
		return 0;
	}

}






void MUART6_EnableTX(void)
{
	// Enable transmit
	UART_6->CR1.TE = 1;
}

void MUART6_EnableRX(void)
{
	// Enable receive
	UART_6->CR1.RE = 1;
}

void MUART6_voidEnable(void)
{
	UART_6->CR1.UE = 1;
}
void MUART6_voidDisable(void)
{
	UART_6->CR1.UE = 0;
}




void MUART6_voidRxInterruptEnable(void)
{
	/* Receive interrupt enable */
	UART_6->CR1.RXNEIE = 1;
	UART_6->SR = 0;
}


void MUART6_voidTxInterruptEnable(void)
{
	/* Transmitter interrupt enable */
	UART_6->CR1.TCIE = 1;
	UART_6->SR = 0;
}



void MUART6_voidRxInterruptDisable(void)
{
	/* Receive interrupt Disable */
	UART_6->CR1.RXNEIE = 0;

}


void MUART6_voidTxInterruptDisable(void)
{
	/* Transmitter interrupt Disable */
	UART_6->CR1.TCIE = 0;

}







void MUART6_voidCallBack(void(*ptr)(void))
{
	if(ptr != NULLPTR)
	{
		MUART6_ptr = ptr;
	}
	else
	{
		/* Do Nothing */
	}
}



void USART6_IRQHandler(void)
{
	UART_6->SR = 0;
	if(MUART6_ptr !=NULLPTR)
	{
		MUART6_ptr();
	}
	else
	{
		/* Do Nothing */
	}



}
