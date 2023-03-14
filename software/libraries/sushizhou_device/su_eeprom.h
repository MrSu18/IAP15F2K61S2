#ifndef _SU_EEPROM_H
#define _SU_EEPROM_H

#include "su_common_typedef.h"
#include "iic.h"
#include "delay.h"

void Write_Eeprom(uint8_t add,uint8_t val);
uint8_t Read_Eeprom(uint8_t add);

#endif
