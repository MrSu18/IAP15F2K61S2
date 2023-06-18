#include "timer.h"
#include <stc15f2k60s2.h>
#include "su_led.h"
#include "su_key.h"
#include "su_ds18b20.h"//温度传感器
#include "su_digital_tube.h"
#include "main.h"
#include "su_ultrasonic.h"

uint8_t sensor_flag=0,key_flag=0,jilu_flag=0,dac_flag=0,shuchu_flag=0;

void Timer2Init(void)		//1毫秒@12.000MHz
{
	AUXR &= 0xFB;		//定时器时钟12T模式
	T2L = 0x18;		//设置定时初值
	T2H = 0xFC;		//设置定时初值
	AUXR |= 0x10;		//定时器2开始计时
	IE2 |=0x04;//允许定时器2中断
}


void Time1_Sever()	interrupt 3//定时器1中断回调函数
{
	;
}

void Time2_Sever()	interrupt 12//定时器2中断回调函数
{
	static uint16_t sensor_cnt=0,key_cnt=0,led_cnt=0,dac_cnt=0,key_10_cnt=0;
	//==============动态刷新数码管一次中断就刷新一位==================
	static uint8_t i=0;
	DigitalTubeDisplay(i,~digitaltube_show[i]);
	i++;
	if(i==8) i=0;
	//===========================传感器==================================
	sensor_cnt++;
	if(sensor_cnt==400)
	{
		sensor_flag=1;
		sensor_cnt=0;
	}
	//=====================按键========================
	key_cnt++;
	if(key_cnt==50)
	{
		LEDResponse(led_object);
		key_flag=1;
		key_cnt=0;
	}
	if(gongchang_led_flag==1)
	{
		led_cnt++;
		if(led_cnt==100)
		{
			led_object.led1=!led_object.led1;
			led_cnt=0;
		}
		if(ui_page!=2)
			gongchang_led_flag=0;
	}
	//=======================输出响应=========================
	if(shuchu_flag==1 && jilu_flag==0)
	{
		dac_cnt++;
		if(dac_cnt==100)
		{
			dac_flag=1;
			dac_cnt=0;
		}
	}
	
	if(jilu_flag==1 && key_now!=10)//测距界面下按下S8开启记录
	{
		key_10_cnt++;
		if(key_10_cnt%100==0)//每0.1s就记录一次
		{
			distance_lianxu[distane_lianxu_cnt]=distance;
			distane_lianxu_cnt++;
		}
		if(key_10_cnt==6000)//6S到了
		{
			jilu_flag=0;
		}
	}
	else if(key_now==10)//S8和S9一起按下
	{
		key_10_cnt++;
		if(key_10_cnt==2000)//2S
		{
			distance_danwei=0;distance_canshu=40;temp_canshu=30;
			ui_page=0;u_speed=340;dac_xiaxian=10;
			key_10_cnt=0;
		}
	}
	else key_10_cnt=0;
}



