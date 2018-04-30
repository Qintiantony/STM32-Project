#ifndef _dht11_H
#define _dht11_H
#include "system.h"
#include "SysTick.h"
#include "usart.h"

#define DHT11_Pin GPIO_Pin_1
#define DHT11_Port GPIOG
#define DHT11_RCC RCC_APB2Periph_GPIOG

#define DHT11_Set PGout(1)
#define DHT11_Read PGin(1)//DHT11_Read GPIO_ReadInputDataBit(DHT11_Port,DHT11_Pin)

void DHT11_ConfigOut(void);
void DHT11_ConfigIn(void);
void DHT11_Reset(void);
u16 DHT11_Scan(void);
u16 DHT11_ReadBit(void);
u16 DHT11_ReadByte(void);
u16 DHT11_ReadData(u8 buffer[4]);
#endif