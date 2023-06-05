#include "su_usart.h"
#include <stc15f2k60s2.h>
#include "su_common_typedef.h"

void UartInit(void)		//9600bps@12.000MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0xE6;			//���ö�ʱ��ʼֵ
	TH1 = 0xFF;			//���ö�ʱ��ʼֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ
    ////////////////////����ΪISP�������////////////////
//  EA=1;       //���ж��ܿ���
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
void ServiceUart() interrupt 4
{
	if(RI==1)//����������
	{
		Rdat=SBUF;//RdatΪ����λ�����յ�������
		RI=0;				
		SendByte(Rdat);//�ٽ��յ��������ٷ��͵���λ��
	}
}