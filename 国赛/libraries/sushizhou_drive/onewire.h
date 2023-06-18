#ifndef _ONE_WIRE_H
#define _ONE_WIRE_H

void Delay_OneWire(unsigned int t);
void Write_DS18B20(unsigned char dat);
unsigned char Read_DS18B20(void);
bit init_ds18b20(void);


#endif
