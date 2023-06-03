#include <stc15f2k60s2.h>
#include <string.h>
#include "su_common_typedef.h"
#include "su_latch.h"//锁存器
#include "su_led.h"//LED的结构体
#include "su_ne555.h"
#include "su_usart.h"
#include "su_ultrasonic.h"
#include "delay.h"
#include "su_digital_tube.h"
#include "su_S12.h"

void main(void)
{	
	//关闭蜂鸣器和继电器
	Select_Latch(5);P04=0;P06=0;
	//初始化led全为暗
	memset(&led_object,0xff,1);Select_Latch(4);P0=*(uint8_t*)&led_object;
	//NE555初始化
	Ne555TimInit();//NE555定时器初始化
//	Ne555CountInit();//NE555记数器初始化
	//串口初始化
//	UartInit();
	//开启总中断EA
	EA=1;
	while (1)
	{
		uint8_t distance=UltrasonicMeasure();
//		printf("%bu\r\n",distance);
		digitaltube_show[2]=t_display[distance%10];
		digitaltube_show[1]=t_display[distance/10%10];
		digitaltube_show[0]=t_display[distance/100%10];
		Delay100ms();
	}
	
}



