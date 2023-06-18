#include "su_ds18b20.h"
#include "reg52.h"
#include "onewire.h"


uint16_t temperature=830;


void Read_DS18B20_temp()
{
	unsigned char LSB=0,MSB=0;
	int temp;
	
	init_ds18b20();
	Write_DS18B20(0xCC);
    Write_DS18B20(0x44); //启动温度转换
	Delay_OneWire(200);
	
	init_ds18b20();
    Write_DS18B20(0xCC);
    Write_DS18B20(0xBE); //读取寄存器
	
	LSB=Read_DS18B20();	//低字节
	MSB=Read_DS18B20();	//高字节
	
	temp=MSB<<8|LSB;//把高低字节合起来变成16位数据
	
	temperature=(int)(temp*0.0625*10);//扩大十倍为了方便求余,如果保留一位小数则扩大10倍，如果两位就100
}