#include "su_led.h"
#include "su_common_typedef.h"
#include "delay.h"

void main(void)
{
    ENABLE_LED_LATCH;
	while (1)
    {
        LED1(ON);  //LEDϨ��
        Delay500ms();
        LED1(OFF);  //LEDϨ��
        Delay500ms();
    }
}
