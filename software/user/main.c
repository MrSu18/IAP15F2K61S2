#include "su_led.h"
#include "su_key.h"
#include "su_common_typedef.h"
#include "delay.h"
#include "timer.h"

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

void Time0Isr() interrupt 1	//定时器0中断回调函数
{
	static uint8_t num=0;
	if(num<100)
	{
		num++;
	}
	else
	{
		LED1=~LED1;//中断服务函数，如果是定时器没有自动重装载的话记得在这里重装初始，即设置：TH0和TL0的值
		num=0;
	}
}

