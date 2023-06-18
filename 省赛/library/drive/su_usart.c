#include "su_usart.h"
#include <stc15f2k60s2.h>
#include "su_common_typedef.h"

void UartInit(void)		//9600bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = 0xC7;		//设置定时初始值
	T2H = 0xFE;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时

    ////////////////////以上为ISP软件生成////////////////
//  EA=1;       //打开中断总开关
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
 void ServiceUart() interrupt 4
 {
 	if(RI==1)//如果接收完成
 	{
 		Rdat=SBUF;//Rdat为从上位机接收到的数据
 		RI=0;				
 		SendByte(Rdat);//再将收到的数据再发送到上位机
 	}
 }