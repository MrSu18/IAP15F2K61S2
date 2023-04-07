#include "su_usart.h"
#include <stc15f2k60s2.h>
#include "su_common_typedef.h"

void UartInit(void)		//9600bps@12.000MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR &= 0xFB;		//��ʱ��ʱ��12Tģʽ
	T2L = 0xE6;			//���ö�ʱ��ʼֵ
	T2H = 0xFF;			//���ö�ʱ��ʼֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ
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