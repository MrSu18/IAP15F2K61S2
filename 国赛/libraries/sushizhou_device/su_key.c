#include <stc15f2k60s2.h>
#include "su_key.h"

//独立按键扫描函数
//使用的时候判断条件是(ReadKey()!=0xff),等待按键释放也是这个
uint8_t ReadKey(void)
{
    uint8_t temp;
    uint8_t key_value = 0;
    
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


//读取矩阵键盘
//如果要检测按键松开，那么这里的key_value应该默认是255，然后三行按键key_up=~key_down
uint8_t	ReadKeyBoard(void)
{
	uint8_t key_value = 0;
	P30=P31=P32=P33=P34=P35=P42=P44=1;
	//第三排
	P32=0;
	if(P42==0)
	{
		key_value=9;
		P32=1;
		//检测S8
		P33=0;
		if(P42==0)//说明是一起按下的
		{
			key_value=10;
		}
		P33=1;
		return key_value;
	}
	else if(P44==0)
	{
		key_value=5;
	}
	P32=1;
	//第四排
	P33=0;
	if(P42==0)
	{
		key_value=8;
		P33=1;
		//检测S9
		P32=0;
		if(P42==0)//说明是一起按下的
		{
			key_value=10;
		}
		P32=1;
		return key_value;
	}
	else if(P44==0)
	{
		key_value=4;
	}
	P33=1;
	
	return key_value;
}



