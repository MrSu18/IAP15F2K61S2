#include "su_led.h"
#include "su_common_typedef.h"
#include "delay.h"

void main(void)
{
    ENABLE_LED_LATCH;
	while (1)
    {
        LED1(ON);  //LEDÏ¨Ãð
        Delay500ms();
        LED1(OFF);  //LEDÏ¨Ãð
        Delay500ms();
    }
}
