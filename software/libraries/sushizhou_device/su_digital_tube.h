#ifndef	_SU_DIGITAL_TUBE_H
#define	_SU_DIGITAL_TUBE_H

#include "su_common_typedef.h"

#define ENABLE_DIGITALTUBE_DUANGXUAN_LATCH P2=(P2&0X1F)|0xE0 //使能数码管段选锁存器Y7C
#define ENABLE_DIGITALTUBE_WEIXUAN_LATCH P2=(P2&0X1F)|0xC0 //使能数码管段选锁存器Y6C

extern uint8_t code t_display[];

#endif
