#ifndef _usart_H
#define _usart_H
#include "system.h"
#include "stdio.h"

extern u8 rx_buffer[8];

void USART1_Init(u32 bound);
void USART1_IRQHandler(void);
int fputc(int ch, FILE *p);
#endif