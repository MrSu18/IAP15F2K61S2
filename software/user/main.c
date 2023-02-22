#include "su_led.h"
#include "su_key.h"
#include "su_common_typedef.h"
#include "delay.h"
#include "timer.h"
#include "su_digital_tube.h"

void main(void)
{
    ENABLE_LED_LATCH;
	while (1)
    {
		
		//*******��һλ��ʾ1*************
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;//Y6C��Ч��P0������ʾ��һλ
		P0=0x01;          //P0=0000 0001��ѡͨ��һλ�������һλ��
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;//Y7C��Ч��P0������ʾ��һ������
		P0=~t_display[1];	//��P0��������1�Ķ��룬���������ʾ1	
		Delay2ms();
		//*******�ڶ�λ��ʾ2*************	
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;	//Y6C��Ч
		P0=0x02;          //P0=0000 0010��ѡͨ�ڶ�λ
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;	//Y7C��Ч
		P0=~t_display[2];	//��P0��������2�Ķ��룬���������ʾ2		
		Delay2ms();
		//*******����λ��ʾ3*************		
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;	//Y6C��Ч
		P0=0x04;					//P0=0000 0100��ѡͨ����λ
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;	//Y7C��Ч
		P0=~t_display[3];	//��P0��������3�Ķ��룬���������ʾ3
		Delay2ms();
		//*******����λ��ʾ4*************		
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;
		P0=0x08;					//P0=0000 1000��ѡͨ����λ
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;
		P0=~t_display[4];	//�������ʾ4
		Delay2ms();
		//*******����λ��ʾ*************		
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;
		P0=0x10;					//P0=0001 0000��ѡͨ����λ
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;
		P0=~t_display[5];	//�������ʾ5
		Delay2ms();
		//*******����λ��ʾ6*************		
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;
		P0=0x20;					//P0=0010 0000��ѡͨ����λ
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;
		P0=~t_display[6];	//�������ʾ6	
		Delay2ms();
		//*******����λ��ʾ7*************		
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;
		P0=0x40;					//P0=0100 0000��ѡͨ����λ
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;
		P0=~t_display[7];	//�������ʾ7	
		Delay2ms();
		//*******�ڰ�λ��ʾ8*************		
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;
		P0=0x80;					//P0=1000 0000��ѡͨ�ڰ�λ
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;
		P0=~t_display[8];	//�������ʾ8	
		Delay2ms();	
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

