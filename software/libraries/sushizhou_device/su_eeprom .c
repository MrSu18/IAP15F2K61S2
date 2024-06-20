#include "su_eeprom.h"
#include <stc15f2k60s2.h>

#define AT24C02_W_ADD 0xa0 //

/**
* @brief ��AT24C02(add)��д������val
*
* @param[in] add - AT24C02�洢��ַ
* @param[in] val - ��д��AT24C02��Ӧ��ַ������
* @return - none
*/
void Write_Eeprom(unsigned char add,unsigned char val)
{
    IIC_Start();
    IIC_SendByte(0xa0);
    IIC_WaitAck();
    IIC_SendByte(add);
    IIC_WaitAck();
    IIC_SendByte(val);
    IIC_WaitAck();
    IIC_Stop();
	Delay5ms();Delay5ms();
}

/**
* @brief ��AT24C02(add)�ж�������da
*
* @param[in] add - AT24C02�洢��ַ
* @param[out] da - ��AT24C02��Ӧ��ַ�ж�ȡ��������
* @return - da
*/
uint8_t Read_Eeprom(uint8_t add)
{
	uint8_t da;
	EA = 0;//�ر��жϣ��жϿ��ܻ�Ӱ������ʱ��
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(add);
	IIC_WaitAck();
	IIC_Stop();

	IIC_Start();
	IIC_SendByte(0xa1);
	IIC_WaitAck();
	da = IIC_RecByte();
	// IIC_SendAck(0);//���ˣ�һ���ĳ�waitack 
	IIC_WaitAck();
	IIC_Stop();
	EA = 1;//���ж�

	Delay5ms();
	return da;
}
