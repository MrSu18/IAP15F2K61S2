#include "su_usart.h"
#include <stc15f2k60s2.h>
#include "stdio.h"
#include "su_common_typedef.h"

void UartInit(void)		//115200bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0xE8;			//���ö�ʱ��ʼֵ
	TH1 = 0xFF;			//���ö�ʱ��ʼֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ
    ////////////////////����ΪISP�������////////////////
    EA=1;       //���ж��ܿ���
	ES=1;       // �������ж�
}

//***************����һ���ֽ�******************************************
void SendByte(unsigned char dat)
{
	SBUF=dat;
	while(TI==0);
	TI=0;
}
//�����ض���
// int fputc(int ch, FILE *f)
// {
//     SendByte(ch);
//     return ch;
// }
char putchar(char c)
{
	//����ض��򵽴���
	SendByte(c);
	return c;  //���ظ������ĵ�����printf
}
