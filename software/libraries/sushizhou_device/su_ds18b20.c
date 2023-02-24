#include "su_ds18b20.h"
#include "reg52.h"

sbit DQ = P1^4;  //单总线接口

//单总线延时函数
void Delay_OneWire(unsigned int t)  //STC89C52RC
{
	while(t--);
}

//通过单总线向DS18B20写一个字节
void Write_DS18B20(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay_OneWire(50);
		DQ = 1;
		dat >>= 1;
	}
	Delay_OneWire(50);
}

//从DS18B20读取一个字节
unsigned char Read_DS18B20(void)
{
	unsigned char i;
	unsigned char dat;
  
	for(i=0;i<8;i++)
	{
		DQ = 0;
		dat >>= 1;
		DQ = 1;
		if(DQ)
		{
			dat |= 0x80;
		}	    
		Delay_OneWire(50);
	}
	return dat;
}

//DS18B20设备初始化
bit init_ds18b20(void)
{
    bit initflag = 0;

    DQ = 1;
    Delay_OneWire(120);
    DQ = 0;
    Delay_OneWire(800);
    DQ = 1;
    Delay_OneWire(100); 
    initflag = DQ;     
    Delay_OneWire(50);

    return initflag;
}

//DS18B20温度采集程序：整数
unsigned char rd_temperature()
{
    unsigned char low,high;
    unsigned int Decimals,Integer;	//定义局部变量，整数、小数
    char temp;

    init_ds18b20();
    Write_DS18B20(0xCC);
    Write_DS18B20(0x44); //启动温度转换
    Delay_OneWire(200);

    init_ds18b20();
    Write_DS18B20(0xCC);
    Write_DS18B20(0xBE); //读取寄存器

    low = Read_DS18B20(); //低字节
    high = Read_DS18B20(); //高字节

    temp = high<<4;
    temp |= (low>>4);

    return temp;
}

