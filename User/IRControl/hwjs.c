#include "hwjs.h"
#include "SysTick.h"
#include "beep.h"
#include "motor.h"
#include "sht30.h"
#include "dac.h"
#include "adc.h"
#include "laser.h"

u32 hw_jsm;	  //����һ��32λ���ݱ��������������
u8  hw_jsbz;  //����һ��8λ���ݵı���������ָʾ���ձ�־
u16 dac_value=0;
u8 Current_Status;
u8 FiberLock_Status=0;


/*******************************************************************************
* �� �� ��         : Hwjs_Init
* ��������		   : ����˿ڳ�ʼ������	  ʱ�Ӷ˿ڼ��ⲿ�жϳ�ʼ�� 
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Hwjs_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* ����GPIOʱ�Ӽ��ܽŸ���ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;//�������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, GPIO_PinSource15); //ѡ��GPIO�ܽ������ⲿ�ж���·
	EXTI_ClearITPendingBit(EXTI_Line15);
	
	/* �����ⲿ�жϵ�ģʽ */ 
	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure); 

	/* ����NVIC���� */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;   //��ȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 	 //��Ӧ���ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   //ʹ��
	NVIC_Init(&NVIC_InitStructure);

}


/*******************************************************************************
* �� �� ��         : HW_jssj
* ��������		   : �ߵ�ƽ����ʱ�䣬����¼��ʱ�䱣����t�з��أ�����һ�δ�Լ20us 
* ��    ��         : ��
* ��    ��         : t
*******************************************************************************/
u8 HW_jssj()
{
	u8 t=0;
	while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_15)==1)//�ߵ�ƽ
	{
		t++;
		delay_us(20);
		if(t>=250) return t;//��ʱ���
	}
	return t;
}


void EXTI15_10_IRQHandler(void)	  //����ң���ⲿ�ж�
{
	u8 Tim=0,Ok=0,Data,Num=0;

   while(1)
   {
	   	if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_15)==1)
		{
			 Tim=HW_jssj();//��ô˴θߵ�ƽʱ��

			 if(Tim>=250) break;//�������õ��ź�

			 if(Tim>=200 && Tim<250)
			 {
			 	Ok=1;//�յ���ʼ�ź�
			 }
			 else if(Tim>=60 && Tim<90)
			 {
			 	Data=1;//�յ����� 1
			 }
			 else if(Tim>=10 && Tim<50)
			 {
			 	Data=0;//�յ����� 0
			 }

			 if(Ok==1)
			 {
			 	hw_jsm<<=1;
				hw_jsm+=Data;

				if(Num>=32)
				{
					hw_jsbz=1;
				  	break;
				}
			 }

			 Num++;
		}
   }

   EXTI_ClearITPendingBit(EXTI_Line15);	
	 if(hw_jsbz==1)
	 {
		 if(Current_Status==0)
			 {
				 if(hw_jsm==IR_Key_1)
				 {
					 Current_Status=1;
					 hw_jsbz=0;
					 hw_jsm=0;
				 }
				 if(hw_jsm==IR_Key_3)
				 {
					 Current_Status=3;
					 hw_jsbz=0;
					 hw_jsm=0;
				 }
				 if(hw_jsm==IR_Key_4)
				 {
					 Current_Status=4;
					 hw_jsbz=0;
					 hw_jsm=0;
				 }
				 if(hw_jsm==IR_Key_5)
				 {
					 Current_Status=5;
					 hw_jsbz=0;
					 hw_jsm=0;
				 }
			 }
			if(Current_Status==1)
			 {
				 if(hw_jsm==IR_Key_0)
				 {
					 Current_Status=0;
					 hw_jsbz=0;
					 hw_jsm=0;
				 }
			 }
			if(Current_Status==3)
			{
				if(hw_jsm==0x00FFC23D)
				{
					MOTOR_Run(500,0);
					BEEP_On(100,1000,50);
					hw_jsbz=0;
					hw_jsm=0;
				}
				else if(hw_jsm==0x00FF02FD)
				{
					MOTOR_Run(500,1);
					BEEP_On(100,1000,50);
					hw_jsbz=0;
					hw_jsm=0;
				}
				else if(hw_jsm==IR_Key_0)
				{
					 Current_Status=0;
					 hw_jsbz=0;
					 hw_jsm=0;
				}
			}
			if(Current_Status==4)
			{
				if(hw_jsm==IR_Key_1)
				{
					dac_value+=10;
					DAC1_SetValue(dac_value);
					hw_jsbz=0;
					hw_jsm=0;
				}
				else if(hw_jsm==IR_Key_2)
				{
					dac_value-=10;
					DAC1_SetValue(dac_value);
					hw_jsbz=0;
					hw_jsm=0;
				}
				else if(hw_jsm==IR_Key_3)
				{
					dac_value=1500;
					DAC1_SetValue(dac_value);
					hw_jsbz=0;
					hw_jsm=0;
				}
				else if(hw_jsm==IR_Key_RunStop)
				{
					FiberLock_Status=1;
					hw_jsbz=0;
					hw_jsm=0;
				}
				else if(hw_jsm==IR_Key_EQ)
				{
					FiberLock_Status=0;
					hw_jsbz=0;
					hw_jsm=0;
				}
				else if(hw_jsm==IR_Key_0)
				{
					 Current_Status=0;
					 hw_jsbz=0;
					 hw_jsm=0;
				}
			}
			if(Current_Status==5)
			{
				if(hw_jsm==IR_Key_RunStop)
				{
					Laser_ScanWrite=1;
					delay_ms(10);
					Laser_ScanWrite=0;
					hw_jsbz=0;
					hw_jsm=0;
				}
				else if(hw_jsm==IR_Key_0)
				{
					 Current_Status=0;
					 hw_jsbz=0;
					 hw_jsm=0;
				}
			}
	 }
	 
}



