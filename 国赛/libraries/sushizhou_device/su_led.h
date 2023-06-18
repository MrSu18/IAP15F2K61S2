#ifndef _SU_LED_H
#define	_SU_LED_H

#include <stc15f2k60s2.h>
#include "su_common_typedef.h"

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

extern LED_t led_object;

void LEDResponse(LED_t led);//LED根据参数进行响应

#endif
