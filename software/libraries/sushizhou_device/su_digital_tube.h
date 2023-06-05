#ifndef	_SU_DIGITAL_TUBE_H
#define	_SU_DIGITAL_TUBE_H

#include "su_common_typedef.h"

#define ENABLE_DIGITALTUBE_DUANGXUAN_LATCH P2=(P2&0X1F)|0xE0 //使能数码管段选锁存器Y7C
#define ENABLE_DIGITALTUBE_WEIXUAN_LATCH P2=(P2&0X1F)|0xC0 //使能数码管段选锁存器Y6C

extern uint8_t code t_display[];
extern uint8_t code T_COM[];
extern uint8_t digitaltube_show[8];//用于存放数码管显示的数字用于修改数码管显示的值

void DigitalTubeDisplay(uint8_t com,uint8_t num);//数码管显示

#endif
