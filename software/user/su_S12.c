#include "su_S12.h"
#include "su_ds18b20.h"//�¶ȴ�����
#include "su_ds1302.h"//ʵʱʱ��ģ��
#include "su_digital_tube.h"//�������ʾ
#include "delay.h"
#include "timer.h"
#include "su_key.h"
#include <stdio.h>
#include "su_led.h"
#include "su_latch.h"
#include <string.h>

uint8_t key_now=0,key_down=0;//������ȡ����ֵ
int cnt1=0,cnt2=0,cnt3=0;//��ȡ�������ļ���������ȡ�����ļ��������������ʾ�ļ�����
uint8_t digitaltube_show[8]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07};//���ڴ���������ʾ�����������޸��������ʾ��ֵ
char temp_thr=23;//�¶Ȳ���
LED_t led;

void DeviceInit(void)
{
    //ʱ��ģ���ʼ��
    TimeBuff[4]=23;TimeBuff[5]=25;
	DS1302_Write_Time();//дһ�α���ʱ��ģ���������Կ�ʼ����
	//�¶ȴ�������ʼ��
	//�����߶�ȡ������Ҫ��ʼ��
	Timer0Init();//������ʱ���ж�
	memset(&led,0xff,sizeof(LED_t));//�ڳ�ʼ����ʱ���led������λ��Ϊ1����Ϊmemset�ǰ����ֽ�д������Ҫ0xff
	while(temperature>=800)//�¶ȴ������ʼ��ֵ��83.5
	{
		Read_DS18B20_temp();
	}
	EA=1;//�������ж�,���һ��Ҫ�����������¶�ֵ��û��ʼ��������ʹ���������ʾ����
}

void DisplayTime(void)//ʱ����ʾ����
{
	//�ж���ʱ����ʾ���Ƿ�����ʾ
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
	//�����ǹ̶���ʾ�Ĳ���
	digitaltube_show[0]=t_display[25];
	digitaltube_show[1]=t_display[2];
	digitaltube_show[2]=t_display[16];
	digitaltube_show[5]=t_display[17];
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
	if(key_down==17)	temp_thr++;
	else if(key_down==16)	temp_thr--;
	digitaltube_show[0]=t_display[25];//U
	digitaltube_show[1]=t_display[3];
	digitaltube_show[2]=t_display[16];//Ϩ��
	digitaltube_show[3]=t_display[16];
	digitaltube_show[4]=t_display[16];
	digitaltube_show[5]=t_display[16];
	digitaltube_show[6]=t_display[temp_thr/10];
	digitaltube_show[7]=t_display[temp_thr%10];
}


void S13Function()
{
	static uint8_t last_key_value=0;//�������д���������
	static uint8_t display_page=0;
	static uint8_t mode=1;//����ģʽ -1: �¶ȿ��� 1��ʱ�����
	if(cnt1==900)//0.9S�ж�һ�δ�����
	{
		Read_DS18B20_temp();
		DS1302_Read_Time();
	}
	if(cnt2==10)//0.1s��һ�ΰ���
	{
		key_now=ReadKeyBoard();
		key_down=key_now&(last_key_value^key_now);
		last_key_value=key_now;
		switch(key_down)//��Ӧ������ֵ
		{
			case 12:display_page=(display_page+1)%3;break;//S12�������·�ҳ��������һ
			case 13:
				led.led2=~led.led2;
				Select_Latch(4);//ʹ��LED������
				P0=*(uint8_t*)&led;
				mode=-mode;break;//S13���������л�����ģʽ
			default:break;
		}
//		printf("%bu\r\n",key_value);
	}
	
//	printf("%bu\r\n",display_page);
	switch(display_page)//�˵���������ʾ��ҳ������ȥ�޸�����ܵ������޸���ʾ
	{
		case 0:DisplayTemperature();break;
		case 1:DisplayTime();break;
		case 2:DisplaySetParameter();break;
		default:break;
	}
	
	switch(mode)
	{
		case -1:
			break;
		case 1:
			break;
		default:break;
	}
}