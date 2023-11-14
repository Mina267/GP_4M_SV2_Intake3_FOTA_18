/*****************************************************************/
/* Author  : Mina Magdy                                          */
/* Layer   : MCAL                                                */
/* SWC     : MRCC                                                */
/* Version : 2.0                                                 */
/* Date    : 09 Sep 2023                                         */
/*****************************************************************/
#ifndef MRCC_PRIVATE_H_
#define MRCC_PRIVATE_H_

/* RCC Start Base address */
#define RCC_BASE_ADDRSS					(0x40023800)

/* RCC register map */
typedef struct
{
	u32 CR;
		u32 PLLCFGR;
		u32 CFGR;
		u32 CIR;
		u32 AHB1RSTR;
		u32 AHB2RSTR;
		u32 RESERVED1;
		u32 RESERVED2;
		u32 APB1RSTR;
		u32 APB2RSTR;
		u32 RESERVED3;
		u32 RESERVED4;
		u32 AHB1ENR;
		u32 AHB2ENR;
		u32 RESERVED5;
		u32 RESERVED6;
		u32 APB1ENR;
		u32 APB2ENR;
		u32 RESERVED7;
		u32 RESERVED8;
		u32 AHB1LPENR;
		u32 AHB2LPENR;
		u32 RESERVED9;
		u32 RESERVED10;
		u32 APB1LPENR;
		u32 APB2LPENR;
		u32 RESERVED11;
		u32 RESERVED12;
		u32 BDCR;
		u32 CSR;
		u32 RESERVED13;
		u32 RESERVED14;
		u32 SSCGR;
		u32 PLLI2SCFGR;
		u32 RESERVED15;
		u32 DCKCFGR;
}RCC_t;

/* pointer to struct of type RCC_t point to Base address of RCC Peripheral */
#define RCC								((volatile RCC_t*)RCC_BASE_ADDRSS)

/* RCC_CR Register Bits */
#define CR_PLLI2S_RDY		            (27)
#define CR_PLLI2S_ON		            (26)
#define CR_PLL_RDY			            (25)
#define CR_PLL_ON			            (24)
#define CR_CSS_ON			            (19)
#define CR_HSE_BYP			            (18)
#define CR_HSE_RDY			            (17)
#define CR_HSE_ON			            (16)
#define CR_HSI_RDY			            (1)
#define CR_HSI_ON			            (0)

/* RCC_PLLCFGR Register Bits */
#define PLLCFGR_PLLQ3		            (27)
#define PLLCFGR_PLLQ2		            (26)
#define PLLCFGR_PLLQ1		            (25)
#define PLLCFGR_PLLQ0		            (24)
#define PLLCFGR_PLLSRC		            (22)
#define PLLCFGR_PLLP1		            (17)
#define PLLCFGR_PLLP0		            (16)
#define PLLCFGR_PLLM5		            (5)
#define PLLCFGR_PLLM4		            (4)
#define PLLCFGR_PLLM3		            (3)
#define PLLCFGR_PLLM2		            (2)
#define PLLCFGR_PLLM1		            (1)
#define PLLCFGR_PLLM0		            (0)

/* RCC_CFGR Register Bits */
#define CFGR_I2SSCR			            (23)
#define CFGR_SWS1			            (3)
#define CFGR_SWS0			            (2)
#define CFGR_SW1			            (1)
#define CFGR_SW0			            (0)

/* RCC_CIR Register Bits */
#define CIR_CSSC			            (23)
#define CIR_PLLI2S_RDYC		            (21)
#define CIR_PLL_RDYC		            (20)
#define CIR_HSE_RDYC		            (19)
#define CIR_HSI_RDYC		            (18)
#define CIR_LSE_RDYC		            (17)
#define CIR_LSI_RDYC		            (16)
#define CIR_PLLI2S_RDYIE	            (13)
#define CIR_PLL_RDYIE		            (12)
#define CIR_HSE_RDYIE		            (11)
#define CIR_HSI_RDYIE		            (10)
#define CIR_LSE_RDYIE		            (9)
#define CIR_LSI_RDYIE		            (8)
#define CIR_CSSF			            (7)
#define CIR_PLLI2S_RDYF		            (5)
#define CIR_PLL_RDYF		            (4)
#define CIR_HSE_RDYF		            (3)
#define CIR_HSI_RDYF		            (2)
#define CIR_LSE_RDYF		            (1)
#define CIR_LSI_RDYF		            (0)


