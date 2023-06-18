#ifndef _SU_LED_H
#define	_SU_LED_H

#include <stc15f2k60s2.h>
#include "su_common_typedef.h"

//状态宏定义
#define	ON	0
#define	OFF	1

typedef struct LED_t//创建个LED结构体，赋值的时候打开锁存器P0=这个结构体定义的变量即可
{
    uint8_t led1:1;
    uint8_t led2:1;
    uint8_t led3:1;
    uint8_t led4:1;
    uint8_t led5:1;
    uint8_t led6:1;
    uint8_t led7:1;
    uint8_t led8:1;
}LED_t;

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
