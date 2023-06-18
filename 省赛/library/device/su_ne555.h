#ifndef __NE555_H_ 
#define __ME555_H_ 

#include "su_common_typedef.h"

extern uint32_t frequency;//频率

//必须用定时器1作为定时器，因为板子上的P34才是拿来测量频率的引脚所以计数器要用定时器0
void Ne555TimInit(void);//NE555定时器初始化
void Ne555CountInit(void);//NE555记数器初始化

#endif