/* System Clock switch */
#define SWITCH_HSI			   	        (0)
#define SWITCH_HSE			   	        (1)
#define SWITCH_PLL			   	        (2)
#define SWITCH_MASK			   	        (0xFFFFFFFC)

/* Selection of system clock option */
#define RCC_HSI				         	(0)
#define RCC_HSE				         	(1)
#define RCC_PLL				         	(2)

/* HSE Option */
#define HSE_RC				         	(0)
#define HSE_CRYSTAL			         	(1)


/* Clock security system */
#define CSS_OFF				         	(0)
#define CSS_ON				         	(1)



/* PLL division Factor */
#define PLL_MAIN_CLK_DIV_BY_2			(0b00)
#define PLL_MAIN_CLK_DIV_BY_4			(0b01)
#define PLL_MAIN_CLK_DIV_BY_6			(0b10)
#define PLL_MAIN_CLK_DIV_BY_8			(0b11)
#define DIV_MAIN_CLK_FACTOR_MASK		(0xFFFCFFFF)

/* HSI Software Trimming Factor */
#define HSI_REMOVE_560KHZ 	         	(0)
#define HSI_REMOVE_520KHZ 	           	(1)
#define HSI_REMOVE_480KHZ 	           	(2)
#define HSI_REMOVE_440KHZ 	         	(3)
#define HSI_REMOVE_400KHZ 	         	(4)
#define HSI_REMOVE_340KHZ 	         	(5)
#define HSI_REMOVE_300KHZ 	         	(6)
#define HSI_REMOVE_260KHZ	         	(7)
#define HSI_REMOVE_220KHZ	         	(8)
#define HSI_REMOVE_280KHZ	         	(9)
#define HSI_REMOVE_240KHZ	         	(10)
#define HSI_REMOVE_200KHZ	         	(11)
#define HSI_REMOVE_160KHZ	         	(12)
#define HSI_REMOVE_120KHZ	         	(13)
#define HSI_REMOVE_80KHZ 	         	(14)
#define HSI_REMOVE_40KHZ 	         	(15)
#define HSI_NO_TRIM			        	(16)
#define HSI_ADD_40KHZ 		        	(17)
#define HSI_ADD_80KHZ 		        	(18)
#define HSI_ADD_120KHZ 		        	(19)
#define HSI_ADD_160KHZ 		        	(20)
#define HSI_ADD_200KHZ 		        	(21)
#define HSI_ADD_240KHZ 		        	(22)
#define HSI_ADD_280KHZ 		        	(23)
#define HSI_ADD_220KHZ 		        	(24)
#define HSI_ADD_260KHZ 		        	(25)
#define HSI_ADD_300KHZ 		        	(26)
#define HSI_ADD_340KHZ 		        	(27)
#define HSI_ADD_400KHZ 		        	(28)
#define HSI_ADD_440KHZ 		        	(29)
#define HSI_ADD_480KHZ 		        	(30)
#define HSI_ADD_520KHZ		        	(31)
#define TRIM_MASK			        	(0xFFFFFF07)


/* PRESCALER of Address Bus */
/* PRESCALER APB Bus */
#define APB_NO_DIV			  	        (0b000)
#define APB_DIV_2_			  	        (0b100)
#define APB_DIV_4_			  	        (0b101)
#define APB_DIV_8_			  	        (0b110)
#define APB_DIV_16_			  	        (0b111)
/* PRESCALER AHB Bus */
#define AHB_NO_DIV			  	        (0b0000)
#define AHB_DIV_2_			  	        (0b1000)
#define AHB_DIV_4_			  	        (0b1001)
#define AHB_DIV_8_			  	        (0b1010)
#define AHB_DIV_16_			  	        (0b1011)
#define AHB_DIV_64_			  	        (0b1100)
#define AHB_DIV_128_		  	        (0b1101)
#define AHB_DIV_256_		  	        (0b1110)
#define AHB_DIV_512_		  	        (0b1111)

/*************** PLL Cfg *******************************/
#define PLLP_DIV_FACTOR_MASK				(0xFFFCFFFF)
#define PLLN_MULT_CLOCK_FACTOR_MASK			(0xFFFF803F)
#define PLLM_DIV_CLOCK_FACTOR_MASK			(0xFFFFFFE0)
#define MIN_PLLN							2
#define MAX_PLLN							432
#define MIN_PLLM							2
#define MAX_PLLM							63

#endif
