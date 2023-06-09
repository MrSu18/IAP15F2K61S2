#include "su_usart.h"
#include <stc15f2k60s2.h>

uint8_t read_data_str[4]="ST\r\n";
uint8_t read_data_cnt=0;
uint8_t read_data_flag=0;

void UartInit(void)		//9600bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器时钟12T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xE6;			//设置定时初始值
	TH1 = 0xFF;			//设置定时初始值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
    ////////////////////以上为ISP软件生成////////////////
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
//		SendByte(Rdat);//再将收到的数据再发送到上位机
	}
}

uint8_t StrCheck(uint8_t* str , uint8_t* cnt, uint8_t ch)//检测字符串是否匹配，状态机检测
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

