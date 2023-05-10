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
	// ne555_cnt++;
	// if(ne555_cnt==1000)//1s到了
	// {
	// 	TR0=0;//停止计数
	// 	if(TF0==1) 
	// 	{
	// 		frequency=0;
	// 		TF0=0;
	// 	}
	// 	else
	// 	{
	// 		frequency=(TH0<<8)|TL0;
	// 	}
	// 	TH0=TL0=0;
	// 	ne555_cnt=0;
	// 	TR0=1;//开始新一轮计数
	// }
	//============================================
}
