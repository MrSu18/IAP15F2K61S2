#include "su_exit.h"
#include <stc15f2k60s2.h>
#include "delay.h"
#include "su_led.h"

void EXTI_Init(void)
{
    IT0=1;//下降沿触发
	EX0=1;//外部中断0中断允许    enable external 0

    IT1=1;//下降沿触发
    EX1=1;//使能外部中断1

	EA=1;//总中断允许
}


//外部中断0中断服务函数
void EXTI0_Sever(void) interrupt 0
{
	P2 = ((P2&0x1f)|0x80);
    LED1 = ~LED1;    
	P2 = P2&0x1f;
}
                        
//外部中断1中断服务函数
void EXTI1_Sever(void) interrupt 2
{
	P2 = ((P2&0x1f)|0x80);
    LED2 = ~LED2;    
	P2 = P2&0x1f;
}
