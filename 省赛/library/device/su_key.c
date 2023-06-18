#include <stc15f2k60s2.h>
#include "su_key.h"


//读取矩阵键盘
uint8_t	ReadKeyBoard(void)
{
	uint8_t key_value = 0;
	P30=P31=P32=P33=P34=P35=P42=P44=1;
	//第三排
	P32=0;
	if(P42==0)
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
	if(P42==0)
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

