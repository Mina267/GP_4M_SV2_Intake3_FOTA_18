#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/MGPIO_interface.h"
#include "../include/TIM_interface.h"


#include "../include/MOTOR_interface.h"
#include "../include/MOTOR_cfg.h"
#include "../include/MOTOR_private.h"


const u8 MotorPinsArray[NUMBER_MOTORS][MOTOR_PIN_NUMBERS][2]={
			    /* IN1     IN2     EN  */
	/* motor 1*/{ {M1_IN1_PORT, M1_IN1_PIN}, {M1_IN2_PORT, M1_IN2_PIN}, {M1_EN_PORT, M1_EN_PIN}},
	/* motor 2*/{ {M2_IN1_PORT, M2_IN1_PIN}, {M2_IN2_PORT, M2_IN2_PIN}, {M2_EN_PORT, M2_EN_PIN}},
	/* motor 3*/{ {M3_IN1_PORT, M3_IN1_PIN}, {M3_IN2_PORT, M3_IN2_PIN}, {M3_EN_PORT, M3_EN_PIN}},
	/* motor 4*/{ {M4_IN1_PORT, M4_IN1_PIN}, {M4_IN2_PORT, M4_IN2_PIN}, {M4_EN_PORT, M4_EN_PIN}},
};
