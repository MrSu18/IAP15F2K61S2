#include "timer.h"
#include <stc15f2k60s2.h>
#include "su_led.h"
#include "su_common_typedef.h"

void Timer0Init(void)		//1����@11.0592MHz
{
	AUXR |= 0x80;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0xCD;				//���ö�ʱ��ʼֵ
	TH0 = 0xD4;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	
	/*�����Ĵ�����ISP�������ɵĶ�ʱ����ģʽ��ֵ���ô��룬���Ҫ�����ж���Ҫ�Լ�д�������䣬�����ж�*/
	
	EA=1;//�������ж�
	ET0=1;//������ʱ��0�ж�
}

void Time0_Sever() interrupt 1	//��ʱ��0�жϻص�����
{
	static uint8_t num=0;
	if(num<100)
	{
		num++;
	}
	else
	{
		LED1=~LED1;//�жϷ�����������Ƕ�ʱ��û���Զ���װ�صĻ��ǵ���������װ��ʼ�������ã�TH0��TL0��ֵ
		num=0;
	}
}
