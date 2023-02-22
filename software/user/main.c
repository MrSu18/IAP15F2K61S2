#include "su_led.h"
#include "su_key.h"
#include "su_common_typedef.h"
#include "delay.h"
#include "timer.h"
#include "su_digital_tube.h"

void main(void)
{
    ENABLE_LED_LATCH;
	while (1)
    {
		
		//*******第一位显示1*************
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;//Y6C有效，P0控制显示哪一位
		P0=0x01;          //P0=0000 0001，选通第一位（最左边一位）
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;//Y7C有效，P0控制显示哪一个数字
		P0=~t_display[1];	//给P0输入数字1的段码，让数码管显示1	
		Delay2ms();
		//*******第二位显示2*************	
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;	//Y6C有效
		P0=0x02;          //P0=0000 0010，选通第二位
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;	//Y7C有效
		P0=~t_display[2];	//给P0输入数字2的段码，让数码管显示2		
		Delay2ms();
		//*******第三位显示3*************		
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;	//Y6C有效
		P0=0x04;					//P0=0000 0100，选通第三位
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;	//Y7C有效
		P0=~t_display[3];	//给P0输入数字3的段码，让数码管显示3
		Delay2ms();
		//*******第四位显示4*************		
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;
		P0=0x08;					//P0=0000 1000，选通第四位
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;
		P0=~t_display[4];	//数码管显示4
		Delay2ms();
		//*******第五位显示*************		
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;
		P0=0x10;					//P0=0001 0000，选通第五位
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;
		P0=~t_display[5];	//数码管显示5
		Delay2ms();
		//*******第六位显示6*************		
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;
		P0=0x20;					//P0=0010 0000，选通第六位
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;
		P0=~t_display[6];	//数码管显示6	
		Delay2ms();
		//*******第七位显示7*************		
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;
		P0=0x40;					//P0=0100 0000，选通第七位
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;
		P0=~t_display[7];	//数码管显示7	
		Delay2ms();
		//*******第八位显示8*************		
		ENABLE_DIGITALTUBE_WEIXUAN_LATCH;
		P0=0x80;					//P0=1000 0000，选通第八位
		ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;
		P0=~t_display[8];	//数码管显示8	
		Delay2ms();	
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

