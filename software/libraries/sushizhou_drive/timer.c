#include "timer.h"
#include <stc15f2k60s2.h>
#include "su_led.h"
#include "su_common_typedef.h"

void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xCD;				//设置定时初始值
	TH0 = 0xD4;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	
	/*上述的代码是ISP工具生成的定时器的模式初值设置代码，如果要开启中断则要自己写下面两句，开启中断*/
	
	EA=1;//开启总中断
	ET0=1;//开启定时器0中断
}

void Time0_Sever() interrupt 1	//定时器0中断回调函数
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
