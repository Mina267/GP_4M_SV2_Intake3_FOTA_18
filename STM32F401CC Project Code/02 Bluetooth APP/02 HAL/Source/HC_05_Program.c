/*****************************************************************/
/* Author  : Mina2                                               */
/* Layer   : HAL                                                 */
/* SWC     : HC_05                                               */
/* Version : 1.0                                                 */
/* Date    : 07 Nov 2023                                         */
/*****************************************************************/


#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/MUART_Interface.h"
#include "../include/MGPIO_interface.h"


#include "../include/HC_05_Interface.h"
#include "../include/HC_05_Private.h"
#include "../include/HC_05_Config.h"


void HC_05_voidInit(void)
{
	MGPIO_SetAlternativeFuncPin(PORTA, PIN11, USART6);
	MGPIO_SetAlternativeFuncPin(PORTA, PIN12, USART6);
	MUART6_voidInit(BAUD_RATE_16MHZ_9600_);
	MUART6_EnableTX();
	MUART6_EnableRX();
	MUART6_voidEnable();
}
