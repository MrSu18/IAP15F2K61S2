#include <stc15f2k60s2.h>
#include <string.h>
#include "su_latch.h"//������
#include "su_led.h"//LED�Ľṹ��

void main(void)
{	
	//�رշ������ͼ̵���
	Select_Latch(5);P04=0;P06=0;
	//��ʼ��ledȫΪ��
	memset(&led_object,0xff,1);Select_Latch(4);P0=*(uint8_t*)&led_object;
	while (1)
	{
		;
	}
	
}



