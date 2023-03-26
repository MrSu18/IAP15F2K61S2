#include "su_S12.h"
#include "su_ds18b20.h"//�¶ȴ�����
#include "su_ds1302.h"//ʵʱʱ��ģ��
#include "su_digital_tube.h"//�������ʾ
#include "delay.h"
#include "timer.h"
#include "reg52.h"
#include "su_key.h"
#include <stdio.h>

uint8_t key_value=0;//������ȡ����ֵ
int cnt1=0,cnt2=0,cnt3=0;//��ȡ�������ļ���������ȡ�����ļ��������������ʾ�ļ�����
uint8_t digitaltube_show[8]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07};//���ڴ���������ʾ�����������޸��������ʾ��ֵ

void DeviceInit(void)
{
    //ʱ��ģ���ʼ��
    TimeBuff[4]=23;TimeBuff[5]=25;
	DS1302_Write_Time();//дһ�α���ʱ��ģ���������Կ�ʼ����
	//�¶ȴ�������ʼ��
	//�����߶�ȡ������Ҫ��ʼ��
	Timer0Init();//������ʱ���ж�
	EA=1;//�������ж�
}

void DisplayTime(void)//ʱ����ʾ����
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

void DisplayTemperature(void)//�¶���ʾ����
{
	digitaltube_show[0]=t_display[25];//U
	digitaltube_show[1]=t_display[1];
	digitaltube_show[2]=t_display[16];//Ϩ��
	digitaltube_show[3]=t_display[16];
	digitaltube_show[4]=t_display[16];
	digitaltube_show[5]=t_display[temperature/100];
	digitaltube_show[6]=t_display[temperature/10%10+30];
	digitaltube_show[7]=t_display[temperature%10];
}

void DisplaySetParameter(void)//�������õ���ʾ����
{
	digitaltube_show[0]=t_display[25];//U
	digitaltube_show[1]=t_display[3];
	digitaltube_show[2]=t_display[16];//Ϩ��
	digitaltube_show[3]=t_display[16];
	digitaltube_show[4]=t_display[16];
	digitaltube_show[5]=t_display[16];
	digitaltube_show[6]=t_display[temperature/100];
	digitaltube_show[7]=t_display[temperature/10%10];
}


void S13Function()
{
	static uint8_t display_page=0;
	if(cnt1==900)//0.9S�ж�һ�δ�����
	{
		Read_DS18B20_temp();
		DS1302_Read_Time();
	}
	if(cnt2==100)//0.1s��һ�ΰ���
	{
		key_value=ReadKeyBoard();
		if(key_value!=0xff)
		{
			Delay10ms();//����
			key_value=ReadKeyBoard();
			if(key_value!=0xff)
			{
				switch(key_value)//��Ӧ������ֵ,��ҳ��������һ
				{
					case 12:display_page=(display_page+1)%3;break;
					default:break;
				}
//				printf("%bu\r\n",key_value);
				while(ReadKeyBoard()!=0xff);//�������
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