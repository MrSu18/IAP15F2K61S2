#include "su_usart.h"
#include <stc15f2k60s2.h>

uint8_t usart_result=0;//用于反馈串口接受到的指令是什么

void UartInit(void)		//4800bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0x8F;			//设定定时初值
	TH1 = 0xFD;			//设定定时初值
	ET1 = 0;			//禁止定时器1中断
	TR1 = 1;			//启动定时器1
    ////////////////////以上为ISP软件生成////////////////
//	ES=1;       // 允许串口中断
}


//***************发送一个字节******************************************
void SendByte(unsigned char dat)
{
	SBUF=dat;
	while(TI==0);
	TI=0;
}
//串口重定向
char putchar(char c)
{
	//输出重定向到串口
	SendByte(c);
	return c;  //返回给函数的调用者printf
}

unsigned char Rdat;
//串口中断服务函数
void ServiceUart() interrupt 4
{
	uint8_t result=0;
	if(RI==1)//如果接收完成
	{
		Rdat=SBUF;//Rdat为从上位机接收到的数据
		result=StrCheck(Rdat);
		RI=0;				
		SendByte(Rdat);//再将收到的数据再发送到上位机
	}
}
