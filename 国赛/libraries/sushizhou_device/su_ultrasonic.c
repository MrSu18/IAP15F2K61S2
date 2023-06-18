#include "su_ultrasonic.h"
#include <intrins.h>//_nop_机器周期延迟
#include <stc15f2k60s2.h>
#include "main.h"
#include "stdio.h"

uint8_t distance=0;

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

unsigned char UltrasonicMeasure(void) //需要用的时候直接调用这里就好了
{ 
	unsigned int time=0;
	float danwei_huansuan=0;
	danwei_huansuan=(float)(u_speed);
	danwei_huansuan=danwei_huansuan/2/10000;
	TMOD&=0XF0;
	TL0=TH0=0;
	UltrasonicStar();
	TR0=1;//开始计时
	while((RX==1)&&(TF0==0));//等待RX信号变0，接受到回来的信号
	TR0=0;//停止计时
	if(TF0==0)
	{
		time=TH0<<8|TL0;//声波出去回来的时间
		//计数值+1表示1us，因为是12T
		return time*danwei_huansuan;//0.017;//时间换算
//		return time*0.017;
	}
	else
	{
		TF0=0;
		return 0;
	}
}
