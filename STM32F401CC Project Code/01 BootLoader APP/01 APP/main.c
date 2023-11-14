
/* Lib */
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

/* MCAL */
#include "../include/MGPIO_interface.h"
#include "../include/MRCC_interface.h"
#include "../include/MSYSTICK_Interface.h"
#include "../include/MDMA_Interface.h"
#include "../include/MNVIC_Interface.h"
#include "../include/MUART_Interface.h"
#include "../include/MFDI_Interface.h"

/* HAL */
#include "../include/FEE_Interface.h"

/* Service */
#include "../include/BCM.h"
#include "../include/UDS_Interface.h"

void main(void)
{

	/* Initialization of RCC */
	MRCC_voidInit();
	/* Enable clock for GPIOA peripheral */
	MRCC_voidEnable_Peripheral(RCC_AHB1, RCC_AHB1_GPIOA);
	/* Enable clock for GPIOB peripheral */
	MRCC_voidEnable_Peripheral(RCC_AHB1, RCC_AHB1_GPIOB);
	/* Enable clock for Flash driver peripheral */
	MRCC_voidEnable_Peripheral(RCC_AHB1LP, RCC_AHB1PL_FLITF);

	/* Initialization of System tick */
	MSYSTICK_voidInit();

	MSYSTICK_voidStart(8000000);

	/* Initialization of GPIO */
	MGPIO_Init();


	/* Initialization of NVIC */
	MNVIC_voidInit();

	/* Initialization of Basic Communication Protocol */
	/* Initialization of UDS */
	UDS_voidInit();
	
	while (1)
	{


		UDS_voidRunnable();



	}

}







