//SHT30 driver
#include "sht30.h"
#include "SysTick.h"
u8 SHT30_Data=0;
u8 sht_buffer[6];
void SHT30_Init(void){
	IIC_Init();
}

void SHT30_Write_P(void)
{
	IIC_Start();
	IIC_Send_Byte(SHT30_Add_Write);
	IIC_Wait_Ack();
	IIC_Send_Byte(CMD_MEAS_PERI_1_H >>8);
	IIC_Wait_Ack();
	IIC_Send_Byte(CMD_MEAS_PERI_1_H%256);
	IIC_Wait_Ack();
	IIC_Stop();
}
void SHT30_Write_H(void)
{
	IIC_Start();
	IIC_Send_Byte(SHT30_Add_Write);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x3066 >>8);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x3066%256);
	IIC_Wait_Ack();
	IIC_Stop();
}

void SHT30_Measure(void)
{
	SHT30_Data=0;
	IIC_Start();
	IIC_Send_Byte(SHT30_Add_Write);
	IIC_Wait_Ack();
	IIC_Send_Byte(CMD_FETCH_DATA >>8);
	IIC_Wait_Ack();
	IIC_Send_Byte(CMD_FETCH_DATA%256);
	IIC_Wait_Ack();
	IIC_Stop();
	IIC_Start();
	IIC_Send_Byte(SHT30_Add_Read);
	IIC_Wait_Ack();
	sht_buffer[0]=IIC_Read_Byte();
	IIC_Ack();
  sht_buffer[1]=IIC_Read_Byte();
	IIC_Ack();
  sht_buffer[2]=IIC_Read_Byte();
	IIC_Ack();
	sht_buffer[3]=IIC_Read_Byte();
	IIC_Ack();	
	sht_buffer[4]=IIC_Read_Byte();
	IIC_Ack();
	sht_buffer[5]=IIC_Read_Byte();
	IIC_NAck();
  IIC_Stop();
}