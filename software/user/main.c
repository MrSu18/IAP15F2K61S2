#include "su_S12.h"
#include "su_usart.h"
#include "delay.h"
#include "su_ds18b20.h"
#include "su_key.h"

#include "su_latch.h"
#include <stc15f2k60s2.h>

void main(void)
{	
	unsigned char temp=0,status=0;
	DeviceInit();//�豸��ʼ��
	UartInit();//���ڳ�ʼ�����ڵ���
	
	Select_Latch(5);
	
	while(1)
	{
		P06=0;//�̵�����
		P04=0;//��������
	}
}



