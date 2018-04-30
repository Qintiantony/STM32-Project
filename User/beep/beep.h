#ifndef _beep_H
#define _beep_H

#include "system.h"

#define BEEP_PORT GPIOB
#define BEEP_PIN GPIO_Pin_5
#define BEEP_PORT_RCC RCC_APB2Periph_GPIOB
#define beep PBout(5)
void BEEP_Init(void);
void BEEP_On(u32 duration_ms, u16 freq,u16 volume);
#endif