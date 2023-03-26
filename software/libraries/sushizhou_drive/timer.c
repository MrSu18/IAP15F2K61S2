#include "timer.h"
#include <stc15f2k60s2.h>
#include "su_led.h"
#include "su_common_typedef.h"
#include "su_S12.h"
#include "su_key.h"
#include "su_ds18b20.h"//温度传感器
#include "su_ds1302.h"//实时时钟模块
#include "su_digital_tube.h"

void Timer0Init(void)		//1毫秒@12.000MHz
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x20;				//设置定时初始值
	TH0 = 0xD1;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	
	/*上述的代码是ISP工具生成的定时器的模式初值设置代码，如果要开启中断则要自己写下面两句，开启中断*/
	
	ET0=1;//开启定时器0中断
}

void Time0_Sever() interrupt 1	//定时器0中断回调函数
{
	//===========动态刷新数码管一次中断就刷新一位==================
	static uint8_t i=0;
	DigitalTubeDisplay(i,~digitaltube_show[i]);
	i++;
	if(i==8) i=0;
	//==============================================================
	
	if(cnt1==900)//1S中读一次传感器
	{
		cnt1=0;
	}
	if(cnt2==100)//0.1s读一次按键
	{
		cnt2=0;
	}
	cnt1++;cnt2++;
}
