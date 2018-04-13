#include "stm32f10x.h"
#define LED_PORT GPIOC
#define LED_PIN (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
#define LED_PORT_RCC RCC_APB2Periph_GPIOC

void LED_Init(){
	GPIO_InitTypeDef(GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(LED_PORT_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin=LED_PIN; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //????????
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //??????
	GPIO_Init(LED_PORT,&GPIO_InitStructure); /* ??? GPIO */
	GPIO_SetBits(LED_PORT,LED_PIN); //? LED ????,???? LED
}

void delay_ms(u16 time){
	u16 i=0;
	while(time--)
	{
		i=10000;
		while(i--);
	}
}

int main(void){
	u16 GPIO_Pin_lit=GPIO_Pin_0;
	u16 counter=0;
LED_Init();
	while(1){
		GPIO_ResetBits(LED_PORT,GPIO_Pin_lit);
		delay_ms(100);
		GPIO_SetBits(LED_PORT,GPIO_Pin_lit);
		GPIO_Pin_lit=GPIO_Pin_lit<<1;
		counter++;
		if(counter==8){
			GPIO_Pin_lit=GPIO_Pin_0;
			counter=0;
		}
		
	}
}