#include "su_S12.h"
#include "su_usart.h"
#include "delay.h"
#include "su_ds18b20.h"
#include "su_key.h"
#include "su_pcf8591.h"
#include "su_latch.h"
#include <stc15f2k60s2.h>
#include "su_digital_tube.h"

void main(void)
{	
	unsigned char temp=0,status=0;
	
//	DeviceInit();//�豸��ʼ��
	UartInit();//���ڳ�ʼ�����ڵ���
	PCF8591_Dac(0xff);
	while(1)
	{
//		S13Function();
	}
}



