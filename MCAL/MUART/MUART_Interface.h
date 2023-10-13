/*****************************************************************/
/* Author  : Mina2                                               */
/* Layer   : MCAL                                                */
/* SWC     : MUART                                               */
/* Version : 1.0                                                 */
/* Date    : 19 Sep 2023                                         */
/*****************************************************************/
#ifndef MUART_INTERFACE_H_
#define MUART_INTERFACE_H_



typedef enum
{
	BAUD_RATE_2400_  =    (0x1A0B),
	BAUD_RATE_9600_  =    (0x683),
	BAUD_RATE_19200_ =    (0x341),
	BAUD_RATE_38400_ =    (0x1A1),
	BAUD_RATE_57600_ =    (0x396)
}UART_BaudRate_t;

/*********************************************************************************************/
/************************************ UART 1 *************************************************/
/*********************************************************************************************/
void MUART1_voidInit(UART_BaudRate_t Copy_enuBaudRate);
void MUART1_voidTransmitFrameSynch(u8 *Copy_u8Data,u8 Copy_u8Length);
void MUART1_voidTransmitSynch(u8 Copy_u8Data);
u8 MUART1_u8ReceiveSynch(void);
void MUART1_voidTransmitNoBlock(u8 Copy_u8Data);
u8 MUART1_u8ReciveNoBlock(void);
void MUART1_voidEnable(void);
void MUART1_voidDiable(void);
void MUART1_EnableRX(void);
void MUART1_EnableTX(void);
void MUART1_voidCallBack(void(*ptr)(void));
void MUART1_voidRxInterruptEnable(void);
void MUART1_voidTxInterruptEnable(void);
void MUART1_voidRxInterruptDisable(void);
void MUART1_voidTxInterruptDisable(void);

/*********************************************************************************************/
/************************************ UART 2 *************************************************/
/*********************************************************************************************/

void MUART2_voidInit(UART_BaudRate_t Copy_enuBaudRate);
void MUART2_voidTransmitFrameSynch(u8 *Copy_u8Data,u8 Copy_u8Length);
void MUART2_voidTransmitSynch(u8 Copy_u8Data);
u8 MUART2_u8ReceiveSynch(void);
void MUART2_voidTransmitNoBlock(u8 Copy_u8Data);
u8 MUART2_u8ReciveNoBlock(void);
void MUART2_voidEnable(void);
void MUART2_voidDiable(void);
void MUART2_EnableRX(void);
void MUART2_EnableTX(void);
void MUART2_voidCallBack(void(*ptr)(void));
void MUART2_voidRxInterruptEnable(void);
void MUART2_voidTxInterruptEnable(void);
void MUART2_voidRxInterruptDisable(void);
void MUART2_voidTxInterruptDisable(void);





#endif
