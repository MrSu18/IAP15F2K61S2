#include <stc15f2k60s2.h>
#include <string.h>
#include "su_latch.h"//������
#include "su_led.h"//LED�Ľṹ��
#include "su_ne555.h"

void main(void)
{	
	//�رշ������ͼ̵���
	Select_Latch(5);P04=0;P06=0;
	//��ʼ��ledȫΪ��
	memset(&led_object,0xff,1);Select_Latch(4);P0=*(uint8_t*)&led_object;
	//NE555��ʼ��
	Ne555TimInit();//NE555��ʱ����ʼ��
	Ne555CountInit();//NE555��������ʼ��
	//�������ж�EA
	EA=1;
	while (1)
	{
		;
	}
	
}



