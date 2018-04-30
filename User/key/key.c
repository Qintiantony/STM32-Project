#include "key.h"
#include "SysTick.h"

void KEY_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	//Initiate KEY_UP
	GPIO_InitStructure.GPIO_Pin=KEY_UP_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD; //Input pulled down
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(KEY_UP_Port,&GPIO_InitStructure);
	//Initiate rest keys
	GPIO_InitStructure.GPIO_Pin=KEY_LEFT_Pin|KEY_DOWN_Pin|KEY_RIGHT_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; //Input pulled up
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(KEY_Port,&GPIO_InitStructure);
}

u8 KEY_Scan(u8 mode) //1 if continuous input
{
	static u8 key_block=0;
	if(key_block==0&&(KEY_UP_Read==1||KEY_LEFT_Read==0||KEY_DOWN_Read==0||KEY_RIGHT_Read==0))
	{
		delay_ms(10);
		key_block=1;
		if (KEY_UP_Read==1)
		{
			return KEY_UP;
		}
		else if (KEY_LEFT_Read==0)
		{
			return KEY_LEFT;
		}
		else if (KEY_DOWN_Read==0)
		{
			return KEY_DOWN;
		}
		else if (KEY_RIGHT_Read==0)
		{
			return KEY_RIGHT;
		}
	}
	else if(KEY_UP_Read==0&&KEY_LEFT_Read==1&&KEY_DOWN_Read==1&&KEY_RIGHT_Read==1)
	{
		key_block=0;
	}
	if(mode==1)
	{
		key_block=0;
	}
	return 0;
}