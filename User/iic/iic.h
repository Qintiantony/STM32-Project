#ifndef _iic_H
#define _iic_H

#include "system.h"

#define HIGH 1  
#define LOW 0  
  
#define TRUE 1  
#define FALSE 0
  
/*  IIC_SCL????????? */
#define IIC_SCL_PORT 			GPIOF   
#define IIC_SCL_PIN 			(GPIO_Pin_10)
#define IIC_SCL_PORT_RCC		RCC_APB2Periph_GPIOF

/*  IIC_SDA????????? */
#define IIC_SDA_PORT 			GPIOF  
#define IIC_SDA_PIN 			(GPIO_Pin_11)
#define IIC_SDA_PORT_RCC		RCC_APB2Periph_GPIOF

#define IIC_SCL    PFout(10) //SCL  
#define IIC_SDA    PFout(11) //SDA      
#define READ_SDA   PFin(11)  //??SDA  

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(void);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�


#endif