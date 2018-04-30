#include "beep.h"
#include "SysTick.h"

void BEEP_Init()
{
GPIO_InitTypeDef GPIO_InitStructure; 
RCC_APB2PeriphClockCmd(BEEP_PORT_RCC,ENABLE); 
GPIO_InitStructure.GPIO_Pin=BEEP_PIN; 
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; 
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; 
GPIO_Init(BEEP_PORT,&GPIO_InitStructure); 
}

void BEEP_On(u32 duration_ms, u16 freq, u16 volume)
{
	int beep_cycle=1000000/freq; //Single cycle duration in us
	int beep_duration=0; //Count in us
	int beep_on_us=beep_cycle*volume/200;
	while(beep_duration <(1000*duration_ms))
	{
		beep=1;
		delay_us(beep_on_us);
		beep=0;
		delay_us(beep_cycle-beep_on_us);
		beep_duration+=beep_cycle;
	}
}