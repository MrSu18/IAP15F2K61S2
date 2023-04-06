#include "su_ultrasonic.h"

sbit TX = P1^0; // ��������
sbit RX = P1^1; // ��������

void Timer0Init_ultrasonic(void) // 12us@12.000MHz 
{ 
 AUXR &= 0x7F; // ��ʱ��ʱ�� 12T ģʽ
 TMOD &= 0xF0; // ���ö�ʱ��ģʽ
 TL0 = 0xF4; // ���ö�ʱ��ֵ
 TH0 = 0xFF; // ���ö�ʱ��ֵ
 TF0 = 0; // ��� TF0 ��־
 TR0 = 0; // ��ʱ�� 0 ֹͣ
} 

unsigned char Wave_Recv(void) 
{ 
	unsigned char ucDist, ucNum = 10; 
	TX = 0; 
	TL0 = 0xF4; // ���ö�ʱ��ֵ
	TH0 = 0xFF; // ���ö�ʱ��ֵ
	TR0 = 1; // ��ʱ�� 0 ��ʱ
	// TX ���ŷ��� 40kHz �����ź���������������̽ͷ
	while(ucNum--) 
	{ 
		while(!TF0); 
		TX ^= 1; 
		TF0 = 0; 
	} 
	TR0 = 0; 
	TL0 = 0; // ���ö�ʱ��ֵ
	TH0 = 0; // ���ö�ʱ��ֵ
	TR0 = 1; 
	while(RX && !TF0); // �ȴ��յ�����
	TR0 = 0; 
	if(TF0) // �������
	{ 
		TF0 = 0; 
		ucDist = 255; 
	} 
	else // �������
		ucDist = ((TH0<<8)+TL0)*0.017; 
	return ucDist; 
}
