#include "su_S12.h"
#include "su_usart.h"
#include "delay.h"

void main(void)
{
	DeviceInit();//设备初始化
	UartInit();//串口初始化用于调试
	while(1)
	{
		printf("usart test\r\n");
		Delay500ms();
	}
}



