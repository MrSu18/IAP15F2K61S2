#ifndef _SU_LED_H
#define	_SU_LED_H

#include <stc15f2k60s2.h>
#include "su_common_typedef.h"

typedef struct LED_t//������LED�ṹ�壬��ֵ��ʱ���������P0=����ṹ�嶨��ı�������
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

void LEDResponse(LED_t led);//LED���ݲ���������Ӧ

#endif
