#include "su_S12.h"
#include "su_usart.h"
#include "delay.h"
#include "su_ds18b20.h"
#include "su_key.h"
#include "su_pcf8591.h"
#include "su_latch.h"
#include <stc15f2k60s2.h>
#include "su_digital_tube.h"
#include "su_ultrasonic.h"
#include "su_ne555.h"

void main(void)
{	
	unsigned char temp=0,status=0;
	
//	DeviceInit();//设备初始化
	UartInit();//串口初始化用于调试
//	PCF8591_Dac(0xff);
	Ne555TimInit();
	Ne555CountInit();
	EA=1;
	while(1)
	{
//		temp=UltrasonicMeasure();
//		printf("hello\r\n");
		printf("%bu\r\n",frequency);
		Delay100ms();
//		S13Function();
	}
}



