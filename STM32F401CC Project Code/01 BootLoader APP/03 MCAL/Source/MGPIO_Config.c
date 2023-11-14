
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
 *
 */

/*************************************************************************/
/******************* PORT A PINS Configuration ***************************/
/*************************************************************************/

GPIO_PinOperateMode_t const GPIOA_Pins_Array[GPIOA_PINS_MAX] =

		/* PIN Status Mode*/
{		IN_PULLUP,						/* PINA0  */				 /* ACD0 */ /* T2C1 */ /* T5C1 */
		IN_PULLUP,				    	/* PINA1  */				 /* ACD1 */ /* T2C2 */ /* T5C2 */
		AF_PUSHPULL_80MHZ_,	  	 		/* PINA2  */    /* TX2 */    /* ACD2 */ /* T2C3 */ /* T5C3 */ /* T9C1 */
		AF_FREE,	    				/* PINA3  */    /* RX2 */    /* ACD3 */ /* T2C4 */ /* T5C4 */ /* T9C2 */
		OUT_PUSHPULL_50MHZ_,	   		/* PINA4  */                 /* ACD4 */
		OUT_PUSHPULL_50MHZ_,		   	/* PINA5  */	/* SCK1 */   /* ACD5 */ /* T2C1 */
		OUT_PUSHPULL_50MHZ_,		  	/* PINA6  */	/* MISO1 */  /* ACD6 */ /* T3C1 */
		OUT_PUSHPULL_50MHZ_,		 	/* PINA7  */	/* MOSI1 */  /* ACD7 */ /* T3C2 */
		OUT_PUSHPULL_50MHZ_,			/* PINA8  */				 /* T1C1 */
		AF_PUSHPULL_80MHZ_,				/* PINA9  */ 	/* TX1 */	 /* T1C2 */
		AF_FREE,						/* PINA10 */ 	/* RX1 */	 /* T1C3 */
		OUT_PUSHPULL_50MHZ_,			/* PINA11 */    /* TX6 */	 /* T1C4 */
		OUT_PUSHPULL_50MHZ_,			/* PINA12 */    /* RX6 */
};

/*************************************************************************/
/******************* PORT B PINS Configuration ***************************/
/*************************************************************************/
GPIO_PinOperateMode_t const GPIOB_Pins_Array[GPIOB_PINS_MAX]=
		/* PIN Status Mode*/
{		OUT_PUSHPULL_50MHZ_,			/* PINB0  */   /* ACD8 */	/* T3C3 */
		OUT_PUSHPULL_50MHZ_,			/* PINB1  */   /* ACD9 */	/* T3C4 */
		OUT_PUSHPULL_50MHZ_,			/* PINB2  */
		OUT_PUSHPULL_50MHZ_,			/* PINB5  */				/* T3C2 */
		OUT_PUSHPULL_50MHZ_,			/* PINB6  */   /* TX1 */	/* T4C1 */
		OUT_PUSHPULL_50MHZ_,			/* PINB7  */   /* RX1 */	/* T4C2 */
		OUT_PUSHPULL_50MHZ_,			/* PINB8  */				/* T10C1 */
		OUT_PUSHPULL_50MHZ_,			/* PINB9  */				/* T4C4 */ /* T11C1 */
		OUT_PUSHPULL_50MHZ_,			/* PINB10 */				/* T2C3 */
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
