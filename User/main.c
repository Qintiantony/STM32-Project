#include "system.h"
#include "led.h"
#include "beep.h"
#include "SysTick.h"
#include "key.h"
#include "exti.h"
#include "time.h"
#include "pwm.h"
#include "usart.h"
#include "tftlcd.h"
#include "dht11.h"

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
TIM4_Init(1000,36000-1); //2Hz
TIM3_CH1_PWM_Init(500,72-1); //2kHz
USART1_Init(9600);
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
	while(1)
	{
		u8 buffer[5];
		double hum=0;
		double temp=0;
		unsigned char string_out[20];
		if(DHT11_ReadData(buffer)==1)
		{
			hum=buffer[0]+buffer[1]/10.0;
			temp=buffer[2]+buffer[3]/10.0;
			printf("Humidity=%lf %%RH\r\n", hum);
			printf("Temperature=%lf C\r\n",temp);
			sprintf(string_out,"Humidity=%lf %%RH\r\n", hum);
			printf(string_out);
			LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,string_out);
			sprintf(string_out,"Temperature=%lf C\r\n",temp);
			printf(string_out);
			LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,string_out);
		}
		delay_ms(1000);
	}
}
