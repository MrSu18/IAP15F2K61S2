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
	// ne555_cnt++;
	// if(ne555_cnt==1000)//1s����
	// {
	// 	TR0=0;//ֹͣ����
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
	// 	TR0=1;//��ʼ��һ�ּ���
	// }
	//============================================
}
