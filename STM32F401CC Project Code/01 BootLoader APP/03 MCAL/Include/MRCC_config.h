/*****************************************************************/
/* Author  : Mina Magdy                                          */
/* Layer   : MCAL                                                */
/* SWC     : MRCC                                                */
/* Version : 2.0                                                 */
/* Date    : 09 Sep 2023                                         */
/*****************************************************************/
#ifndef MRCC_CONFIG_H_
#define MRCC_CONFIG_H_

/*********************************************************************************************/
/********************************* Select System clock ***************************************/
/*********************************************************************************************/


/* Select system clock
 * Option: 	SWITCH_HSI
			SWITCH_HSE
			SWITCH_PLL
 */
#define SYS_CLK					RCC_HSI

/*************************** For Selection of HSE AS System Clock *****************************/

/* HSE Operation
 *  Option: HSE_RC
 *  		HSE_CRYSTAL
 */
#define HSE_MODE				HSE_CRYSTAL

/* Clock security system ON/OFF
 * Option: 	CSS_ON
 * 			CSS_OFF
 */

#define CSS_ENABLE				CSS_OFF

/*************************** For Selection of HSI AS System Clock *****************************/
/* +40KHZ OR -40KHZ per step
 * Max Add is		HSI_ADD_520KHZ
 * Max Remove is	HSI_REMOVE_560KHZ
 * No trimming	 	HSI_NO_TRIM
 */
#define HSI_TRIM_FACTOR			HSI_NO_TRIM

/*************************** For Selection of PLL AS System Clock ****************************/

/*
 * Option: 	PLL_HSI
 * 			PLL_HSE
 */
#define PLL_SOURCE				PLL_HSI

/*********************************************************************************************/
/******************** f(PLL general clock output) = f(VCO clock) / PLLP **********************/
/*********************************************************************************************/

/*
 * Option:	PLL_DIV_BY_2
 *			PLL_DIV_BY_4
 *			PLL_DIV_BY_6
 *			PLL_DIV_BY_8
 */

#define PLLP_MAIN_CLK_DIVISION_FACTOR		PLL_MAIN_CLK_DIV_BY_2

/*********************************************************************************************/
/********************* f(VCO clock) = f(PLL clock input) * (PLLN / PLLM) *********************/
/*********************************************************************************************/

/* PLLN: Multiplication FACTOR for output to PLL
 * Option:
 * From 2 -> 432
 */

#define PLLN_MULT_CLOCK_FACTOR		2

/* PLLM: Division FACTOR for output to PLL
 * Option:
 * From 2 -> 63
 */


#define PLLM_DIV_CLOCK_FACTOR		2

/*********************************************************************************************/
/******************************** PRESCALER of Address Bus ***********************************/
/*********************************************************************************************/

/*
 * PRESCALER for AHB
 * Max = 84 MHz
 * Option: 	AHB_NO_DIV
 * 			AHB_DIV_2_
 * 			AHB_DIV_4_
 * 			AHB_DIV_8_
 * 			AHB_DIV_16_
 * 			AHB_DIV_64_
 * 			AHB_DIV_128_
 * 			AHB_DIV_256_
 * 			AHB_DIV_512_
 */
#define AHB_PRESCALER			AHB_NO_DIV

/*
 * PRESCALER for APB1
 * Max = 42 MHz
 * Option: 	APB_NO_DIV
 * 			APB_DIV_2_
 * 			APB_DIV_4_
 * 			APB_DIV_8_
 * 			APB_DIV_16_
 */
#define APB1_PRESCALER			APB_NO_DIV

/*
 * PRESCALER for APB2
 * Max = 84 MHz
 * Option: 	APB_NO_DIV
 * 			APB_DIV_2_
 * 			APB_DIV_4_
 * 			APB_DIV_8_
 * 			APB_DIV_16_
 */
#define APB2_PRESCALER			APB_NO_DIV

#endif
