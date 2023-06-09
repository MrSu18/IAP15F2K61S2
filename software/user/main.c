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
#include "su_ds18b20.h"
#include "su_eeprom.h"

uint8_t adc_flag=0,temperature_flag=0,ultrasonic_flag=0;

void main(void)
{	
	uint8_t adc,eeprom;
	uint16_t distance;
	//�رշ������ͼ̵���
	P04=0;P06=0;Select_Latch(5);
	//��ʼ��ledȫΪ��
	memset(&led_object,0xff,1);P0=*(uint8_t*)&led_object;Select_Latch(4);
	//NE555��ʼ��
	Ne555TimInit();//NE555��ʱ����ʼ��
	// Ne555CountInit();//NE555��������ʼ��
	//���ڳ�ʼ��
	UartInit();
	eeprom=Read_Eeprom(0);
	//adcģ���ʼ��
	Pcf8591_Adc_Init(0x43);//����DA���ADC�ɼ�ͨ��3
	//�������ж�EA
	EA=1;
	while (1)
	{
		if(adc_flag==1)
		{
			adc=PCF8591_ADC(0x43);
			Write_Eeprom(0,adc);
			adc_flag=0;
		}
		if (temperature_flag==1)
		{
			Read_DS18B20_temp();
			temperature_flag=0;
		}
		if (ultrasonic_flag==1)
		{
			distance=UltrasonicMeasure();
			ultrasonic_flag=0;
		}
		digitaltube_show[0]=t_display[eeprom/100%10];
		digitaltube_show[1]=t_display[eeprom/10%10];
		digitaltube_show[2]=t_display[eeprom%10];
		digitaltube_show[5]=t_display[adc/100%10];
		digitaltube_show[6]=t_display[adc/10%10];
		digitaltube_show[7]=t_display[adc%10];
	}
	
}



