#ifndef _laser_H
#define _laser_H
#include "system.h"
#define Laser_ScanPin GPIO_Pin_10
#define Laser_ScanPort GPIOF
#define Laser_ScanWrite PFout(10)
void Laser_ScanInit(void);
#endif