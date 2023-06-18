#include "su_pcf8591.h"
#include "iic.h"

#define PCF8591_W_ADD	0X90	//PCF8591��д��ַ
#define PCF8591_R_ADD	0X91	//PCF8591�Ķ���ַ

//����addr��������
bit Pcf8591_Adc_Init(uint8_t addr)
{
	bit OK = 0;
	IIC_Start();
	IIC_SendByte(PCF8591_W_ADD);
	if(!IIC_WaitAck());
	{
		IIC_SendByte(addr);	
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

