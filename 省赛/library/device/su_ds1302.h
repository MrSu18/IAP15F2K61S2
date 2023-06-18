#ifndef __DS1302_H
#define __DS1302_H

#include "su_common_typedef.h"

extern uint8_t TimeBuff[7];//ʱ������


/********************������ʱ�����������*************************/
void Write_Ds1302(unsigned char temp);
void Write_Ds1302_Byte( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302_Byte( unsigned char address );
/**************************************************************/

/*******************��ȡ���ݵĽӿڴ���***********************/
void DS1302_Read_Time(void);
void DS1302_Write_Time(void);

#endif
