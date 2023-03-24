#include "su_S12.h"
#include "su_usart.h"
#include "delay.h"
#include "su_ds18b20.h"

void main(void)
{
	float temperature=0;
	char temp=0;
	
	DeviceInit();//设备初始化
	UartInit();//串口初始化用于调试
	
	while(1)
	{
//		temp=rd_temperature();
		temperature=Read_DS18B20_temp();
		printf("%f\r\n",temperature);
		Delay500ms();
	}
}



