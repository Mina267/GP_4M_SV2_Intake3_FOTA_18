/*****************************************************************/
/* Author  : Mina Magdy                                          */
/* Layer   : MCAL                                                */
/* SWC     : MNVIC                                               */
/* Version : 1.0                                                 */
/* Date    : 11 Sep 2023                                         */
/*****************************************************************/
#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"
#include "../include/MNVIC_interface.h"
#include "../include/MNVIC_config.h"
#include "../include/MNVIC_private.h"



static MNVIC_Group_t Global_enuPRI;




/* Initialization of NVIC
 * Enable of Configuration interrupts
 */
void MNVIC_voidInit(void)
{
	NVIC_Position_t Per_Index;
	for (Per_Index = NVIC_WWDG; Per_Index <= NVIC_SPI4; Per_Index++)
	{
		/* Enable interrupt of Selected Peripheral */
		if (NVIC_PerEnable_Arr[Per_Index] == NVIC_ENABLE)
		{
			MNVIC_voidEnableInterrupt(Per_Index);
		}
		else
		{
			/* Do Nothing*/
		}
	}
}

/* DeInitialization of NVIC
 * Disable of Configuration interrupts
 */
void MNVIC_voidDeInit(void)
{
	NVIC_Position_t Per_Index;
	for (Per_Index = NVIC_WWDG; Per_Index <= NVIC_SPI4; Per_Index++)
	{
		/* Disable interrupt of Selected Peripheral */
		if (NVIC_PerEnable_Arr[Per_Index] != NVIC_RESERVED)
		{
			MNVIC_voidDisableInterrupt(Per_Index);
		}
		else
		{
			/* Do Nothing*/
		}
	}
}


/* Enable interrupt of Selected Peripheral */
void MNVIC_voidEnableInterrupt(u8 Copy_u8IntPos)
{
	/* Check if Entered position of peripheral not exceed number of total peripheral */
	if (Copy_u8IntPos < MAX_INTERUPT_NUM)
	{
		/* Set by set one in in Interrupt set-enable register */
		NVIC->ISER[Copy_u8IntPos / REG_DIV] = 1 << (Copy_u8IntPos % REG_DIV);
	}
	else
	{
		/* Return Error */
	}
}

/* Disable interrupt of Selected Peripheral */
void MNVIC_voidDisableInterrupt(u8 Copy_u8IntPos)
{
	/* Check if Entered position of peripheral not exceed number of total peripheral */
	if (Copy_u8IntPos < MAX_INTERUPT_NUM)
	{
		/* Clear by set one in interrupt clear-enable register */
		NVIC->ICER[Copy_u8IntPos / REG_DIV] = 1 << (Copy_u8IntPos % REG_DIV);
	}
	else
	{
		/* Return Error */
	}
}

/* Enable of Pending Flag on Selected Peripheral */
void MNVIC_voidEnableInterruptPending(u8 Copy_u8IntPos)
{
	/* Check if Entered position of peripheral not exceed number of total peripheral */
	if (Copy_u8IntPos < MAX_INTERUPT_NUM)
	{
		NVIC->ISPR[Copy_u8IntPos / REG_DIV] = 1 << (Copy_u8IntPos % REG_DIV);
	}
	else
	{
		/* Return Error */
	}
}
/* Disable of Pending Flag on Selected Peripheral */
void MVIC_voidDisableInterruptPending(u8 Copy_u8IntPos)
{
	/* Check if Entered position of peripheral not exceed number of total peripheral */
	if (Copy_u8IntPos < MAX_INTERUPT_NUM)
	{
		NVIC->ICPR[Copy_u8IntPos / REG_DIV] = 1 << (Copy_u8IntPos % REG_DIV);
	}
	else
	{
		/* Return Error */
	}
}
/* Read Active Flag for selected peripheral */
void MNVIC_voidIsInterruptAvtive(u8 Copy_u8IntPos, u8* Copy_pu8Read)
{
	/* Check if Entered position of peripheral not exceed number of total peripheral */
	if (Copy_u8IntPos < MAX_INTERUPT_NUM)
	{
		*Copy_pu8Read = GET_BIT((NVIC->IAPR[Copy_u8IntPos / REG_DIV]), ( Copy_u8IntPos % REG_DIV));
	}
	else
	{
		/* Return Error */
	}
}

/* Set to external peripheral Group and sub group priority */
void MVIC_voidSetInterruptPriorty(u8 Copy_u8IntPos, u8 Copy_u8GroupnNum, u8 Copy_u8SubGroupnNum)
{
	/* Set in NVIC peripheral Group and SubGroup */
	switch (Global_enuPRI)
	{
	case GROUP16_SUB0:
		NVIC->IPR[Copy_u8IntPos] = Copy_u8GroupnNum << 4;
		break;
	case GROUP8_SUB2:
		NVIC->IPR[Copy_u8IntPos] = Copy_u8GroupnNum << 5 | Copy_u8SubGroupnNum << 4;
		break;
	case GROUP4_SUB4:
		NVIC->IPR[Copy_u8IntPos] = Copy_u8GroupnNum << 6 | Copy_u8SubGroupnNum << 4;;
		break;
	case GROUP2_SUB8:
		NVIC->IPR[Copy_u8IntPos] = Copy_u8GroupnNum << 7 | Copy_u8SubGroupnNum << 4;;
		break;
	case GROUP0_SUB16:
		NVIC->IPR[Copy_u8IntPos] = Copy_u8SubGroupnNum << 4;;
		break;
	default:
		/* Return Error */
		break;
	}
}

/* Select which grouping mode system NVIC priority will operate */
void MVIC_voidSetInterruptGroupMode(MNVIC_Group_t Copy_enuGroupMode)
{
	Global_enuPRI = Copy_enuGroupMode;
	/* Set mode by writing VECT key (password) and mode in System control block
	 * Application interrupt and reset control register
	 */
	SCB_AIRCR = (Copy_enuGroupMode << 8) | (VECTKEY) | (SCB_AIRCR & 0xFFFF7FF8);
}


/*
 * @brief   System Reset
 * @details Initiates a system reset request to reset the MCU.
 */
void MNVIC_SystemReset(void)
{
	__asm volatile ("dsb 0xF":::"memory");                              /* Ensure all outstanding memory accesses included
	                                                                    buffered write are completed before reset */
	//SCB_AIRCR  = 	(u32)0x5FA0004;
#define NVIC_AIRCR_VECTKEY    (0x5FA << 16)   /*!< AIRCR Key for write access   */
#define NVIC_SYSRESETREQ            2         /*!< System Reset Request         */

	SCB->AIRCR  = 0x5FA0004;

	__asm volatile ("dsb 0xF":::"memory");                              /* Ensure completion of memory access */

	for(;;)                                     	                    /* wait until reset */
	{
		__asm volatile ("nop");
	}
}

/* Reallocate of vector table */
void MNVIC_SetVectorTable(u32 Copy_u32Address)
{
	/* Reallocate of vector table */
	SCB->VTOR = Copy_u32Address;

}

