#ifndef _SU_LED_H
#define	_SU_LED_H

#include <stc15f2k60s2.h>

//LED锁存器
#define	ENABLE_LED_LATCH	P2 = (P2&0x1f)|0x80	//使能LED对应的锁存器设置为透传模式 P2 & (0001 1111) | (1000 0000)
//状态宏定义
#define	ON	0
#define	OFF	1

//LED
sbit LED1=P0^0;
sbit LED2=P0^1;
sbit LED3=P0^2;
sbit LED4=P0^3;
sbit LED5=P0^4;
sbit LED6=P0^5;
sbit LED7=P0^6;
sbit LED8=P0^7;

#endif
