#ifndef __ONEWIRE_H
#define __ONEWIRE_H

extern int temperature;

unsigned char rd_temperature(void);
void Read_DS18B20_temp();

#endif