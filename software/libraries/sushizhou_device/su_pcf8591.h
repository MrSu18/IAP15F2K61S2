#ifndef _SU_PCF8591_H
#define _SU_PCF8591_H

#include "su_common_typedef.h"


bit Pcf8591_Adc_Init(uint8_t control_byte);//��ʼ��pcf8591,��д�������
uint8_t AdcRead();
uint8_t PCF8591_ADC(uint8_t control_byte);//����Ҫ��ʼ����д���ַȻ������ֵȣ�ȫ����
void PCF8591_Dac(uint8_t control_byte,unsigned char dat);//д�������Ȼ�����

#endif
