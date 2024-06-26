#include "su_eeprom.h"
#include <stc15f2k60s2.h>

#define AT24C02_W_ADD 0xa0 //

/**
* @brief 向AT24C02(add)中写入数据val
*
* @param[in] add - AT24C02存储地址
* @param[in] val - 待写入AT24C02相应地址的数据
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
* @brief 从AT24C02(add)中读出数据da
*
* @param[in] add - AT24C02存储地址
* @param[out] da - 从AT24C02相应地址中读取到的数据
* @return - da
*/
uint8_t Read_Eeprom(uint8_t add)
{
	uint8_t da;
	EA = 0;//关闭中断，中断可能会影响总线时序
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
	// IIC_SendAck(0);//错了，一个改成waitack 
	IIC_WaitAck();
	IIC_Stop();
	EA = 1;//打开中断

	Delay5ms();
	return da;
}
