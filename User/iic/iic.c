#include "iic.h"
#include "SysTick.h"
  
/* ???I2C */  
void IIC_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(IIC_SCL_PORT_RCC|IIC_SDA_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=IIC_SCL_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(IIC_SCL_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_PIN;
	GPIO_Init(IIC_SDA_PORT,&GPIO_InitStructure);
	
	IIC_SCL=1;
	IIC_SDA=1;	
}

/*******************************************************************************
* ? ? ?         : SDA_OUT
* ????		   : SDA????	   
* ?    ?         : ?
* ?    ?         : ?
*******************************************************************************/
void SDA_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(IIC_SDA_PORT,&GPIO_InitStructure);
}

/*******************************************************************************
* ? ? ?         : SDA_IN
* ????		   : SDA????	   
* ?    ?         : ?
* ?    ?         : ?
*******************************************************************************/
void SDA_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(IIC_SDA_PORT,&GPIO_InitStructure);
}

void IIC_Start(void)  
{  
    /* ??SDA???? */  
    SDA_OUT();       
      
    /* ?????????, ??SDA?SCL??? */  
    IIC_SDA = HIGH;         
    IIC_SCL = HIGH;  
      
    delay_us(5);  
      
    /* ??I2C????: SCL???, ?????????????? */  
    IIC_SDA = LOW;  
    delay_us(5);  
      
    /*  
    SCL?????, ????????, ????????????,  
    ??????????????????????????????  
    ?????????I2C?? 
    */  
    IIC_SCL = LOW;  
}  
  
/* ??I2C???? */  
void IIC_Stop(void)  
{  
    SDA_OUT();//sda???  
      
    /*  
    ??SCL???????SDA???????????????????  
    ??????I2C Start???????SCL?????, SDA???? 
    */  
    IIC_SCL = LOW;  
      
    /*  
        ?????SCL???, ???????????????SDA??,  
        ??????????? 
    */  
    IIC_SDA = LOW;  
      
    delay_us(5);  
      
    /* Okay, ??????????: ?????SCL??(??????? ??I2C????? 
    ???SCL?????????????????/?????????) */  
    IIC_SCL = HIGH;   
      
    /* ??, ???????SDA???, ????????????SDA??????? */  
    IIC_SDA = HIGH;  
    delay_us(5);                                  
}  
  
/* 
???????: 
Master????8bit???????Slave?ACK 
?????9?Clock, ???(Slave)IC??ACK, ??SDA???? 
????ACK, SDA????,?????Master??Restart??Stop?? 
*/  
/*  
    ???????? 
*/  
u8 IIC_Wait_Ack(void)  
{  
    u8 ucErrTime = 0;
		IIC_SCL=0;
	delay_us(2);
    IIC_SDA = HIGH;  
    delay_us(5);  
      
    /* ??SDA?????, ????SDA??ACK */  
    SDA_IN();        
    delay_us(2);
    /* ?SCL??, ?????? */  
    IIC_SCL = HIGH;  
    delay_us(5);      
      
    while(READ_SDA)  
    {  
        ucErrTime++;  
        if(ucErrTime > 250)  
        {//??????????IC?ACK, ??????  
            return FALSE;  
        }  
    }  
      
    /*  
    ??, ??????????????SDA??, ????ACK???  
    ?????????, ????SCL????(??? ????????? 
    SCL?????????) 
    */  
		delay_us(2);
    IIC_SCL = LOW;  
     delay_us(2);
    return TRUE;    
}  
  
/* 
 ??ACK????? 
 ?????????????IC??????????? 
 ??, ?IC?????Restart??Stop?? 
*/  
void IIC_Ack(void)  
{  
    /* ?????SCL???, ??SDA????I2C */  
    IIC_SCL = LOW;  
      
    /* ????????SDA?????, ?????? */  
    SDA_OUT();  
      
    /* SDA??, ?????????????, ??????? */  
    IIC_SDA = LOW;  
      
    delay_us(5);  
      
    /* SCL??, ????????????? */  
    IIC_SCL = HIGH;  
      
    delay_us(5);  
      
    /*  
    ????????, ??????, ?????ACK?? 
    ???????????? */  
    IIC_SCL = LOW;  
}  
  
/* 
??NACK, I2C????????: 
???9????????SDA??????, ?????NACK. 
Master????Stop?????????,????Start??? 
???????? 
*/  
void IIC_NAck(void)  
{  
    IIC_SCL = LOW;  
    SDA_OUT();  
      
    /* ????, ??SDA, ??NACK??? */  
    IIC_SDA = HIGH;  
    delay_us(5);  
      
    /* ?????, ??NACK???? */  
    IIC_SCL = HIGH;  
    delay_us(5);  
      
    /* SCL??, ???? */  
    IIC_SCL = LOW;  
}  
  
void IIC_Send_Byte(u8 txd)  
{                          
    u8 t;    
    /* ??????????, ????SDA????????? */      
    SDA_OUT();     
  
    /* ??????, ????????????? */      
    IIC_SCL = LOW;  
    for(t = 0; t < 8; t++)  
    {       
        /* I2C??????????, ???????? */  
        if((txd&0x80) >> 7)  
            IIC_SDA = HIGH;  
        else  
            IIC_SDA = LOW;  
          
        txd <<= 1;   
        /* ?????????? */          
        delay_us(5);     
          
        /* SCL?????? */  
        IIC_SCL = HIGH;  
          
        delay_us(5);  
          
        /* ??SCL, ???? */  
        IIC_SCL = LOW;    
          
        delay_us(5);  
    }      
}   
  
u8 IIC_Read_Byte(void)  
{  
    unsigned char i, receive = 0;  
      
    /* ??SDA??????, ?????? */  
    SDA_IN();  
      
    for(i = 0; i < 8; i++ )  
    {  
        /* SCL?? */  
        IIC_SCL = LOW;   
        delay_us(5);  
          
        /* ???SCL, ??????????? */  
        IIC_SCL = HIGH;  
          
        /* ???????? */  
        receive = (receive << 1) | READ_SDA;  
          
        delay_us(5);   
    }  
      
    return receive;  
}  

