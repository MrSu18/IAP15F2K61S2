#include <stc15f2k60s2.h>
#include <string.h>
#include "su_latch.h"//锁存器
#include "su_led.h"//LED的结构体

void main(void)
{	
	//关闭蜂鸣器和继电器
	Select_Latch(5);P04=0;P06=0;
	//初始化led全为暗
	memset(&led_object,0xff,1);Select_Latch(4);P0=*(uint8_t*)&led_object;
	while (1)
	{
		;
	}
	
}



