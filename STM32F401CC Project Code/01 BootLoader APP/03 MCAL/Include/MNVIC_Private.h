/*****************************************************************/
/* Author  : Mina Magdy                                          */
/* Layer   : MCAL                                                */
/* SWC     : MNVIC                                               */
/* Version : 1.0                                                 */
/* Date    : 11 Sep 2023                                         */
/*****************************************************************/
#ifndef MNVIC_PRIVATE_H_
#define MNVIC_PRIVATE_H_

/* NVIC Start Base address */
#define NVIC_BASE_ADDRSS					(0xE000E100)

/* SCB Start Base address */
#define SCB_BASE_ADDRSS						(0xE000ED00)

/* NVIC register map */
typedef struct
{
	volatile u32 ISER[8];
	volatile u32 RESERVED1[24];
	volatile u32 ICER[8];
	volatile u32 RESERVED2[24];
	volatile u32 ISPR[8];
	volatile u32 RESERVED3[24];
	volatile u32 ICPR[8];
	volatile u32 RESERVED4[24];
	volatile u32 IAPR[8];
	volatile u32 RESERVED5[56];
	volatile u8 IPR[240];
	volatile u32 RESERVED6[580];
	volatile u32 STIR;
}NVIC_t;


//SCB
typedef struct{

	volatile u32 CPUID;
	volatile u32 ICSR;
	volatile u32 VTOR;
	volatile u32 AIRCR;
	volatile u32 SCR;
	volatile u32 CCR;
	volatile u32 SHPR1;
	volatile u32 SHPR2;
	volatile u32 SHPR3;
	volatile u32 SHCSR;
	volatile u32 CFSR;
	volatile u32 HFSR;
	volatile u32 RESERVED;
	volatile u32 MMFAR;
	volatile u32 BFAR;

}SCB_Type;

#define SCB ((volatile SCB_Type *) SCB_BASE_ADDRSS)

/* pointer to struct of type NVIC_t point to Base address of NVIC Peripheral */
#define NVIC								((volatile NVIC_t*)NVIC_BASE_ADDRSS)
/* Application interrupt and reset control register */
#define SCB_AIRCR							(*((volatile u32*) 0xE000ED00 + 0x0C))		/* APP Interrupt and reset control */
/* The Key of Application interrupt and reset control register */
#define VECTKEY								0x5FA0000


#define MAX_INTERUPT_NUM	240
#define REG_DIV				32

/* Interrupt Enable/Disable configuration Array */
extern const MNVIC_Enable_t NVIC_PerEnable_Arr[NVIC_MAX_NUM];

#endif
