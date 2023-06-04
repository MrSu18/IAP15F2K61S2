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

#include "iic.h"
#define PCF8591_W_ADD	0X90	//PCF8591��д��ַ
#define PCF8591_R_ADD	0X91	//PCF8591�Ķ���ַ

void main(void)
{	
	uint8_t adc;
	//�رշ������ͼ̵���
	Select_Latch(5);P04=0;P06=0;
	//��ʼ��ledȫΪ��
	memset(&led_object,0xff,1);Select_Latch(4);P0=*(uint8_t*)&led_object;
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
		adc=PCF8591_ADC(0x43);
		PCF8591_Dac(4.0/5*255);
		printf("%bu\r\n",adc);
		Delay200ms();
	}
	
}



