#ifndef __NE555_H_ 
#define __ME555_H_ 

#include "su_common_typedef.h"

extern uint8_t frequency;//Ƶ��

//�����ö�ʱ��1��Ϊ��ʱ������Ϊ�����ϵ�P34������������Ƶ�ʵ��������Լ�����Ҫ�ö�ʱ��0
void Ne555TimInit(void);//NE555��ʱ����ʼ��
void Ne555CountInit(void);//NE555��������ʼ��

#endif