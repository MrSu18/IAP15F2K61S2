#include "su_led.h"
#include "su_key.h"
#include "su_common_typedef.h"
#include "delay.h"

void main(void)
{
	uint8_t temp;
    ENABLE_LED_LATCH;
	while (1)
    {
		temp=ReadKey();
		if(temp!=0xff)
		{
			Delay10ms();
			temp=ReadKey();
			if(temp!=0xff)
			{
				switch(temp)
				{
					case 1: LED1=!LED1;break;
					case 2: LED2=!LED2;break;
					case 3: LED3=!LED3;break;
					case 4: LED4=!LED4;break;
					default: LED5=!LED5;break;
				}
				while(ReadKey()!=0xff);
			}
		}
    }
}
