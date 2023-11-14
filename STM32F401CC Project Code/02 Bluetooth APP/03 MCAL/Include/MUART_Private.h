/*****************************************************************/
/* Author  : Mina2                                               */
/* Layer   : MCAL                                                */
/* SWC     : MUART                                               */
/* Version : 1.0                                                 */
/* Date    : 19 Sep 2023                                         */
/*****************************************************************/
#ifndef MUART_PRIVATE_H_
#define MUART_PRIVATE_H_



/* UART Start Base address */
#define UART1_BASE_ADDRSS					(0x40011000)
#define UART6_BASE_ADDRSS					(0x40011400)
#define UART2_BASE_ADDRSS					(0x40004400)


typedef struct
{
	u32 SBK			:1;
	u32 RWU			:1;
	u32 RE			:1;
	u32 TE			:1;
	u32 IDKEIE		:1;
	u32 RXNEIE		:1;
	u32 TCIE		:1;
	u32 TXEIE		:1;
	u32 PEIE		:1;
	u32 PS			:1;
	u32 PCE			:1;
	u32 WAKE		:1;
	u32 M			:1;
	u32 UE			:1;
	u32 RESERVED0	:1;
	u32 OVER8		:1;
	u32 RESERVED1	:16;

}MUART_CR1;


typedef struct
{
	u32 PE			:1;
	u32 FE			:1;
	u32 NF			:1;
	u32 ORE			:1;
	u32 IDLE		:1;
	u32 RXNE		:1;
	u32 TC			:1;
	u32 TXE			:1;
	u32 LBD			:1;
	u32 CTS			:1;
	u32 RESERVED1	:22;

}MUART_SR;

typedef struct
{
	union
	{
		u32 SR;
		MUART_SR SR_B;
	};

	u32 DR;
	u32 BRR;
	MUART_CR1 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;
}MUART_t;

#define UART_1 				((volatile MUART_t *)UART1_BASE_ADDRSS)
#define UART_2 				((volatile MUART_t *)UART2_BASE_ADDRSS)
#define UART_6 				((volatile MUART_t *)UART6_BASE_ADDRSS)


#define NO_PARIY      	 	(0b00)
#define EVEN_PARITY   	 	(0b10)
#define ODD_PARITY     		(0b11)

#define STOP_BIT_MASK		(0xFFFFCFFF)
#define	 ONE_STOP			(0b00)
#define	 TWO_STOP			(0b10)



/* BRR Bits */
#define BRR_DIV_FRACTION0				0
#define BRR_DIV_MANTISSA0				4

/* CR2 Bits */
#define CR2_STOP0						12

/* SR Bits */
#define SR_RXNE							5
#define SR_TC							6



#endif
