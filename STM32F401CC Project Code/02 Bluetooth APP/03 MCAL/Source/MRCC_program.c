/*****************************************************************/
/* Author  : Mina Magdy                                          */
/* Layer   : MCAL                                                */
/* SWC     : MRCC                                                */
/* Version : 2.0                                                 */
/* Date    : 09 Sep 2023                                         */
/*****************************************************************/


#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"

#include "../include/MRCC_config.h"
#include "../include/MRCC_interface.h"
#include "../include/MRCC_private.h"

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
void MRCC_voidInit( void )
{
	/****************************************************/
	/***** System clock operate with External clock *****/
	/****************************************************/
#if (SYS_CLK == RCC_HSE)

	/* Select If external clock is RC or Crystal */
#if (HSE_MODE == HSE_CRYSTAL)
	CLR_BIT(RCC->CR, CR_HSE_BYP);
#elif (HSE_MODE == HSE_RC)
	SET_BIT(RCC->CR, CR_HSE_BYP);
#endif

	/* Clock security system ON/OFF */
#if (CSS_ENABLE == CSS_ON)
	SET_BIT(RCC->CR, CR_CSS_ON);
#elif (CSS_ENABLE == CSS_OFF)
	CLR_BIT(RCC->CR, CR_CSS_ON);
#endif

	/* Enable HSE */
	SET_BIT(RCC->CR, CR_HSE_ON);
	/* Check HSE Ready flag  */
	while(!GET_BIT(RCC->CR, CR_HSE_RDY));
	/* Switch to HSE */
	(RCC->CFGR) &= SWITCH_MASK;
	(RCC->CFGR) |= SWITCH_HSE;


	/****************************************************/
	/***** System clock operate with Internal clock *****/
	/****************************************************/
#elif (SYS_CLK == RCC_HSI)

	/* Enable HSI */
	SET_BIT(RCC->CR, CR_HSI_ON);
	/* Check HSE Ready flag  */
	while(!GET_BIT(RCC->CR, CR_HSI_RDY));
	/* Switch to HSI */
	(RCC->CFGR) &= SWITCH_MASK;
	(RCC->CFGR) |= SWITCH_HSI;




	/****************************************************/
	/****** System clock operate with PLL clock *********/
	/****************************************************/
#elif (SYS_CLK == RCC_PLL)

	/* Set PLL input Source HSE or HSI */
#if (PLL_SOURCE == PLL_HSI)
	CLR_BIT(RCC->PLLCFGR, PLLCFGR_PLLSRC);
#elif (PLL_SOURCE == PLL_HSE)
	SET_BIT(RCC->PLLCFGR, PLLCFGR_PLLSRC);
#endif

	/* Set  PLLP DIVISION FACTOR for selected main clock input to PLL */
	(RCC->PLLCFGR) &= PLLP_DIV_FACTOR_MASK;
	(RCC->PLLCFGR) |= (PLLP_MAIN_CLK_DIVISION_FACTOR << 16) ;


	/* Set PLLN Multiplication FACTOR for output to PLL */
	(RCC->PLLCFGR) &= PLLN_MULT_CLOCK_FACTOR_MASK;
	(RCC->PLLCFGR) |= (PLLN_MULT_CLOCK_FACTOR << 6) ;

	/* Set PLLM Division FACTOR for output to PLL */
	(RCC->PLLCFGR) &= PLLM_DIV_CLOCK_FACTOR_MASK;
	(RCC->PLLCFGR) |= (PLLM_DIV_CLOCK_FACTOR) ;

	/* Enable PLL */
	SET_BIT(RCC->CR, CR_PLL_ON);
	/* Check HSE Ready flag  */
	while(!GET_BIT(RCC->CR, CR_PLL_RDY));
	/* Switch to PLL */
	(RCC->CFGR) &= SWITCH_MASK;
	(RCC->CFGR) |= SWITCH_PLL;

#endif
}

