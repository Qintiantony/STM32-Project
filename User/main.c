#include "system.h"
#include "led.h"
#include "beep.h"
#include "SysTick.h"
#include "key.h"
#include "exti.h"
//#include "time.h"
#include "pwm.h"
#include "usart.h"
#include "tftlcd.h"
#include "dht11.h"
#include "motor.h"
#include "hwjs.h"


int main(void){
	u8 key=0;
	u8 fx=0;
	u16 i=0;
SysTick_Init(72);
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
LED_Init();
BEEP_Init();
KEY_Init();
KEY_EXTI_Init();
//TIM4_Init(1000,36000-1); //2Hz
TIM3_CH1_PWM_Init(1000-1,720-1); //1kHz
TIM4_CH1_PWM_Init(1000-1,720-1); //1kHz
TIM_SetCompare1(TIM3,500);
TIM_SetCompare1(TIM4,32);
MOTOR_Init();
USART1_Init(9600);
	Hwjs_Init();
TFTLCD_Init();
		/*GPIO_ResetBits(LED_PORT,GPIO_Pin_lit);
		delay_ms(100);
		GPIO_SetBits(LED_PORT,GPIO_Pin_lit);
		GPIO_Pin_lit=GPIO_Pin_lit<<1;
		counter++;
		if(counter==8){
			GPIO_Pin_lit=GPIO_Pin_0;
			counter=0;
		}
		*/
		//beep=!beep;
		//delay_ms(10);
//LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"Hello World!");
//LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"Read Data");
FRONT_COLOR=WHITE;
BACK_COLOR=BLACK;
Current_Status=0;
u8 Previous_Status=0;
LCD_Clear(BLACK);
	while(1)
	{
		u8 buffer[5];
		double hum=0;
		double temp=0;
		unsigned char str_hum[10];
		unsigned char str_tem[10];
		unsigned char IR_code[10];
		if(Current_Status!=Previous_Status)
		{
			Previous_Status=Current_Status;
			LCD_Clear(BLACK);
		}
		switch(Current_Status)
		{
			case 0:
			{
				LCD_ShowString(10,100,tftlcd_data.width,tftlcd_data.height,24,"Welcome to QTC");
				LCD_ShowString(10,140,tftlcd_data.width,tftlcd_data.height,16,"1. Temperature & Humidity");
				LCD_ShowString(10,170,tftlcd_data.width,tftlcd_data.height,16,"2. Tapered Fiber Lock");
				break;
			}
			case 1:
			{
				LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,24,"Temp & Humi");
				LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,16,"Sensor 1:");
				if(DHT11_ReadData(buffer)==1)
				{
					hum=buffer[0]+buffer[1]/10.0;
					temp=buffer[2]+buffer[3]/10.0;
					//printf("Humidity=%lf %%RH\r\n", hum);
					//printf("Temperature=%lf C\r\n",temp);
					sprintf(str_hum,"Humi=%2.2lf",hum);
					printf(str_hum);
					LCD_ShowString(20,80,tftlcd_data.width,tftlcd_data.height,16,str_hum);
					sprintf(str_tem,"Temp=%2.2lf",temp);
					printf(str_tem);
					LCD_ShowString(20,110,tftlcd_data.width,tftlcd_data.height,16,str_tem);
				}
				LCD_ShowString(10,350,tftlcd_data.width,tftlcd_data.height,16,"PRESS 0 to MAIN screen");
			}
		}
		
		if(hw_jsbz==1)
		{
			hw_jsbz=0;
			sprintf(IR_code,"IR code: %0.8X",hw_jsm);
			LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,16,IR_code);
			hw_jsm=0;
		}
		
		//MOTOR_Run(500,1);
		PCout(0)=!PCout(0);
		//printf("Test\r\n");
		delay_ms(1000);
	}
}
