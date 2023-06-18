#include "timer.h"
#include <stc15f2k60s2.h>
#include "su_led.h"
#include "su_common_typedef.h"
#include "su_digital_tube.h"
#include "su_ne555.h"
#include "su_led.h"
#include "su_latch.h"
#include "su_ds18b20.h"

extern uint8_t key_cnt,light_flag,led_warm_flag,temp_param;//��ʱ����������
extern uint16_t adc_cnt,display_page_cnt,data_cnt;
extern LED_t led;


void Time1_Sever()	interrupt 3//��ʱ��1�жϻص�����
{
	static uint16_t ne555_cnt=0;
	static uint8_t led_cnt=0;
	//===========��̬ˢ�������һ���жϾ�ˢ��һλ==================
	static uint8_t i=0;
	DigitalTubeDisplay(i,~digitaltube_show[i]);
	i++;
	if(i==8) i=0;
	//==============================================================
	key_cnt++;adc_cnt++;data_cnt++;
	if(light_flag==1)
	{
		display_page_cnt++;
	}
	//========================NE555===========================
	ne555_cnt++;
	if(ne555_cnt==1000)//1s����
	{
		TR0=0;
		if(TF0==1)//�����
		{
			led.led5=0;
			Select_Latch(4);
			P0=*(uint8_t*)&led;
			frequency=0;//��Ч����
			TF0=0;
		}
		else
		{
			frequency=(TH0<<8)+TL0;
			if(frequency<200 || frequency>2000)
			{
				led.led5=0;
				Select_Latch(4);
				P0=*(uint8_t*)&led;
				frequency=0;
			}
			else
			{
				led.led5=1;
				Select_Latch(4);
				P0=*(uint8_t*)&led;
			}
		}
		TH0=TL0=0;
		ne555_cnt=0;
		TR0=1;
	}
	//============================================
	if(led_warm_flag==1)
	{
		led_cnt++;
		if(led_cnt>=100)
		{
			led.led4=~led.led4;
			Select_Latch(4);
			P0=*(uint8_t*)&led;
		}
		if(temperature<temp_param*10)
		{
			led.led4=1;
			Select_Latch(4);
			P0=*(uint8_t*)&led;
			led_warm_flag=0;
		}
	}
}
