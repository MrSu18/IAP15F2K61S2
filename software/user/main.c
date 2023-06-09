#include <stc15f2k60s2.h>
#include <string.h>
#include "su_common_typedef.h"
#include "su_latch.h"//������
#include "su_led.h"//LED�Ľṹ��
#include "su_ne555.h"
#include "su_usart.h"
#include "su_ultrasonic.h"
#include "delay.h"
#include "su_digital_tube.h"
#include "su_S12.h"
#include "su_pcf8591.h"

uint8_t adc=0;

void main(void)
{	
	uint8_t adc;
	//�رշ������ͼ̵���
	P04=0;P06=0;Select_Latch(5);
	//��ʼ��ledȫΪ��
	memset(&led_object,0xff,1);P0=*(uint8_t*)&led_object;Select_Latch(4);
	//NE555��ʼ��
	Ne555TimInit();//NE555��ʱ����ʼ��
	Ne555CountInit();//NE555��������ʼ��
	//���ڳ�ʼ��
	UartInit();
	//adcģ���ʼ��
	Pcf8591_Adc_Init(0x43);//����DA���ADC�ɼ�ͨ��3
	//�������ж�EA
	EA=1;
	while (1)
	{
		EA=0;
		adc=AdcRead();
		EA=1;
		digitaltube_show[0]=t_display[adc/100%10];
		digitaltube_show[1]=t_display[adc/10%10];
		digitaltube_show[2]=t_display[adc%10];
		Delay50ms();
	}
	
}



