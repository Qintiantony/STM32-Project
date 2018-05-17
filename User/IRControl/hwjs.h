#ifndef _hwjs_H
#define _hwjs_H

#include "system.h"
#define IR_Key_0 0x00FF6897
#define IR_Key_2 0x00FF18E7
#define IR_Key_1 0x00FF30CF
#define IR_Key_3 0x00FF7A85
#define IR_Key_4 0x00FF10EF
#define IR_Key_5 0x00FF38C7
#define IR_Key_RunStop 0x00FF22DD
#define IR_Key_EQ 0x00FFE01F




void Hwjs_Init(void);
u8 HW_jssj(void);

//定义全局变量
extern u32 hw_jsm;
extern u8  hw_jsbz;
extern u8 Current_Status;
extern u8 FiberLock_Status;
extern u16 dac_value;

#endif
