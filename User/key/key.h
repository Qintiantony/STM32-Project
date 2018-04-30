#ifndef _key_H
#define _key_H

#include "system.h"

//Define pin and port of keys
#define KEY_UP_Pin GPIO_Pin_0
#define KEY_UP_Port GPIOA
#define KEY_LEFT_Pin GPIO_Pin_2
#define KEY_DOWN_Pin GPIO_Pin_3
#define KEY_RIGHT_Pin GPIO_Pin_4
#define KEY_Port GPIOE


//Define input by bit
#define KEY_UP_Read PAin(0)
#define KEY_DOWN_Read PEin(3)
#define KEY_LEFT_Read PEin(2)
#define KEY_RIGHT_Read PEin(4)

//Define key value
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4

void KEY_Init(void);
u8 KEY_Scan(u8 mode);

#endif