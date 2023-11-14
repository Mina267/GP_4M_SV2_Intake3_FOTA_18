/*****************************************************************/
/* Author  : Mina Magdy                                          */
/* Layer   : MCAL                                                */
/* SWC     : MGPIO                                               */
/* Version : 1.0                                                 */
/* Date    : 09 Sep 2023                                         */
/*****************************************************************/
#ifndef GPIO_CONFIG_H_
#define GPIO_CONFIG_H_

/* Size of Each port Pin of port initialization */
#define GPIOA_PINS_MAX	13
#define GPIOB_PINS_MAX	15
#define GPIOC_PINS_MAX	3


/* Option: GPIO_ENABLE	GPIO_DISABLE */
#define GPIOA_PORT_INIT_ENABLE		GPIO_ENABLE
#define GPIOB_PORT_INIT_ENABLE		GPIO_ENABLE
#define GPIOC_PORT_INIT_ENABLE		GPIO_DISABLE



#endif
