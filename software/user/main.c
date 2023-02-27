#include "su_led.h"
#include "su_key.h"
#include "su_common_typedef.h"
#include "delay.h"
#include "timer.h"
#include "su_ds1302.h"
#include "su_S12.h"
#include "stdio.h"
#include "su_usart.h"


unsigned char Rdat;

//***************�����жϷ����ӳ���******************************************
// void ServiceUart() interrupt 4
// {
// 	if(RI==1)//����������
// 	{
// 		Rdat=SBUF;//RdatΪ����λ�����յ�������
// 		RI=0;				
// 		SendByte(Rdat);//�ٽ��յ��������ٷ��͵���λ��
// 	}
// }


void main(void)
{
    ENABLE_LED_LATCH;
	UartInit();
	while (1)
    {
		printf("hello\r\n");
		Delay500ms();
    }
}

void Time0Isr() interrupt 1	//��ʱ��0�жϻص�����
{
	static uint8_t num=0;
	if(num<100)
	{
		num++;
	}
	else
	{
		LED1=~LED1;//�жϷ�����������Ƕ�ʱ��û���Զ���װ�صĻ��ǵ���������װ��ʼ�������ã�TH0��TL0��ֵ
		num=0;
	}
}

