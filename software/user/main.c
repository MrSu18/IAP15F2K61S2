#include "su_S12.h"
#include "su_usart.h"
#include "delay.h"

void main(void)
{
	DeviceInit();//�豸��ʼ��
	UartInit();//���ڳ�ʼ�����ڵ���
	while(1)
	{
		printf("usart test\r\n");
		Delay500ms();
	}
}



