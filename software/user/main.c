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

uint8_t adc_flag=0,temperature_flag=0,ultrasonic_flag=0;

void main(void)
{	
	uint8_t adc,eeprom;
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
		if(adc_flag==1)
		{
			adc=PCF8591_ADC(0x43);
			Write_Eeprom(0,adc);
			adc_flag=0;
		}
		if (temperature_flag==1)
		{
			Read_DS18B20_temp();
			temperature_flag=0;
		}
		if (ultrasonic_flag==1)
		{
			distance=UltrasonicMeasure();
			ultrasonic_flag=0;
		}
		digitaltube_show[0]=t_display[eeprom/100%10];
		digitaltube_show[1]=t_display[eeprom/10%10];
		digitaltube_show[2]=t_display[eeprom%10];
		digitaltube_show[5]=t_display[adc/100%10];
		digitaltube_show[6]=t_display[adc/10%10];
		digitaltube_show[7]=t_display[adc%10];
	}
	
}



