#include "su_eeprom.h"

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
	Delay10ms();
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
  
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(add);
	IIC_WaitAck();
	IIC_Start();
	IIC_SendByte(0xa1);
	IIC_WaitAck();
	da = IIC_RecByte();
	IIC_SendAck(0); 
	IIC_Stop();
	
	return da;
}
