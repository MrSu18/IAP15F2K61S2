#include "su_S12.h"
#include "su_usart.h"
#include "delay.h"
#include "su_ds18b20.h"
#include "su_key.h"

void main(void)
{	
	unsigned char temp=0;
	DeviceInit();//�豸��ʼ��
	UartInit();//���ڳ�ʼ�����ڵ���
	
	while(1)
	{
		temp=ReadKeyBoard();
		if(temp!=0xff)
		{
			printf("%bu\r\n",temp);
			while(ReadKeyBoard()!=0xff);
		}
		Delay200ms();
	}
}



