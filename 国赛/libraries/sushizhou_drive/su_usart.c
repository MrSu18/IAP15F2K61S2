#include "su_usart.h"
#include <stc15f2k60s2.h>

uint8_t usart_result=0;//���ڷ������ڽ��ܵ���ָ����ʲô

void UartInit(void)		//4800bps@12.000MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0x8F;			//�趨��ʱ��ֵ
	TH1 = 0xFD;			//�趨��ʱ��ֵ
	ET1 = 0;			//��ֹ��ʱ��1�ж�
	TR1 = 1;			//������ʱ��1
    ////////////////////����ΪISP�������////////////////
//	ES=1;       // �������ж�
}


//***************����һ���ֽ�******************************************
void SendByte(unsigned char dat)
{
	SBUF=dat;
	while(TI==0);
	TI=0;
}
//�����ض���
char putchar(char c)
{
	//����ض��򵽴���
	SendByte(c);
	return c;  //���ظ������ĵ�����printf
}

unsigned char Rdat;
//�����жϷ�����
void ServiceUart() interrupt 4
{
	uint8_t result=0;
	if(RI==1)//����������
	{
		Rdat=SBUF;//RdatΪ����λ�����յ�������
		result=StrCheck(Rdat);
		RI=0;				
		SendByte(Rdat);//�ٽ��յ��������ٷ��͵���λ��
	}
}
