#include "ad7705.h"
#include "spi.h"

void AD7705_Init(void){
	{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOF, ENABLE);
	
	/* FLASH_CS PG13 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);//???
	GPIO_SetBits(GPIOG,GPIO_Pin_13);
	
	/* SD_CS PG14 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOG, &GPIO_InitStructure);//???
	GPIO_SetBits(GPIOG,GPIO_Pin_14);
	
	/* ENC28J60_CS PB12 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//???
	GPIO_SetBits(GPIOB, GPIO_Pin_12); 
	
	/* AD7705 PF9 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//PF7
	GPIO_Init(GPIOF, &GPIO_InitStructure);//???
	GPIO_SetBits(GPIOF,GPIO_Pin_9);//PF9??1,??NRF??SPI FLASH???
	
	AD7705_CS=1;			//SPI FLASH???
	SPI2_Init();		   			//???SPI		
	//EN25QXX_TYPE=EN25QXX_ReadID();	//??FLASH ID.
}