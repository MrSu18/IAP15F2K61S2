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
#include "su_ds18b20.h"
#include "su_eeprom.h"
#include "su_key.h"

uint8_t adc_flag=0,temperature_flag=0,ultrasonic_flag=0;

void main(void)
{	
	uint8_t adc,eeprom,key_now,key_old,key_down;
	uint16_t distance;
	//关闭蜂鸣器和继电器
	P04=0;P06=0;Select_Latch(5);
	//初始化led全为暗
	memset(&led_object,0xff,1);P0=*(uint8_t*)&led_object;Select_Latch(4);
	//NE555初始化
	Ne555TimInit();//NE555定时器初始化
	// Ne555CountInit();//NE555记数器初始化
	//串口初始化
	UartInit();
	eeprom=Read_Eeprom(0);
	//adc模块初始化
	Pcf8591_Adc_Init(0x43);//允许DA输出ADC采集通道3
	//开启总中断EA
	EA=1;
	while (1)
	{
		key_now=ReadKeyBoard();
		key_down=key_now&(key_now^key_old);
		key_old=key_now;
		switch (key_down)
		{
		case 4:
			printf("void UltrasonicStar(void)//启动超声波模块\r\n");
			printf("{ \r\n");
			printf("	unsigned char ucNum=10;\r\n");
			printf("	TX=0;\r\n");
			printf("	TL0=0XF4;TH0=0XFF;\r\n");
			printf("	TR0=1;\r\n");
			printf("	while (ucNum--)\r\n");
			printf("	{\r\n");
			printf("		while (!TF0);\r\n");
			printf("		TX^=1;\r\n");
			printf("		TF0=0;\r\n");
			printf("	}\r\n");
			printf("	TR0=0;\r\n");
			printf("	TL0=TH0=0;\r\n");
			printf("} \r\n");
			break;
		case 5:
			printf("eeprom写操作最后的延迟可以改为5ms\r\n");
			printf("ds18b20中的Delay_OneWire(200);可以去掉\r\n");
			printf("超声波返回值是cm单位\r\n");
			printf("超声波的触发信号按S4打印出来的写\r\n");
			break;
		case 8:
			printf("uint8_t StrCheck(uint8_t* str , uint8_t* cnt, uint8_t ch)//检测字符串是否匹配，状态机检测\r\n");
			printf("{\r\n");
			printf("	if(str[*cnt]==ch)\r\n");
			printf("	{\r\n");
			printf("		(*cnt)++;\r\n");
			printf("		if(*cnt==4)\r\n");
			printf("		{\r\n");
			printf("			(*cnt)=0;\r\n");
			printf("			return 1;\r\n");
			printf("		}\r\n");
			printf("	}\r\n");
			printf("	else\r\n");
			printf("	{\r\n");
			printf("		(*cnt)=0;\r\n");
			printf("	}\r\n");
			printf("	return 0;\r\n");
			printf("}\r\n");
			break;
		default:
			break;
		}
	}
	
}



