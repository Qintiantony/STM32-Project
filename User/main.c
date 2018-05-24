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
#include "iic.h"
#include "sht30.h"
#include "dac.h"
#include "laser.h"
#include "spi.h"
#include "adc.h"


int main(void){
SysTick_Init(72);
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
LED_Init();
BEEP_Init();
KEY_Init();
KEY_EXTI_Init();
//TIM4_Init(1000,36000-1); //2Hz
TIM3_CH1_PWM_Init(1000-1,360-1); //1kHz
TIM4_CH1_PWM_Init(1000-1,720-1); //1kHz
TIM_SetCompare1(TIM3,500);
TIM_SetCompare1(TIM4,500);
MOTOR_Init();
USART1_Init(115200);
	Hwjs_Init();
DAC1_Init();
//Laser_ScanInit();
TFTLCD_Init();
SHT30_Init();
delay_us(250);
SHT30_Write_P();
SHT30_Write_H();
delay_us(150);
ADCx_Init();
TIM4_CH1_PWM_State(0);
//IIC_Init();
//IIC_Start();
	
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
FiberLock_Status=0;
u8 Previous_Status=0;
u8 Fan_State=0;
u8 CoupleControl_Status=0;
u8 DHT11_Counter=20;
LCD_Clear(BLACK);
double hum=0;
double temp=0;
double sht_hum=0;
double sht_tem=0;
u16 adc_value=0;
float adc_vol=0;
float target_vol=0;
	while(1)
	{
		u8 buffer[5];
		unsigned char str_hum[10];
		unsigned char str_tem[10];
		unsigned char str_sht[10];
		unsigned char IR_code[10];
		unsigned char ADC_str[10];
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
				LCD_ShowString(10,200,tftlcd_data.width,tftlcd_data.height,16,"3. Tapered Fiber Control");
				LCD_ShowString(10,230,tftlcd_data.width,tftlcd_data.height,16,"4. Coupling Adjustment");
				TIM4_CH1_PWM_State(0);
				Fan_State=0;
				CoupleControl_Status=0;
				break;
			}
			case 1:
			{
				LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,24,"Temp & Humi");
				LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,16,"Sensor 1:");
				LCD_ShowString(10,220,tftlcd_data.width,tftlcd_data.height,16,"Sensor 2:");
				DHT11_Counter++;
				if(DHT11_Counter>10)
				{
					DHT11_Counter=0;
				if(DHT11_ReadData(buffer)==1)
				{
					DHT11_Counter=0;
					hum=buffer[0]+buffer[1]/10.0;
					temp=buffer[2]+buffer[3]/10.0;
					//printf("Humidity=%lf %%RH\r\n", hum);
					//printf("Temperature=%lf C\r\n",temp);
					sprintf(str_hum,"Humi=%2.2lf",hum);
					//printf(str_hum);
					LCD_ShowString(20,80,tftlcd_data.width,tftlcd_data.height,16,str_hum);
					sprintf(str_tem,"Temp=%2.2lf",temp);
					//printf(str_tem);
					LCD_ShowString(20,110,tftlcd_data.width,tftlcd_data.height,16,str_tem);
					
				}
				SHT30_Measure();
				sht_hum=(float)(sht_buffer[3]<<8|sht_buffer[4])/655.35;
				sht_tem=(float)(sht_buffer[0]<<8|sht_buffer[1])*175/65535-45;
				sprintf(str_sht,"SHTH=%2.2lf",sht_hum);
				printf(str_sht);
				LCD_ShowString(20,250,tftlcd_data.width,tftlcd_data.height,16,str_sht);
				sprintf(str_sht,"SHTT=%2.2lf",sht_tem);
				printf(str_sht);
				LCD_ShowString(20,280,tftlcd_data.width,tftlcd_data.height,16,str_sht);
			}
				if((sht_hum>25.0)&&(Fan_State==0))
						{
							TIM4_CH1_PWM_State(1);
							Fan_State=1;
						}
						else if((sht_hum<22.0)&&(Fan_State==1))
						{
							TIM4_CH1_PWM_State(0);
							Fan_State=0;
						}
						if(Fan_State==1)
						{
							LCD_ShowString(10,320,tftlcd_data.width,tftlcd_data.height,16,"Fan is running...");
						}
						else
						{
							LCD_ShowString(10,320,tftlcd_data.width,tftlcd_data.height,16,"Fan is stopped...");
						}
				LCD_ShowString(10,350,tftlcd_data.width,tftlcd_data.height,16,"PRESS 0 to MAIN screen");
				break;
			}
			case 3:
			{
				LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,24,"Fiber Control");
				LCD_ShowString(20,80,tftlcd_data.width,tftlcd_data.height,12,"Press |<< to loosen the fiber");
				LCD_ShowString(20,110,tftlcd_data.width,tftlcd_data.height,12,"Press >>| to tighten the fiber");
				LCD_ShowString(10,350,tftlcd_data.width,tftlcd_data.height,16,"PRESS 0 to MAIN screen");
				break;
			}
			case 4:
			{
				if(CoupleControl_Status==0)
				{
				LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,24,"Couple Adjustment");
				CoupleControl_Status=1;
				}
				adc_value=Get_ADC_Value(ADC_Channel_3,50);
				adc_vol=(float)adc_value*(3.3/4096);
				sprintf(ADC_str,"Aval=%.3f",adc_vol);
				LCD_ShowString(10,40,tftlcd_data.width,tftlcd_data.height,16,ADC_str);
				//printf(ADC_str);
				if(FiberLock_Status==1)
				{
					if(target_vol==0)
						{
							target_vol=adc_vol;
						}
					dac_value=(int)(dac_value+adc_vol*150-target_vol*150);
						DAC1_SetValue(dac_value);
				}
				else target_vol=0;
				sprintf(ADC_str,"Dval=%d",dac_value);
				LCD_ShowString(10,70,tftlcd_data.width,tftlcd_data.height,16,ADC_str);
				//printf(ADC_str);
				break;
			}
			
			case 5:
			{
				LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,24,"Laser Control");
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
		delay_ms(100);
	}
}
