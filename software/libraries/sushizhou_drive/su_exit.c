#include "su_exit.h"
#include <stc15f2k60s2.h>
#include "delay.h"
#include "su_led.h"

void EXTI_Init(void)
{
    IT0=1;//�½��ش���
	EX0=1;//�ⲿ�ж�0�ж�����    enable external 0

    IT1=1;//�½��ش���
    EX1=1;//ʹ���ⲿ�ж�1

	EA=1;//���ж�����
}


//�ⲿ�ж�0�жϷ�����
void EXTI0_Sever(void) interrupt 0
{
	P2 = ((P2&0x1f)|0x80);
    LED1 = ~LED1;    
	P2 = P2&0x1f;
}
                        
//�ⲿ�ж�1�жϷ�����
void EXTI1_Sever(void) interrupt 2
{
	P2 = ((P2&0x1f)|0x80);
    LED2 = ~LED2;    
	P2 = P2&0x1f;
}
