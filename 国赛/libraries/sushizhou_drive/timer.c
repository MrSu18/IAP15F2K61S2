#include "timer.h"
#include <stc15f2k60s2.h>
#include "su_led.h"
#include "su_key.h"
#include "su_ds18b20.h"//�¶ȴ�����
#include "su_digital_tube.h"
#include "main.h"
#include "su_ultrasonic.h"

uint8_t sensor_flag=0,key_flag=0,jilu_flag=0,dac_flag=0,shuchu_flag=0;

void Timer2Init(void)		//1����@12.000MHz
{
	AUXR &= 0xFB;		//��ʱ��ʱ��12Tģʽ
	T2L = 0x18;		//���ö�ʱ��ֵ
	T2H = 0xFC;		//���ö�ʱ��ֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ
	IE2 |=0x04;//����ʱ��2�ж�
}


void Time1_Sever()	interrupt 3//��ʱ��1�жϻص�����
{
	;
}

void Time2_Sever()	interrupt 12//��ʱ��2�жϻص�����
{
	static uint16_t sensor_cnt=0,key_cnt=0,led_cnt=0,dac_cnt=0,key_10_cnt=0;
	//==============��̬ˢ�������һ���жϾ�ˢ��һλ==================
	static uint8_t i=0;
	DigitalTubeDisplay(i,~digitaltube_show[i]);
	i++;
	if(i==8) i=0;
	//===========================������==================================
	sensor_cnt++;
	if(sensor_cnt==400)
	{
		sensor_flag=1;
		sensor_cnt=0;
	}
	//=====================����========================
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
	//=======================�����Ӧ=========================
	if(shuchu_flag==1 && jilu_flag==0)
	{
		dac_cnt++;
		if(dac_cnt==100)
		{
			dac_flag=1;
			dac_cnt=0;
		}
	}
	
	if(jilu_flag==1 && key_now!=10)//�������°���S8������¼
	{
		key_10_cnt++;
		if(key_10_cnt%100==0)//ÿ0.1s�ͼ�¼һ��
		{
			distance_lianxu[distane_lianxu_cnt]=distance;
			distane_lianxu_cnt++;
		}
		if(key_10_cnt==6000)//6S����
		{
			jilu_flag=0;
		}
	}
	else if(key_now==10)//S8��S9һ����
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



