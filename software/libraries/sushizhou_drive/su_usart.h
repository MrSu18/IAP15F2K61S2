#ifndef _SU_USART_H
#define _SU_USART_H

#include "stdio.h"
#include "su_common_typedef.h"

extern uint8_t read_data_cnt;
extern uint8_t read_data_str[4];

void UartInit(void);//´®¿Ú³õÊ¼»¯
uint8_t StrCheck(uint8_t* str , uint8_t* cnt, uint8_t ch);//¼ì²â×Ö·û´®ÊÇ·ñÆ¥Åä£¬×´Ì¬»ú¼ì²â

#endif
