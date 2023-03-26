#include "su_S12.h"
#include "su_ds18b20.h"//温度传感器
#include "su_ds1302.h"//实时时钟模块
#include "su_digital_tube.h"//数码管显示
#include "delay.h"
#include "timer.h"
#include "reg52.h"
#include "su_key.h"
#include <stdio.h>

uint8_t key_value=0;//按键读取到的值
int cnt1=0,cnt2=0,cnt3=0;//读取传感器的计数器，读取按键的计数器，数码管显示的计数器
uint8_t digitaltube_show[8]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07};//用于存放数码管显示的数字用于修改数码管显示的值

void DeviceInit(void)
{
    //时钟模块初始化
    TimeBuff[4]=23;TimeBuff[5]=25;
	DS1302_Write_Time();//写一次避免时钟模块里面足以开始不对
	//温度传感器初始化
	//单总线读取，不需要初始化
	Timer0Init();//开启定时器中断
	EA=1;//开启总中断
}

void DisplayTime(void)//时间显示界面
{
	digitaltube_show[0]=t_display[25];
	digitaltube_show[1]=t_display[2];
	digitaltube_show[2]=t_display[16];
	digitaltube_show[3]=t_display[TimeBuff[4]/10];
	digitaltube_show[4]=t_display[TimeBuff[4]%10];
	digitaltube_show[5]=t_display[17];
	digitaltube_show[6]=t_display[TimeBuff[5]/10];
	digitaltube_show[7]=t_display[TimeBuff[5]%10];
}

void DisplayTemperature(void)//温度显示界面
{
	digitaltube_show[0]=t_display[25];//U
	digitaltube_show[1]=t_display[1];
	digitaltube_show[2]=t_display[16];//熄灭
	digitaltube_show[3]=t_display[16];
	digitaltube_show[4]=t_display[16];
	digitaltube_show[5]=t_display[temperature/100];
	digitaltube_show[6]=t_display[temperature/10%10+30];
	digitaltube_show[7]=t_display[temperature%10];
}

void DisplaySetParameter(void)//参数设置的显示界面
{
	digitaltube_show[0]=t_display[25];//U
	digitaltube_show[1]=t_display[3];
	digitaltube_show[2]=t_display[16];//熄灭
	digitaltube_show[3]=t_display[16];
	digitaltube_show[4]=t_display[16];
	digitaltube_show[5]=t_display[16];
	digitaltube_show[6]=t_display[temperature/100];
	digitaltube_show[7]=t_display[temperature/10%10];
}


void S13Function()
{
	static uint8_t display_page=0;
	if(cnt1==900)//0.9S中读一次传感器
	{
		Read_DS18B20_temp();
		DS1302_Read_Time();
	}
	if(cnt2==100)//0.1s读一次按键
	{
		key_value=ReadKeyBoard();
		if(key_value!=0xff)
		{
			Delay10ms();//消抖
			key_value=ReadKeyBoard();
			if(key_value!=0xff)
			{
				switch(key_value)//响应按键的值,翻页的索引加一
				{
					case 12:display_page=(display_page+1)%3;break;
					default:break;
				}
//				printf("%bu\r\n",key_value);
				while(ReadKeyBoard()!=0xff);//检测松手
			}
			
		}
	}
	
//	printf("%bu\r\n",display_page);
	switch(display_page)
	{
		case 0:DisplayTemperature();break;
		case 1:DisplayTime();break;
		case 2:DisplaySetParameter();break;
		default:break;
	}
}