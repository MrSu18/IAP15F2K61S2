#include "timer.h"
#include <stc15f2k60s2.h>
#include "su_led.h"
#include "su_common_typedef.h"
#include "su_key.h"
#include "su_ds18b20.h"//�¶ȴ�����
#include "su_ds1302.h"//ʵʱʱ��ģ��
#include "su_digital_tube.h"
#include "su_ne555.h"
#include "su_pwm.h"
#include "su_pcf8591.h"

extern uint8_t adc_flag;

void Time0_Sever() interrupt 1	//��ʱ��0�жϻص�����
{
	;
}

void Time1_Sever()	interrupt 3//��ʱ��1�жϻص�����
{
	;
}

void Time2_Sever()	interrupt 12//��ʱ��2�жϻص�����
{
	static uint16_t ne555_cnt=0,digitaltube_cnt=0,read_adc_cnt=0;
	//==============��̬ˢ�������һ���жϾ�ˢ��һλ==================
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
	if(ne555_cnt==5000)//1s����
	{
		TR0=0;//ֹͣ����
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
		TR0=1;//��ʼ��һ�ּ���
	}
	//==================================================================
	
	//==============================PWM=================================
	PWMSetDuty(1);
	//==================================================================
}
