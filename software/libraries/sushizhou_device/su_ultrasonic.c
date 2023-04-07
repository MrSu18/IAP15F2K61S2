#include "su_ultrasonic.h"
#include <intrins.h>//_nop_机器周期延迟
#include <stc15f2k60s2.h>

sbit TX = P1^0; // 发射引脚
sbit RX = P1^1; // 接收引脚

void Delay12us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 3;
	while (--i);
}


void UltrasonicStar(void)//启动超声波模块
{ 
	unsigned char i;
	for(i=0;i<8;i++)
	{
		TX=1;
		Delay12us();
		TX=0;
		Delay12us();
	}
} 

unsigned char UltrasonicMeasure(void) 
{ 
	unsigned int time=0;
	TMOD&=0XF0;
	TL0=TH0=0;
	UltrasonicStar();
	TR0=1;//开始计时
	while((RX==1)&&(TF0==0));
	TR0=0;
	if(TF0==0)
	{
		time=TH0<<8|TL0;
		
		return time*0.017;
	}
	else
	{
		TF0=0;
		return 200;
	}
	return 200;
}
