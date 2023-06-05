#include "su_pwm.h"
#include <stc15f2k60s2.h>
#include "su_led.h"
#include "su_latch.h"

void PWMSetDuty(uint32_t duty)//����PWMռ�ձ�,��ռ�ձ�Ϊ5
{
	static uint8_t pwm_cnt=0;
	pwm_cnt++;
	if(pwm_cnt==duty)
	{
		P05=0;
		Select_Latch(5);
	}
	else if(pwm_cnt==5)//1ms���ڵ��ˣ�һ��PWM�����ڵ��˾�����
	{
		P05=1;
		Select_Latch(5);
		pwm_cnt=0;
	}
}

