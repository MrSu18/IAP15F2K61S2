#ifndef _SU_KEY_H
#define	_SU_KEY_H

#include "su_common_typedef.h"

//独立按键
sbit S7=P3^0;
sbit S6=P3^1;
sbit S5=P3^2;
sbit S4=P3^3;

uint8_t ReadKey(void);//独立按键扫描函数
uint8_t	ReadKeyBoard(void);

#endif
