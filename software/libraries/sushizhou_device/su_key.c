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
