
#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_


#define  MOTOR_PIN_NUMBERS   3
#define  IN1   0
#define  IN2   1
#define  EN    2


typedef enum
{
	M_CW,
	M_CCW,
	M_STOP
}Direction_status;



typedef enum
{
	M1,
	M2,
	M3,
	M4
	}MOTOR_type;

void MOTOR_Init(void);


void MOTOR_Init(void);
Error_type MOTOR_Stop(MOTOR_type motor);
Error_type MOTOR_CW(MOTOR_type motor);
Error_type MOTOR_CCW(MOTOR_type motor);
/*  speed from 0 to 100  %**/
void MOTOR_Speed(MOTOR_type motor,u8 speed);
/*  speed from 0 to 100  % , Dir CW or CCW*/
void MOTOR_Speed_dir(MOTOR_type motor, u8 speed, Direction_status status);


void MOTOR_dir(MOTOR_type motor, Direction_status status);

#endif /* MOTOR_INTERFACE_H_ */