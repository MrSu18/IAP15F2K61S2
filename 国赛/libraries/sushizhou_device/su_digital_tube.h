#ifndef	_SU_DIGITAL_TUBE_H
#define	_SU_DIGITAL_TUBE_H

#include "su_common_typedef.h"

extern uint8_t code t_display[];
extern uint8_t code float_display[];
extern uint8_t code T_COM[];
extern uint8_t digitaltube_show[8];//用于存放数码管显示的数字用于修改数码管显示的值

void DigitalTubeDisplay(uint8_t com,uint8_t num);//数码管显示

#endif
