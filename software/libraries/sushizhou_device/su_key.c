#include <stc15f2k60s2.h>
#include "su_key.h"

//独立按键扫描函数
//使用的时候判断条件是(ReadKey()!=0xff),等待按键释放也是这个
uint8_t ReadKey(void)
{
    uint8_t temp;
    uint8_t key_value = 0xff;
    
    temp = P3&0x0f;//把高四位清零
    switch(temp)
    {
        case 0x0e:
			key_value = 1;  //S7
            break;    
        case 0x0d:
			key_value = 2;  //S6
            break;    
        case 0x0b:
			key_value = 3;  //S5
            break;    
        case 0x07:
			key_value = 4;  //S4
            break;    
    }
    return key_value;
}

/****************************************独立按键测试程序***************************************
void main(void)
{
	uint8_t temp;
    ENABLE_LED_LATCH;
	while (1)
    {
		temp=ReadKey();
		if(temp!=0xff)
		{
			Delay10ms();
			temp=ReadKey();
			if(temp!=0xff)
			{
				switch(temp)
				{
					case 1: LED1=!LED1;break;
					case 2: LED2=!LED2;break;
					case 3: LED3=!LED3;break;
					case 4: LED4=!LED4;break;
					default: LED5=!LED5;break;
				}
				while(ReadKey()!=0xff);
			}
		}
    }
}
************************************************************************************************/

//读取矩阵键盘
uint8_t	ReadKeyBoard(void)
{
	uint8_t key_value = 0xff;
	P30=P31=P32=P33=P34=P35=P42=P44=1;
	//第一排
	P30=0;
	if(P34==0)
	{
		key_value=19;
	}
	else if(P35==0)
	{
		key_value=15;
	}
	else if(P42==0)
	{
		key_value=11;
	}
	else if(P44==0)
	{
		key_value=7;
	}
	P30=1;
	//第二排
	P31=0;
	if(P34==0)
	{
		key_value=18;
	}
	else if(P35==0)
	{
		key_value=14;
	}
	else if(P42==0)
	{
		key_value=10;
	}
	else if(P44==0)
	{
		key_value=6;
	}
	P31=1;
	//第三排
	P32=0;
	if(P34==0)
	{
		key_value=17;
	}
	else if(P35==0)
	{
		key_value=13;
	}
	else if(P42==0)
	{
		key_value=9;
	}
	else if(P44==0)
	{
		key_value=5;
	}
	P32=1;
	//第四排
	P33=0;
	if(P34==0)
	{
		key_value=16;
	}
	else if(P35==0)
	{
		key_value=12;
	}
	else if(P42==0)
	{
		key_value=8;
	}
	else if(P44==0)
	{
		key_value=4;
	}
	P33=1;
	
	return key_value;
}

/****************************************矩阵按键测试程序***************************************
void main(void)
{
	uint8_t temp;
    ENABLE_LED_LATCH;
	while (1)
    {
		temp=ReadKeyBoard();
		if(temp!=0xff)
		{
			Delay10ms();
			temp=ReadKeyBoard();
			if(temp!=0xff)
			{
				switch(temp)
				{
					case 1: LED1=!LED1;break;
					case 2: LED2=!LED2;break;
					case 3: LED3=!LED3;break;
					case 4: LED4=!LED4;break;
					default: LED5=!LED5;break;
				}
				while(ReadKeyBoard()!=0xff);
			}
		}
		else
		{
			LED6=!LED6;
			Delay500ms();
		}
    }
}
************************************************************************************************/
