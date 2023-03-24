#include "su_S12.h"
#include "su_usart.h"
#include "delay.h"
#include "su_ds18b20.h"

void main(void)
{
	float temperature=0;
	char temp=0;
	
	DeviceInit();//�豸��ʼ��
	UartInit();//���ڳ�ʼ�����ڵ���
	
	while(1)
	{
//		temp=rd_temperature();
		temperature=Read_DS18B20_temp();
		printf("%f\r\n",temperature);
		Delay500ms();
	}
}



