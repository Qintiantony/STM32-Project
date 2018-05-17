#include "laser.h"
#include "SysTick.h"

void Laser_ScanInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
	GPIO_InitStructure.GPIO_Pin=Laser_ScanPin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(Laser_ScanPort,&GPIO_InitStructure);
	Laser_ScanWrite=0;
}