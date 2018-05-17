//Define dac
#include "dac.h"
#include "SysTIck.h"

void DAC1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;//DAC1
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	DAC_InitStructure.DAC_Trigger=DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;
	DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Disable;
	DAC_Init(DAC_Channel_1,&DAC_InitStructure);
	
	DAC_SetChannel1Data(DAC_Align_12b_R,0);
	DAC_Cmd(DAC_Channel_1,ENABLE);
}

void DAC1_SetValue(u16 value)
{
	if(value<0)
		value=0;
	if(value>4095)
		value=4095;
	DAC_SetChannel1Data(DAC_Align_12b_R,value);
}