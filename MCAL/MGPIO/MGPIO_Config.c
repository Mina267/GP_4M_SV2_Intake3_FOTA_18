
#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"

#include "../include/MGPIO_interface.h"
#include "../include/MGPIO_config.h"




/*
 * Options: OUT_PUSHPULL_8MHZ_       ***  LOW_SPEED        ***
 *          OUT_PUSHPULL_50MHZ_      ***  MEDIUM_SPEED     ***
 *          OUT_PUSHPULL_80MHZ_      ***  HIGH_SPEED       ***
 *          OUT_PUSHPULL_180MHZ_     ***  VERY_HIGH_SPEED  ***
 *          OUT_OPENDRAIN_8MHZ,      ***  LOW_SPEED        ***
 *          OUT_OPENDRAIN_50MHZ_     ***  MEDIUM_SPEED     ***
 *          OUT_OPENDRAIN_80MHZ_     ***  HIGH_SPEED       ***
 *          OUT_OPENDRAIN_180MHZ_    ***  VERY_HIGH_SPEED  ***
 *          AF_PUSHPULL_8MHZ_,       ***  LOW_SPEED        ***
 *			AF_PUSHPULL_50MHZ_,      ***  MEDIUM_SPEED     ***
 *			AF_PUSHPULL_80MHZ_,      ***  HIGH_SPEED       ***
 *			AF_PUSHPULL_180MHZ_,     ***  VERY_HIGH_SPEED  ***
 *			AF_OPENDRAIN_8MHZ,       ***  LOW_SPEED        ***
 *			AF_OPENDRAIN_50MHZ_,     ***  MEDIUM_SPEED     ***
 *			AF_OPENDRAIN_80MHZ_,     ***  HIGH_SPEED       ***
 *			AF_OPENDRAIN_180MHZ_,    ***  VERY_HIGH_SPEED  ***
 *          IN_FREE,
 *          IN_PULLUP,
 *          IN_PULLDOWN,
 *          AF_FREE,
 *          AF_PULLUP,
 *          AF_PULLDOWN

 */

/*************************************************************************/
/******************* PORT A PINS Configuration ***************************/
/*************************************************************************/

GPIO_PinOperateMode_t const GPIOA_Pins_Array[GPIOA_PINS_MAX] =

		/* PIN Status Mode*/
{		IN_PULLUP,						/* PINA0  */				 /* ACD0 */
		OUT_PUSHPULL_50MHZ_,	    	/* PINA1  */				 /* ACD1 */
		AF_PUSHPULL_80MHZ_,	  	 		/* PINA2  */    /* TX2 */    /* ACD2 */
		AF_FREE,	    				/* PINA3  */    /* RX2 */    /* ACD3 */
		OUT_PUSHPULL_50MHZ_,	   		/* PINA4  */                 /* ACD4 */
		OUT_PUSHPULL_50MHZ_,		   	/* PINA5  */	/* SCK1 */   /* ACD5 */
		OUT_PUSHPULL_50MHZ_,		  	/* PINA6  */	/* MISO1 */  /* ACD6 */
		OUT_PUSHPULL_50MHZ_,		 	/* PINA7  */	/* MOSI1 */  /* ACD7 */
		OUT_PUSHPULL_50MHZ_,			/* PINA8  */
		AF_PUSHPULL_80MHZ_,				/* PINA9  */ 	/* TX1 */
		AF_FREE,						/* PINA10 */ 	/* RX1 */
		OUT_PUSHPULL_50MHZ_,			/* PINA11 */    /* TX6 */
		OUT_PUSHPULL_50MHZ_,			/* PINA12 */    /* RX6 */
};

/*************************************************************************/
/******************* PORT B PINS Configuration ***************************/
/*************************************************************************/
GPIO_PinOperateMode_t const GPIOB_Pins_Array[GPIOB_PINS_MAX]=
		/* PIN Status Mode*/
{		OUT_PUSHPULL_50MHZ_,			/* PINB0  */   /* ACD8 */
		OUT_PUSHPULL_50MHZ_,			/* PINB1  */   /* ACD9 */
		OUT_PUSHPULL_50MHZ_,			/* PINB2  */
		OUT_PUSHPULL_50MHZ_,			/* PINB5  */
		OUT_PUSHPULL_50MHZ_,			/* PINB6  */   /* TX1 */
		OUT_PUSHPULL_50MHZ_,			/* PINB7  */   /* RX1 */
		OUT_PUSHPULL_50MHZ_,			/* PINB8  */
		OUT_PUSHPULL_50MHZ_,			/* PINB9  */
		OUT_PUSHPULL_50MHZ_,			/* PINB10 */
		OUT_PUSHPULL_50MHZ_,			/* PINB11 */
		OUT_PUSHPULL_50MHZ_,			/* PINB12 */
		OUT_PUSHPULL_50MHZ_,			/* PINB13 */  /* SCK2 */
		OUT_PUSHPULL_50MHZ_,			/* PINB14 */  /* MISO2 */
		OUT_PUSHPULL_50MHZ_				/* PINB15 */  /* MOSI2 */
};

/*************************************************************************/
/******************* PORT C PINS Configuration ***************************/
/*************************************************************************/
GPIO_PinOperateMode_t const GPIOC_Pins_Array[GPIOC_PINS_MAX] =
		/* PIN Status Mode*/
{		OUT_PUSHPULL_8MHZ_,				/* PINC13 */
		OUT_PUSHPULL_8MHZ_,				/* PINC14 */
		OUT_PUSHPULL_8MHZ_				/* PINC15 */
};
