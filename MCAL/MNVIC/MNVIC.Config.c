/*
 * MNVIC.Config.c
 *
 *  Created on: Oct 8, 2023
 *      Author: mina2
 */


#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"
#include "../include/MNVIC_interface.h"
#include "../include/MNVIC_config.h"
#include "../include/MNVIC_private.h"


/* Options: NVIC_DISABLE,
 *          NVIC_ENABLE,
 *          NVIC_RESERVED
 */

const MNVIC_Enable_t NVIC_PerEnable_Arr[NVIC_MAX_NUM] =
{

	NVIC_DISABLE,	                      	/* WWDG               (0)  */
	NVIC_DISABLE,	                      	/* EXTI16             (1)  */
	NVIC_DISABLE,	                      	/* EXTI21             (2)  */
	NVIC_DISABLE,	                      	/* EXTI22             (3)  */
	NVIC_DISABLE,	                      	/* FLASH              (4)  */
	NVIC_DISABLE,	                      	/* RCC                (5)  */
	NVIC_DISABLE,	                      	/* EXTI0              (6)  */
	NVIC_DISABLE,	                      	/* EXTI1              (7)  */
	NVIC_DISABLE,	                      	/* EXTI2              (8)  */
	NVIC_DISABLE,	                      	/* EXTI3              (9)  */
	NVIC_DISABLE,	                      	/* EXTI4              (10) */
	NVIC_DISABLE,	                      	/* DMA1_Stream0       (11) */
	NVIC_DISABLE,	                      	/* DMA1_Stream1       (12) */
	NVIC_DISABLE,	                      	/* DMA1_Stream2       (13) */
	NVIC_DISABLE,	                      	/* DMA1_Stream3       (14) */
	NVIC_DISABLE,	                      	/* DMA1_Stream4       (15) */
	NVIC_DISABLE,	                      	/* DMA1_Stream5       (16) */
	NVIC_DISABLE,	                      	/* DMA1_Stream6       (17) */
	NVIC_DISABLE,	                      	/* ADC                (18) */
	NVIC_RESERVED,							/* ADC                (19) */
	NVIC_RESERVED,							/*                    (20) */
	NVIC_RESERVED,							/*                    (21) */
	NVIC_RESERVED,							/*                    (22) */
	NVIC_DISABLE,	                      	/* EXTI9_5            (23) */
	NVIC_DISABLE,	                      	/* TIM1_BRK_TIM9      (24) */
	NVIC_DISABLE,	                      	/* TIM1_UP_TIM10      (25) */
	NVIC_DISABLE,	                      	/* TIM1_TRG_COM_TIM11 (26) */
	NVIC_DISABLE,	                      	/* TIM1_CC            (27) */
	NVIC_DISABLE,	                      	/* TIM2               (28) */
	NVIC_DISABLE,	                      	/* TIM3               (29) */
	NVIC_DISABLE,	                      	/* TIM4               (30) */
	NVIC_DISABLE,	                      	/* I2C1_EV            (31) */
	NVIC_DISABLE,	                      	/* I2C1_ER            (32) */
	NVIC_DISABLE,	                      	/* I2C2_EV            (33) */
	NVIC_DISABLE,	                      	/* I2C2_ER            (34) */
	NVIC_DISABLE,	                      	/* SPI1               (35) */
	NVIC_DISABLE,	                      	/* SPI2               (36) */
	NVIC_ENABLE,	                      	/* USART1             (37) */
	NVIC_ENABLE,	                      	/* USART2             (38) */
	NVIC_RESERVED,							/*                    (39) */
	NVIC_DISABLE,	                      	/* EXTI15_10          (40) */
	NVIC_DISABLE,	                      	/* EXTI17             (41) */
	NVIC_DISABLE,	                      	/* EXTI18             (42) */
	NVIC_RESERVED,							/*                    (43) */
	NVIC_RESERVED,							/*                    (44) */
	NVIC_RESERVED,							/*                    (45) */
	NVIC_RESERVED,							/*                    (46) */
	NVIC_DISABLE,	                      	/* DMA1_Stream7       (47) */
	NVIC_RESERVED,							/* DMA1_Stream7       (48) */
	NVIC_DISABLE,	                      	/* SDIO               (49) */
	NVIC_DISABLE,	                      	/* TIM5               (50) */
	NVIC_DISABLE,	                      	/* SPI3               (51) */
	NVIC_RESERVED,                         	/*                    (52) */
	NVIC_RESERVED,                         	/*                    (53) */
	NVIC_RESERVED,                         	/*                    (54) */
	NVIC_RESERVED,                        	/*                    (55) */
	NVIC_DISABLE,	                      	/* DMA2_Stream0       (56) */
	NVIC_DISABLE,	                      	/* DMA2_Stream1       (57) */
	NVIC_DISABLE,	                      	/* DMA2_Stream2       (58) */
	NVIC_DISABLE,	                      	/* DMA2_Stream3       (59) */
	NVIC_DISABLE,	                     	/* DMA2_Stream4       (60) */
	NVIC_RESERVED,                          /*                    (61) */
	NVIC_RESERVED,                          /*                    (62) */
	NVIC_RESERVED,                          /*                    (63) */
	NVIC_RESERVED,                          /*                    (64) */
	NVIC_RESERVED,                          /*                    (65) */
	NVIC_RESERVED,                          /*                    (66) */
	NVIC_DISABLE,	                      	/* OTG_FS             (67) */
	NVIC_DISABLE,	                      	/* DMA2_Stream5       (68) */
	NVIC_DISABLE,	                      	/* DMA2_Stream6       (69) */
	NVIC_DISABLE,	                      	/* DMA2_Stream7       (70) */
	NVIC_DISABLE,	                      	/* USART6             (71) */
	NVIC_DISABLE,	                      	/* I2C3_EV            (72) */
	NVIC_DISABLE,	                      	/* I2C3_ER            (73) */
	NVIC_RESERVED,                         	/*                    (74) */
	NVIC_RESERVED,                         	/*                    (75) */
	NVIC_RESERVED,                         	/*                    (76) */
	NVIC_RESERVED,                         	/*                    (77) */
	NVIC_RESERVED,                         	/*                    (78) */
	NVIC_RESERVED,                         	/*                    (79) */
	NVIC_RESERVED,                         	/*                    (80) */
	NVIC_DISABLE,	                     	/* FPU                (81) */
	NVIC_DISABLE,	                      	/* SPI4               (84) */

};
