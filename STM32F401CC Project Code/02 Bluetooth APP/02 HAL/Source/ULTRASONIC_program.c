#include	"../include/STD_TYPES.h"
#include	"../include/BIT_MATH.h"

#include "../include/MGPIO_interface.h"
#include "../include/MRCC_interface.h"
#include "../include/MSYSTICK_Interface.h"
#include "../include/MSPI_Interface.h"
#include "../include/MDMA_Interface.h"
#include "../include/MNVIC_Interface.h"
#include	"../include/TIM_interface.h"

#include	"../include/ULTRASONIC_interface.h"

#include	"../include/ULTRASONIC_config.h"



void HUltrasonicInti(void)
{
	// init the Input Caputer mode for TIM1_CC
	MTIM1_f32Ch1Ch2InitMeasureTonPeriod();

	MGPIO_SetAlternativeFuncPin(PORTA, PIN8, TIM1_TIM2);







}
void HUltraSonicTriger(void)
{
	MGPIO_SetPinValue(PORTB, PIN1, HIGH);
	MTIM2_voidSetBusyWaitUs(10);
	MGPIO_SetPinValue(PORTB, PIN1, LOW);
}

f32 HUltrasonicReturnDistance(void)
{
	volatile f32 Local_f32TonPeriod ;
	////// test the ultrasonic
	Local_f32TonPeriod = MTIM1_f32Ch1Ch2MeasureTonPeriod();
	volatile f32 distance =( Local_f32TonPeriod /58);

	return distance;
}
