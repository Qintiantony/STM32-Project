#ifndef _time_H
#define _time_H
void TIM4_Init(u16 per, u16 psc); //per:reload;psc:divider
void TIM4_IRQHandler(void);
#endif