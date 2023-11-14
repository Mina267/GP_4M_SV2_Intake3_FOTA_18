/*********************************************************/
/*********************************************************/
/***********		Author: Adel Magdy   	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: ULTRASONIC   		**************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#ifndef ULTLASONIC_INTERFACE_H_
#define ULTLASONIC_INTERFACE_H_

/*Intialization put vcc on 5 v */
void HUltrasonicInti(void);

/**/
void HUltraSonicTriger(void);

/*return distance */
f32 HUltrasonicReturnDistance(void);

#endif
