#include "timer.h"
#include <stc15f2k60s2.h>
#include "su_led.h"
#include "su_common_typedef.h"
#include "su_S12.h"
#include "su_key.h"
#include "su_ds18b20.h"//温度传感器
#include "su_ds1302.h"//实时时钟模块
#include "su_digital_tube.h"
#include "su_ne555.h"

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
//	S13TimeServer();
}

void Time1_Sever()	interrupt 3//定时器1中断回调函数
{
	static uint16_t ne555_cnt=0;
	//===========动态刷新数码管一次中断就刷新一位==================
	static uint8_t i=0;
	DigitalTubeDisplay(i,~digitaltube_show[i]);
	i++;
	if(i==8) i=0;
	//==============================================================
	
	//========================NE555===========================
	ne555_cnt++;
	if(ne555_cnt==1000)//1s到了
	{
		frequency=(TH0<<8)|TL0;
		TH0=TL0=0;
		ne555_cnt=0;
	}
	//============================================
}
