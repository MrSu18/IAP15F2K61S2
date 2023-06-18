#include "su_ultrasonic.h"
#include <intrins.h>//_nop_���������ӳ�
#include <stc15f2k60s2.h>
#include "main.h"
#include "stdio.h"

uint8_t distance=0;

sbit TX = P1^0; // ��������
sbit RX = P1^1; // ��������

void Delay12us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 3;
	while (--i);
}


void UltrasonicStar(void)//����������ģ��
{ 
	unsigned char ucNum=10;
	TX=0;
	TL0=0XF4;TH0=0XFF;
	TR0=1;
	while (ucNum--)
	{
		while (!TF0);
		TX^=1;
		TF0=0;
	}
	TR0=0;
	TL0=TH0=0;
//	unsigned char i;
//	for(i=0;i<8;i++)
//	{
//		TX=1;
//		Delay12us();
//		TX=0;
//		Delay12us();
//	}
} 

unsigned char UltrasonicMeasure(void) //��Ҫ�õ�ʱ��ֱ�ӵ�������ͺ���
{ 
	unsigned int time=0;
	float danwei_huansuan=0;
	danwei_huansuan=(float)(u_speed);
	danwei_huansuan=danwei_huansuan/2/10000;
	TMOD&=0XF0;
	TL0=TH0=0;
	UltrasonicStar();
	TR0=1;//��ʼ��ʱ
	while((RX==1)&&(TF0==0));//�ȴ�RX�źű�0�����ܵ��������ź�
	TR0=0;//ֹͣ��ʱ
	if(TF0==0)
	{
		time=TH0<<8|TL0;//������ȥ������ʱ��
		//����ֵ+1��ʾ1us����Ϊ��12T
		return time*danwei_huansuan;//0.017;//ʱ�任��
//		return time*0.017;
	}
	else
	{
		TF0=0;
		return 0;
	}
}