void MRCC_voidDeInit( void )
{
	/* Reset GPIOA, GPIOB and GPIOC */
	RCC->AHB1RSTR = (u32)0x7;
	/* Release reset */
	RCC->AHB1RSTR = (u32)0x0;

	/* Reset UART2 and TIM3 */
	RCC->APB1RSTR = (u32)0x20002;
	/* Release reset */
	RCC->APB1RSTR = (u32)0x0;

	/* Reset SYSCFG and USART1 */
	RCC->APB2RSTR = (u32)0x4010;
	/* Release reset */
	RCC->APB2RSTR = (u32)0x0;
}

/* Peripheral Clock Enable
 * Take as argument Bus and Peripheral want to enable clock on it
 */
void MRCC_voidEnable_Peripheral(u32 Copy_u32Address_Bus, u32 Copy_u32Peripheral)
{
	/* Check if Peripheral number larger than 31 */
	if (Copy_u32Peripheral <= 31)
	{
		/* switch over address Bus
		 * Enable required Peripheral
		 * By set Peripheral Bit in Bus Register */
		switch (Copy_u32Address_Bus)
		{
		case RCC_AHB1:
			SET_BIT(RCC->AHB1ENR, Copy_u32Peripheral);		/* Set bit of peripheral to Enable its Clock */
			break;

		case RCC_AHB2:
			SET_BIT(RCC->AHB2ENR, Copy_u32Peripheral);		/* Set bit of peripheral to Enable its Clock */
			break;

		case RCC_APB1:
			SET_BIT(RCC->APB1ENR, Copy_u32Peripheral);		/* Set bit of peripheral to Enable its Clock */
			break;

		case RCC_APB2:
			SET_BIT(RCC->APB2ENR, Copy_u32Peripheral);		/* Set bit of peripheral to Enable its Clock */
			break;

		case RCC_AHB1LP:
			SET_BIT(RCC->AHB1LPENR , Copy_u32Peripheral);	/* Set bit of peripheral to Enable Low Power its Clock */
			break;
		case RCC_AHB2LP:
			SET_BIT(RCC->AHB2LPENR , Copy_u32Peripheral);	/* Set bit of peripheral to Enable Low Power its Clock */
			break;

		case RCC_APB1LP:
			SET_BIT(RCC->APB1LPENR , Copy_u32Peripheral);	/* Set bit of peripheral to Enable Low Power its Clock */
			break;

		case RCC_APB2LP:
			SET_BIT(RCC->APB2LPENR , Copy_u32Peripheral);	/* Set bit of peripheral to Enable Low Power its Clock */
			break;

		default:
			/* return Error */
			break;
		}
	}
	else
	{
		/* return Error */
	}
}
/* Peripheral Clock Enable
 * Take as argument Bus and Peripheral want to disable clock on it
 */
void MRCC_voidDisable_Peripheral(u32 Copy_u32Address_Bus, u32 Copy_u32Peripheral)
{
	/* Check if Peripheral number larger than 31 */
	if (Copy_u32Peripheral <= 31)
	{
		/* switch over address Bus
		 * Disable required Peripheral
		 * By Clear Peripheral Bit in Bus Register */
		switch (Copy_u32Address_Bus)
		{
		case RCC_AHB1:
			CLR_BIT(RCC->AHB1ENR, Copy_u32Peripheral);	/* Set bit of peripheral to Disable its Clock */
			break;

		case RCC_AHB2:
			CLR_BIT(RCC->AHB2ENR, Copy_u32Peripheral);	/* Set bit of peripheral to Disable its Clock */
			break;

		case RCC_APB1:
			CLR_BIT(RCC->APB1ENR, Copy_u32Peripheral);	/* Set bit of peripheral to Disable its Clock */
			break;

		case RCC_APB2:
			CLR_BIT(RCC->APB2ENR, Copy_u32Peripheral);	/* Set bit of peripheral to Disable its Clock */
			break;

		case RCC_AHB1LP:
			CLR_BIT(RCC->AHB1LPENR , Copy_u32Peripheral);	/* Set bit of peripheral to Disable Low Power its Clock */
			break;
		case RCC_AHB2LP:
			CLR_BIT(RCC->AHB2LPENR , Copy_u32Peripheral);	/* Set bit of peripheral to Disable Low Power its Clock */
			break;

		case RCC_APB1LP:
			CLR_BIT(RCC->APB1LPENR , Copy_u32Peripheral);	/* Set bit of peripheral to Disable Low Power its Clock */
			break;

		case RCC_APB2LP:
			CLR_BIT(RCC->APB2LPENR , Copy_u32Peripheral);	/* Set bit of peripheral to Disable Low Power its Clock */
			break;

		default:
			/* return Error */
			break;
		}
	}
	else
	{
		/* return Error */
	}
}



