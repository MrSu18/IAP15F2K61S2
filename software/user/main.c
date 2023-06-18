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
#include "su_key.h"

uint8_t adc_flag=0,temperature_flag=0,ultrasonic_flag=0;

void main(void)
{	
	uint8_t adc,eeprom,key_now,key_old,key_down;
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
		key_now=ReadKeyBoard();
		key_down=key_now&(key_now^key_old);
		key_old=key_now;
		switch (key_down)
		{
		case 4:
			printf("void UltrasonicStar(void)//����������ģ��\r\n");
			printf("{ \r\n");
			printf("	unsigned char ucNum=10;\r\n");
			printf("	TX=0;\r\n");
			printf("	TL0=0XF4;TH0=0XFF;\r\n");
			printf("	TR0=1;\r\n");
			printf("	while (ucNum--)\r\n");
			printf("	{\r\n");
			printf("		while (!TF0);\r\n");
			printf("		TX^=1;\r\n");
			printf("		TF0=0;\r\n");
			printf("	}\r\n");
			printf("	TR0=0;\r\n");
			printf("	TL0=TH0=0;\r\n");
			printf("} \r\n");
			break;
		case 5:
			printf("eepromд���������ӳٿ��Ը�Ϊ5ms\r\n");
			printf("ds18b20�е�Delay_OneWire(200);����ȥ��\r\n");
			printf("����������ֵ��cm��λ\r\n");
			printf("�������Ĵ����źŰ�S4��ӡ������д\r\n");
			break;
		case 8:
			printf("uint8_t StrCheck(uint8_t* str , uint8_t* cnt, uint8_t ch)//����ַ����Ƿ�ƥ�䣬״̬�����\r\n");
			printf("{\r\n");
			printf("	if(str[*cnt]==ch)\r\n");
			printf("	{\r\n");
			printf("		(*cnt)++;\r\n");
			printf("		if(*cnt==4)\r\n");
			printf("		{\r\n");
			printf("			(*cnt)=0;\r\n");
			printf("			return 1;\r\n");
			printf("		}\r\n");
			printf("	}\r\n");
			printf("	else\r\n");
			printf("	{\r\n");
			printf("		(*cnt)=0;\r\n");
			printf("	}\r\n");
			printf("	return 0;\r\n");
			printf("}\r\n");
			break;
		default:
			break;
		}
	}
	
}



