#ifndef _SU_KEY_H
#define	_SU_KEY_H

#include "su_common_typedef.h"

//��������
sbit S7=P3^0;
sbit S6=P3^1;
sbit S5=P3^2;
sbit S4=P3^3;

uint8_t ReadKey(void);//��������ɨ�躯��
uint8_t	ReadKeyBoard(void);

#endif
