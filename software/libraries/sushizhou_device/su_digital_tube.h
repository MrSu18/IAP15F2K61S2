#ifndef	_SU_DIGITAL_TUBE_H
#define	_SU_DIGITAL_TUBE_H

#include "su_common_typedef.h"

#define ENABLE_DIGITALTUBE_DUANGXUAN_LATCH P2=(P2&0X1F)|0xE0 //ʹ������ܶ�ѡ������Y7C
#define ENABLE_DIGITALTUBE_WEIXUAN_LATCH P2=(P2&0X1F)|0xC0 //ʹ������ܶ�ѡ������Y6C

extern uint8_t code t_display[];
extern uint8_t code T_COM[];
extern uint8_t digitaltube_show[8];//���ڴ���������ʾ�����������޸��������ʾ��ֵ

void DigitalTubeDisplay(uint8_t com,uint8_t num);//�������ʾ

#endif
