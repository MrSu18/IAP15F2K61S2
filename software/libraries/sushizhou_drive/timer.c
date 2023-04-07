#include "timer.h"
#include <stc15f2k60s2.h>
#include "su_led.h"
#include "su_common_typedef.h"
#include "su_S12.h"
#include "su_key.h"
#include "su_ds18b20.h"//�¶ȴ�����
#include "su_ds1302.h"//ʵʱʱ��ģ��
#include "su_digital_tube.h"
#include "su_ne555.h"

void Timer0Init(void)		//1����@12.000MHz
{
	AUXR |= 0x80;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0x20;				//���ö�ʱ��ʼֵ
	TH0 = 0xD1;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	
	/*�����Ĵ�����ISP�������ɵĶ�ʱ����ģʽ��ֵ���ô��룬���Ҫ�����ж���Ҫ�Լ�д�������䣬�����ж�*/
	
	ET0=1;//������ʱ��0�ж�
}

void Time0_Sever() interrupt 1	//��ʱ��0�жϻص�����
{
//	S13TimeServer();
}

void Time1_Sever()	interrupt 3//��ʱ��1�жϻص�����
{
	static uint16_t ne555_cnt=0;
	//===========��̬ˢ�������һ���жϾ�ˢ��һλ==================
	static uint8_t i=0;
	DigitalTubeDisplay(i,~digitaltube_show[i]);
	i++;
	if(i==8) i=0;
	//==============================================================
	
	//========================NE555===========================
	ne555_cnt++;
	if(ne555_cnt==1000)//1s����
	{
		frequency=(TH0<<8)|TL0;
		TH0=TL0=0;
		ne555_cnt=0;
	}
	//============================================
}
