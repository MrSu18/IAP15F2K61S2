#include "su_led.h"
#include "su_key.h"
#include "su_common_typedef.h"
#include "delay.h"
#include "timer.h"
#include "su_ds1302.h"
#include "su_S12.h"
#include "stdio.h"
#include "su_usart.h"


unsigned char Rdat;

//***************串口中断服务子程序******************************************
// void ServiceUart() interrupt 4
// {
// 	if(RI==1)//如果接收完成
// 	{
// 		Rdat=SBUF;//Rdat为从上位机接收到的数据
// 		RI=0;				
// 		SendByte(Rdat);//再将收到的数据再发送到上位机
// 	}
// }


void main(void)
{
    ENABLE_LED_LATCH;
	UartInit();
	while (1)
    {
		printf("hello\r\n");
		Delay500ms();
    }
}

void Time0Isr() interrupt 1	//定时器0中断回调函数
{
	static uint8_t num=0;
	if(num<100)
	{
		num++;
	}
	else
	{
		LED1=~LED1;//中断服务函数，如果是定时器没有自动重装载的话记得在这里重装初始，即设置：TH0和TL0的值
		num=0;
	}
}

