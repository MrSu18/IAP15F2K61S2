#ifndef	_SU_DIGITAL_TUBE_H
#define	_SU_DIGITAL_TUBE_H

#include "su_common_typedef.h"

extern uint8_t code t_display[];
extern uint8_t code float_display[];
extern uint8_t code T_COM[];
extern uint8_t digitaltube_show[8];//���ڴ���������ʾ�����������޸��������ʾ��ֵ

void DigitalTubeDisplay(uint8_t com,uint8_t num);//�������ʾ

#endif
