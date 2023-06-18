#include "su_ne555.h"
#include <intrins.h>//_nop_机器周期延迟
#include <stc15f2k60s2.h>

uint32_t frequency=0;//频率

void Ne555TimInit(void)//NE555定时器初始化//1毫秒@12.000MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x20;		//设置定时初始值
	TH1 = 0xD1;		//设置定时初始值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	//开启中断
	ET1=1;//允许定时器0中断
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


