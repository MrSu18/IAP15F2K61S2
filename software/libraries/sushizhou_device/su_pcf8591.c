#include "su_pcf8591.h"
#include "iic.h"

#define PCF8591_W_ADD	0X90	//PCF8591��д��ַ
#define PCF8591_R_ADD	0X91	//PCF8591�Ķ���ַ

//����control_byte��������
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

//��ȡADC��ֵ
uint8_t PCF8591_ADC(uint8_t control_byte)
{
	uint8_t _data;
	IIC_Start();
	IIC_SendByte(PCF8591_W_ADD);		//����������ַ��д
	IIC_WaitAck();
	IIC_SendByte(control_byte);		//���Ϳ����ֽ�
	IIC_WaitAck();
	IIC_Start();
	IIC_SendByte(PCF8591_R_ADD);		//����������ַ����
	IIC_WaitAck();
	_data=IIC_RecByte();		//��һ���ֽ�����
	IIC_SendAck(1);			//�������ͷ�Ӧ�𣬲��ٽ�������
	IIC_Stop();
	return _data;
}

// DAC ���
void PCF8591_Dac(uint8_t control_byte,unsigned char dat) // �����֣�DA�����ֵ
{ 
	IIC_Start(); 
	IIC_SendByte(PCF8591_W_ADD); 
	IIC_WaitAck(); 
	IIC_SendByte(control_byte); // ���� DAC��ADC ͨ�� 3 
	IIC_WaitAck(); 
	IIC_SendByte(dat); // dat-�����ģת��������
	IIC_WaitAck(); 
	IIC_Stop(); 
} 
