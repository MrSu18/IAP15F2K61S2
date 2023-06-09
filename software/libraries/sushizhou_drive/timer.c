#include "timer.h"
#include <stc15f2k60s2.h>
#include "su_led.h"
#include "su_common_typedef.h"
#include "su_key.h"
#include "su_ds18b20.h"//温度传感器
#include "su_ds1302.h"//实时时钟模块
#include "su_digital_tube.h"
#include "su_ne555.h"
#include "su_pwm.h"
#include "su_pcf8591.h"

extern uint8_t adc_flag;

void Time0_Sever() interrupt 1	//定时器0中断回调函数
{
	;
}

void Time1_Sever()	interrupt 3//定时器1中断回调函数
{
	;
}

void Time2_Sever()	interrupt 12//定时器2中断回调函数
{
	static uint16_t ne555_cnt=0,digitaltube_cnt=0,read_adc_cnt=0;
	//==============动态刷新数码管一次中断就刷新一位==================
	static uint8_t i=0;
	digitaltube_cnt++;
	if(digitaltube_cnt==10)//1ms
	{
		DigitalTubeDisplay(i,~digitaltube_show[i]);
		i++;
		if(i==8) i=0;
		digitaltube_cnt=0;
	}
	//=================================================================
	
	//============================ADC==================================
	read_adc_cnt++;
	if (read_adc_cnt==1000)//200ms
	{
		adc_flag=1;
		read_adc_cnt=0;
	}
	
	//=================================================================

	//=============================NE555===============================
	ne555_cnt++;
	if(ne555_cnt==5000)//1s到了
	{
		TR0=0;//停止计数
		if(TF0==1) 
		{
			frequency=0;
			TF0=0;
		}
		else
		{
			frequency=(TH0<<8)|TL0;
		}
		TH0=TL0=0;
		ne555_cnt=0;
		TR0=1;//开始新一轮计数
	}
	//==================================================================
	
	//==============================PWM=================================
	PWMSetDuty(1);
	//==================================================================
}