/*
 * Convert to PLL Source in Running time.
 * Select if source is HSE or HSI.
 * f(VCO clock) = (f(VCO clock) / PLLP) * (PLLN / PLLM)
 */
void MRCC_voidStartOfPLL(MRCC_PLLSource_t Copy_enuInputClock, u16 Copy_u8PLLP, u16 Copy_u8PLLN, u16 Copy_u8PLLM)
{
//	/* Set PLL input Source HSE or HSI */
//	switch (Copy_enuInputClock) {
//	case MRCC_HSI:
//		CLR_BIT(RCC->PLLCFGR, PLLCFGR_PLLSRC);
//		break;
//	case MRCC_HSE:
//		SET_BIT(RCC->PLLCFGR, PLLCFGR_PLLSRC);
//		break;
//	default:
//		break;
//	}
//
//
//	/* Set  PLLP DIVISION FACTOR for selected main clock input to PLL */
//	(RCC->PLLCFGR) &= PLLP_DIV_FACTOR_MASK;
//	(RCC->PLLCFGR) |= (Copy_u8PLLP << 16) ;
//
//	/* Check For PLLN Range */
//	if ( MIN_PLLN >= Copy_u8PLLN && Copy_u8PLLN <= MAX_PLLN)
//	{
//		/* Set PLLM Division FACTOR for output to PLL */
//		(RCC->PLLCFGR) &= PLLM_DIV_CLOCK_FACTOR_MASK;
//		(RCC->PLLCFGR) |= (Copy_u8PLLM) ;
//	}
//
//	/* Check For PLLM Range */
//	if ( MIN_PLLM >= Copy_u8PLLM && Copy_u8PLLM <= MAX_PLLM)
//	{
//		/* Set PLLN Multiplication FACTOR for output to PLL */
//		(RCC->PLLCFGR) &= PLLN_MULT_CLOCK_FACTOR_MASK;
//		(RCC->PLLCFGR) |= (Copy_u8PLLN << 6) ;
//	}
//
//	/* Enable PLL */
//	SET_BIT(RCC->CR, CR_PLL_ON);
//	/* Check HSE Ready flag  */
//	while(!GET_BIT(RCC->CR, CR_PLL_RDY));
//	/* Switch to PLL */
//	(RCC->CFGR) &= SWITCH_MASK;
//	(RCC->CFGR) |= SWITCH_PLL;
}


/*
 * Convert to HSE Source in Running time as system clock source.
 * Operate for RCC or crystal as configuration.
 */
void MRCC_voidStartOfHSE(void)
{
	/* Select If external clock is RC or Crystal */
#if (HSE_MODE == HSE_CRYSTAL)
	CLR_BIT(RCC->CR, CR_HSE_BYP);
#elif (HSE_MODE == HSE_RC)
	SET_BIT(RCC->CR, CR_HSE_BYP);
#endif

	/* Enable HSE */
	SET_BIT(RCC->CR, CR_HSE_ON);
	/* Check HSE Ready flag  */
	while(!GET_BIT(RCC->CR, CR_HSE_RDY));
	/* Switch to HSE */
	(RCC->CFGR) &= SWITCH_MASK;
	(RCC->CFGR) |= SWITCH_HSE;
}

/*
 * Convert to HSI Source in Running time as system clock source.
 */
void MRCC_voidStartOfHSI(void)
{
	/* Enable HSI */
	SET_BIT(RCC->CR, CR_HSI_ON);
	/* Check HSE Ready flag  */
	while(!GET_BIT(RCC->CR, CR_HSI_RDY));
	/* Switch to HSI */
	(RCC->CFGR) &= SWITCH_MASK;
	(RCC->CFGR) |= SWITCH_HSI;
}

