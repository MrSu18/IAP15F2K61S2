#ifndef _SU_USART_H
#define _SU_USART_H

#include "stdio.h"
#include "su_common_typedef.h"

extern uint8_t usart_result;//用于反馈串口接受到的指令是什么

void UartInit(void);//串口初始化
uint8_t StrCheck(uint8_t ch);//检测字符串是否匹配，状态机检测


#endif
