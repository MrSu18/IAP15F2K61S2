#include "su_pcf8591.h"
#include "iic.h"

#define PCF8591_W_ADD	0X90	//PCF8591的写地址
#define PCF8591_R_ADD	0X91	//PCF8591的读地址

//参数control_byte：控制字
bit Pcf8591_Adc_Init(uint8_t control_byte)
{
	bit OK = 0;
	IIC_Start();
	IIC_SendByte(PCF8591_W_ADD);
	if(!IIC_WaitAck());
	{
		IIC_SendByte(control_byte);	
		if(!IIC_WaitAck());
		{
			IIC_Stop();
			IIC_Start();
			IIC_SendByte(PCF8591_R_ADD);
			if(!IIC_WaitAck())
			{
				OK = 1;
			}
		}
	}
	return OK;
}

uint8_t AdcRead()
{
	uint8_t _data;
	_data = IIC_RecByte();
	IIC_SendAck(0);
	return _data;
}

//读取ADC的值
uint8_t PCF8591_ADC(uint8_t control_byte)
{
	uint8_t _data;
	IIC_Start();
	IIC_SendByte(PCF8591_W_ADD);		//发送器件地址，写
	IIC_WaitAck();
	IIC_SendByte(control_byte);		//发送控制字节
	IIC_WaitAck();
	IIC_Start();
	IIC_SendByte(PCF8591_R_ADD);		//发送器件地址，读
	IIC_WaitAck();
	_data=IIC_RecByte();		//读一个字节数据
	IIC_SendAck(1);			//主机发送非应答，不再接收数据
	IIC_Stop();
	return _data;
}

// DAC 输出
void PCF8591_Dac(uint8_t control_byte,unsigned char dat) // 控制字，DA输出的值
{ 
	IIC_Start(); 
	IIC_SendByte(PCF8591_W_ADD); 
	IIC_WaitAck(); 
	IIC_SendByte(control_byte); // 允许 DAC，ADC 通道 3 
	IIC_WaitAck(); 
	IIC_SendByte(dat); // dat-输出数模转换的数据
	IIC_WaitAck(); 
	IIC_Stop(); 
} 
