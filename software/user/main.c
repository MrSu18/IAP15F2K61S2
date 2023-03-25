#include "su_S12.h"
#include "su_usart.h"
#include "delay.h"
#include "su_ds18b20.h"
#include "su_key.h"

void main(void)
{	
	unsigned char temp=0;
	DeviceInit();//设备初始化
	UartInit();//串口初始化用于调试
	
	while(1)
	{
		temp=ReadKeyBoard();
		if(temp!=0xff)
		{
			printf("%bu\r\n",temp);
			while(ReadKeyBoard()!=0xff);
		}
		Delay200ms();
	}
}



