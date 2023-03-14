#include "su_led.h"
#include "su_key.h"
#include "su_common_typedef.h"
#include "delay.h"
#include "timer.h"
#include "su_ds1302.h"
#include "su_S12.h"
#include "stdio.h"
#include "su_usart.h"
#include "su_pcf8591.h"
#include "su_eeprom.h"


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
	uint8_t adc=0,channel=0;
	uint8_t test=0;
	ENABLE_LED_LATCH;
	UartInit();
	while(Pcf8591_Adc_Init(0x04)!=1)
	{
		printf("adc init eeror\r\n");
		Delay100ms();
	}
//	Write_Eeprom(0x00,5);
	while (1)
    {
		//=================ADC�ɼ�==========================
		adc=AdcRead();
		if(adc==128) 	channel=-1;
		else			channel=(channel+1)%4;
//		printf("channel is %bu,data is %bu\r\n",channel,adc);
		//=================����洢=========================
		test=Read_Eeprom(0x00);
		printf("%bu\r\n",test);
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

