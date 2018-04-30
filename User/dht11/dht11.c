//Driver for DHT11
#include "dht11.h"
#include "tftlcd.h"

void DHT11_ConfigIn(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=DHT11_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(DHT11_Port,&GPIO_InitStructure);
}

void DHT11_ConfigOut(void)
{
	RCC_APB2PeriphClockCmd(DHT11_RCC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=DHT11_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(DHT11_Port,&GPIO_InitStructure);
}

void DHT11_Reset(void)
{
	DHT11_ConfigOut();
	DHT11_Set=0;
	delay_ms(19);
	DHT11_Set=1;
	delay_us(30);
	DHT11_ConfigIn();
}
u16 DHT11_Scan(void)
{
	return DHT11_Read;
}

u16 DHT11_ReadBit(void)
{
	while(DHT11_Read==RESET);
	delay_us(40);
	if(DHT11_Read==SET)
	{
		while(DHT11_Read==SET);
		return 1;
	}
	else{
		return 0;
	}
}

u16 DHT11_ReadByte(void)
{
	u16 i;
	u16 data=0;
	for(i=0;i<8;i++)
	{
		data<<=1;
		data|=DHT11_ReadBit();
	}
	return data;
}

u16 DHT11_ReadData(u8 buffer[5])
{
	u16 i=0;
	DHT11_Reset();
	//LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"Read Data");
	if (DHT11_Scan()==RESET)
	{
		//LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"Read Data");
		while(DHT11_Scan()==RESET);
		while(DHT11_Scan()==SET);
		for (i=0;i<5;i++)
		{
			buffer[i]=DHT11_ReadByte();
		}
		while (DHT11_Scan()==RESET);
		DHT11_ConfigOut();
		DHT11_Set=1;
		
		u8 check=buffer[0]+buffer[1]+buffer[2]+buffer[3];
		if (check==buffer[4])
		{
			return 1;
		}
	}
	return 0;
}