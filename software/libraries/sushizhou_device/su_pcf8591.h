#ifndef _SU_PCF8591_H
#define _SU_PCF8591_H

#include "su_common_typedef.h"


bit Pcf8591_Adc_Init(uint8_t control_byte);//初始化pcf8591,并写入控制字
uint8_t AdcRead();
uint8_t PCF8591_ADC(uint8_t control_byte);//不需要初始化，写入地址然后控制字等，全在这
void PCF8591_Dac(uint8_t control_byte,unsigned char dat);//写入控制字然后输出

#endif
