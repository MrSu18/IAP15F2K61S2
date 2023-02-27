#include "su_usart.h"
#include <stc15f2k60s2.h>
#include "stdio.h"
#include "su_common_typedef.h"

void UartInit(void)		//115200bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xE8;			//设置定时初始值
	TH1 = 0xFF;			//设置定时初始值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
    ////////////////////以上为ISP软件生成////////////////
    EA=1;       //打开中断总开关
	ES=1;       // 允许串口中断
}

//***************发送一个字节******************************************
void SendByte(unsigned char dat)
{
	SBUF=dat;
	while(TI==0);
	TI=0;
}
//串口重定向
// int fputc(int ch, FILE *f)
// {
//     SendByte(ch);
//     return ch;
// }
char putchar(char c)
{
	//输出重定向到串口
	SendByte(c);
	return c;  //返回给函数的调用者printf
}
