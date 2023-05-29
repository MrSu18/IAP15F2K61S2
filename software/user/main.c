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

void Timer0Init(void)		//100΢��@12.000MHz
{
	AUXR &= 0x7F;			//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0x9C;				//���ö�ʱ��ʼֵ
	TH0 = 0xFF;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
}


void main(void)
{	
	//�رշ������ͼ̵���
	Select_Latch(5);P04=0;P06=0;
	//��ʼ��ledȫΪ��
	memset(&led_object,0xff,1);Select_Latch(4);P0=*(uint8_t*)&led_object;
	//NE555��ʼ��
	Ne555TimInit();//NE555��ʱ����ʼ��
//	Ne555CountInit();//NE555��������ʼ��
	//���ڳ�ʼ��
//	UartInit();
	//�������ж�EA
	EA=1;
	Timer0Init();
	while (1)
	{
		uint8_t distance=UltrasonicMeasure();
//		printf("%bu\r\n",distance);
		digitaltube_show[2]=t_display[distance%10];
		digitaltube_show[1]=t_display[distance/10%10];
		digitaltube_show[0]=t_display[distance/100%10];
		Delay100ms();
	}
	
}



