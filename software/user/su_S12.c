#include "su_S12.h"
#include "su_ds18b20.h"//温度传感器
#include "su_ds1302.h"//实时时钟模块
#include "su_digital_tube.h"//数码管显示
#include "delay.h"
#include "timer.h"
#include "su_key.h"
#include <stdio.h>
#include "su_led.h"
#include "su_latch.h"
#include <string.h>

uint8_t key_now=0,key_down=0;//按键读取到的值
int cnt1=0,cnt2=0,cnt3=0;//读取传感器的计数器，读取按键的计数器，数码管显示的计数器
char temp_thr=23;//温度参数
LED_t led;
uint8_t jidianqi_flag=0;//0：关 1: 开

void DeviceInit(void)
{
	P06=0;//蜂鸣器关
	P04=0;//继电器关
	Select_Latch(5);
    //时钟模块初始化
    TimeBuff[4]=23;TimeBuff[5]=25;
	DS1302_Write_Time();//写一次避免时钟模块里面足以开始不对
	//温度传感器初始化
	//单总线读取，不需要初始化
	Timer0Init();//开启定时器中断
	memset(&led,0xff,sizeof(LED_t));//在初始化的时候把led的所有位置为1，因为memset是按照字节写的所以要0xff
	while(temperature>=800)//温度传感器最开始读值是83.5
	{
		Read_DS18B20_temp();
	}
	EA=1;//开启总中断,这句一定要放在最后避免温度值还没初始化结束，使得数码管显示错误
}

void DisplayTime(void)//时间显示界面
{
	//判断是时分显示还是分秒显示
	if(key_now==17)
	{
		digitaltube_show[3]=t_display[TimeBuff[5]/10];
		digitaltube_show[4]=t_display[TimeBuff[5]%10];
		digitaltube_show[6]=t_display[TimeBuff[6]/10];
		digitaltube_show[7]=t_display[TimeBuff[6]%10];
	}
	else
	{
		digitaltube_show[3]=t_display[TimeBuff[4]/10];
		digitaltube_show[4]=t_display[TimeBuff[4]%10];
		digitaltube_show[6]=t_display[TimeBuff[5]/10];
		digitaltube_show[7]=t_display[TimeBuff[5]%10];
	}
	//以下是固定显示的部分
	digitaltube_show[0]=t_display[25];
	digitaltube_show[1]=t_display[2];
	digitaltube_show[2]=t_display[16];
	digitaltube_show[5]=t_display[17];
}

void DisplayTemperature(void)//温度显示界面
{
	digitaltube_show[0]=t_display[25];//U
	digitaltube_show[1]=t_display[1];
	digitaltube_show[2]=t_display[16];//熄灭
	digitaltube_show[3]=t_display[16];
	digitaltube_show[4]=t_display[16];
	digitaltube_show[5]=t_display[temperature/100];
	digitaltube_show[6]=t_display[temperature/10%10+32];
	digitaltube_show[7]=t_display[temperature%10];
}

void DisplaySetParameter(void)//参数设置的显示界面
{
	if(key_down==17)	temp_thr++;
	else if(key_down==16)	temp_thr--;
	digitaltube_show[0]=t_display[25];//U
	digitaltube_show[1]=t_display[3];
	digitaltube_show[2]=t_display[16];//熄灭
	digitaltube_show[3]=t_display[16];
	digitaltube_show[4]=t_display[16];
	digitaltube_show[5]=t_display[16];
	digitaltube_show[6]=t_display[temp_thr/10];
	digitaltube_show[7]=t_display[temp_thr%10];
}


void S13Function()
{
	static uint8_t last_key_value=0;//用于三行代码消抖法
	static uint8_t display_page=0;
	static char mode=-1;//工作模式 -1: 温度控制 1：时间控制
	if(cnt1==900)//0.9S中读一次传感器
	{
		Read_DS18B20_temp();
		DS1302_Read_Time();
	}
	if(cnt2==10)//0.1s读一次按键
	{
		key_now=ReadKeyBoard();
		key_down=key_now&(last_key_value^key_now);
		last_key_value=key_now;
		switch(key_down)//响应按键的值
		{
			case 12:display_page=(display_page+1)%3;break;//S12按键按下翻页的索引加一
			case 13:
				led.led2=~led.led2;
				P0=*(uint8_t*)&led;
				Select_Latch(4);//使能LED锁存器
				jidianqi_flag=0;//切换模式了这个flag应该改回来
				mode=-mode;break;//S13按键按下切换工作模式
			default:break;
		}
	}
	//修改数码管
	switch(display_page)
	{
		case 0:DisplayTemperature();break;
		case 1:DisplayTime();break;
		case 2:DisplaySetParameter();break;
		default:break;
	}
	//修改继电器
	switch(mode)
	{
		case -1:
			if(temperature>(temp_thr*10) && jidianqi_flag==0)
			{
				P04=1;//继电器开
				P06=0;//蜂鸣器关
				Select_Latch(5);
				jidianqi_flag=1;
			}
			else if(temperature<=(temp_thr*10) && jidianqi_flag==1)
			{
				P04=0;//继电器关
				P06=0;//蜂鸣器关
				Select_Latch(5);
				jidianqi_flag=0;
			}
			break;
		case 1:
			break;
		default:break;
	}
}

void S13TimeServer(void)
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
	if(cnt2==10)//0.1s读一次按键
	{
		cnt2=0;
	}
	cnt1++;cnt2++;
}