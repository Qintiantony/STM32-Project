#include "motor.h"
void MOTOR_Init(void)
{
	RCC_APB2PeriphClockCmd(DIR_ENA_RCC,ENABLE);
	//Configure IO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=DIR_Pin|ENA_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(DIR_ENA_Port,&GPIO_InitStructure);
	DIR=1;
	ENA=1;
	
	//Initiate PWM/PUL
	//TIM3_CH1_PWM_Init(500, 72-1);//2kHz
}

void MOTOR_Run(u32 time_ms, u8 Direction)
{
	ENA=0;
	DIR=Direction;
	delay_ms(time_ms);
	ENA=1;
}
