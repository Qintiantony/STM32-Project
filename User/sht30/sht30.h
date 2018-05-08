#ifndef _sht30_H
#define _sht30_H
#include "system.h"
#include "iic.h"
#define SHT30_Add_Write 0x88
#define SHT30_Add_Read 0x89

//#define SHT30_Add_Write 0x8A
//#define SHT30_Add_Read 0x8B

#define CMD_READ_SERIALNBR  0x3780
#define CMD_MEAS_PERI_1_H   0x2130
#define CMD_FETCH_DATA      0xE000
#define CMD_READ_STATUS     0xF32D

extern u8 SHT30_Data;
extern u8 sht_buffer[6];

void SHT30_Init(void);
void SHT30_Write_P(void);
void SHT30_Write_H(void);
void SHT30_Measure(void);
#endif