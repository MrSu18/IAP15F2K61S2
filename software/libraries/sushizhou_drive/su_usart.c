#include "su_usart.h"
#include <stc15f2k60s2.h>

uint8_t read_data_str[4]="ST\r\n";
uint8_t read_data_cnt=0;
uint8_t read_data_flag=0;

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
		result=StrCheck(read_data_str,&read_data_cnt,Rdat);
		if(result==1)
		{
			printf("queset read data\r\n");
		}
		else if(result==2)
		{
			printf("queset read parameter\r\n");
		}
		RI=0;				
//		SendByte(Rdat);//�ٽ��յ��������ٷ��͵���λ��
	}
}

uint8_t StrCheck(uint8_t* str , uint8_t* cnt, uint8_t ch)//����ַ����Ƿ�ƥ�䣬״̬�����
{
	if(str[*cnt]==ch)
	{
		(*cnt)++;
		if(*cnt==4)
		{
			(*cnt)=0;
			return 1;
		}
	}
	else
	{
		(*cnt)=0;
	}
	return 0;
}

