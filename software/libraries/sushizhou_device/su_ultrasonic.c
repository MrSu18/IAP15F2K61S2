#include "su_ultrasonic.h"

sbit TX = P1^0; // 发射引脚
sbit RX = P1^1; // 接收引脚

void Timer0Init_ultrasonic(void) // 12us@12.000MHz 
{ 
 AUXR &= 0x7F; // 定时器时钟 12T 模式
 TMOD &= 0xF0; // 设置定时器模式
 TL0 = 0xF4; // 设置定时初值
 TH0 = 0xFF; // 设置定时初值
 TF0 = 0; // 清除 TF0 标志
 TR0 = 0; // 定时器 0 停止
} 

unsigned char Wave_Recv(void) 
{ 
	unsigned char ucDist, ucNum = 10; 
	TX = 0; 
	TL0 = 0xF4; // 设置定时初值
	TH0 = 0xFF; // 设置定时初值
	TR0 = 1; // 定时器 0 计时
	// TX 引脚发送 40kHz 方波信号驱动超声波发送探头
	while(ucNum--) 
	{ 
		while(!TF0); 
		TX ^= 1; 
		TF0 = 0; 
	} 
	TR0 = 0; 
	TL0 = 0; // 设置定时初值
	TH0 = 0; // 设置定时初值
	TR0 = 1; 
	while(RX && !TF0); // 等待收到脉冲
	TR0 = 0; 
	if(TF0) // 发生溢出
	{ 
		TF0 = 0; 
		ucDist = 255; 
	} 
	else // 计算距离
		ucDist = ((TH0<<8)+TL0)*0.017; 
	return ucDist; 
}
