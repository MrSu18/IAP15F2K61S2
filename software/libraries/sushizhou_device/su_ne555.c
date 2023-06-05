#include "su_ne555.h"
#include <intrins.h>//_nop_机器周期延迟
#include <stc15f2k60s2.h>

uint16_t frequency=0;//频率

void Ne555TimInit(void)//NE555定时器初始化//200us@12.000MHz
{
	AUXR &= 0xFB;			//定时器时钟12T模式
	T2L = 0x38;				//设置定时初始值
	T2H = 0xFF;				//设置定时初始值
	AUXR |= 0x10;			//定时器2开始计时
	/*上述的代码是ISP工具生成的定时器的模式初值设置代码，如果要自己设置定时器中断允许和开启EA总中断*/
	IE2 |=0x04;//允许定时器2中断
}

void Ne555CountInit(void)//NE555记数器初始化//1毫秒@12.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x05;		//设置定时器模式，设置成计数器模式，并且不自动重装载
	TL0 = 0;		//设置定时初始值
	TH0 = 0;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}


