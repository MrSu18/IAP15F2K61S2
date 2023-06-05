#include "su_pwm.h"
#include <stc15f2k60s2.h>
#include "su_led.h"
#include "su_latch.h"

void PWMSetDuty(uint32_t duty)//设置PWM占空比,满占空比为5
{
	static uint8_t pwm_cnt=0;
	pwm_cnt++;
	if(pwm_cnt==duty)
	{
		P05=0;
		Select_Latch(5);
	}
	else if(pwm_cnt==5)//1ms周期到了，一个PWM的周期到了就拉高
	{
		P05=1;
		Select_Latch(5);
		pwm_cnt=0;
	}
}

