#ifndef _motor_H
#define _motor_H
#include "pwm.h"
#include "SysTick.h"
#define DIR_Pin GPIO_Pin_2
#define ENA_Pin GPIO_Pin_3
#define DIR_ENA_Port GPIOG
#define DIR_ENA_RCC RCC_APB2Periph_GPIOG
#define DIR PGout(2)
#define ENA PGout(3)
// PUL_Pin GPIOC_Pin6 AFIO predefined by pwm
void MOTOR_Init(void);
void MOTOR_Run(u32 time_ms, u8 Direction);
#endif