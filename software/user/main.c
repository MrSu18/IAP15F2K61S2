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
#include "su_pcf8591.h"

#include "iic.h"
#define PCF8591_W_ADD	0X90	//PCF8591的写地址
#define PCF8591_R_ADD	0X91	//PCF8591的读地址

void main(void)
{	
	uint8_t adc;
	//关闭蜂鸣器和继电器
	P04=0;P06=0;Select_Latch(5);
	//初始化led全为暗
	memset(&led_object,0xff,1);P0=*(uint8_t*)&led_object;Select_Latch(4);
	//NE555初始化
	Ne555TimInit();//NE555定时器初始化
	Ne555CountInit();//NE555记数器初始化
	//串口初始化
	UartInit();
	//adc模块初始化
	Pcf8591_Adc_Init(0x43);//允许DA输出ADC采集通道3
	//开启总中断EA
	EA=1;
	while (1)
	{
		printf("%d\r\n",frequency);
		Delay500ms();
	}
	
}



