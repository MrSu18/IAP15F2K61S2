#include "su_led.h"
#include "su_latch.h"

LED_t led_object;

void LEDResponse(LED_t led)//LED���ݲ���������Ӧ
{
	P0=*(uint8_t*)&led;
	Select_Latch(4);
}
