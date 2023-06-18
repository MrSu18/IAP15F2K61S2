#include <reg52.h>
#include <intrins.h>
#include "su_ds1302.h"


sbit SCK=P1^7;		
sbit SDA=P2^3;		
sbit RST=P1^3;   // DS1302复位												

uint8_t TimeBuff[7]={17,9,1,6,13,03,05};				// 时间数组
// TimeBuff[0] 代表年份，范围00-99
// TimeBuff[1] 代表月份，范围1-12
// TimeBuff[2] 代表日期，范围1-31
// TimeBuff[3] 代表星期，范围1-7
// TimeBuff[4] 代表小时，范围00-23
// TimeBuff[5] 代表分钟，范围00-59
// TimeBuff[6] 代表秒钟，范围00-59

void Write_Ds1302(unsigned  char temp)//竞赛给出 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302_Byte( unsigned char address,unsigned char dat )//竞赛给出     
{
	RST=0;	_nop_();
	SCK=0;	_nop_();
	RST=1; 	_nop_();  
	Write_Ds1302(address);	
	Write_Ds1302(dat);		
	RST=0; 
}

unsigned char Read_Ds1302_Byte ( unsigned char address )//竞赛给出
{
	unsigned char i,temp=0x00;
	RST=0;	_nop_();
	SCK=0;	_nop_();
	RST=1;	_nop_();
	Write_Ds1302(address);
	for (i=0;i<8;i++) 	
	{		
		SCK=0;
		temp>>=1;	
		if(SDA)
		temp|=0x80;	
		SCK=1;
	} 
	RST=0;	_nop_();
	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}

/*********************************************************/
// 向DS1302写入时间数据
/*********************************************************/
void DS1302_Write_Time() 
{  
	uint8_t i;	
	uint8_t temp1;	
	uint8_t temp2;		
	for(i=0;i<7;i++)			// 十进制转BCD码	
	{		
		temp1=(TimeBuff[i]/10)<<4;		
		temp2=TimeBuff[i]%10;		
		TimeBuff[i]=temp1+temp2;	
	}		
	Write_Ds1302_Byte(0x8E,0x00);					// 关闭写保护
	Write_Ds1302_Byte(0x80,0x80);					// 暂停时钟 	
	Write_Ds1302_Byte(0x8C,TimeBuff[0]);			// 年 	
	Write_Ds1302_Byte(0x88,TimeBuff[1]);			// 月 	
	Write_Ds1302_Byte(0x86,TimeBuff[2]);			// 日 	
	Write_Ds1302_Byte(0x8A,TimeBuff[3]);			// 星期	
	Write_Ds1302_Byte(0x84,TimeBuff[4]);			// 时 	
	Write_Ds1302_Byte(0x82,TimeBuff[5]);			// 分	
	Write_Ds1302_Byte(0x80,TimeBuff[6]);			// 秒	
	Write_Ds1302_Byte(0x80,TimeBuff[6]&0x7F);		// 运行时钟	
	Write_Ds1302_Byte(0x8E,0x80);					// 打开写保护  
} 
/*********************************************************/
// 从DS1302读出时间数据
/*********************************************************/
void DS1302_Read_Time()  
{ 	
	uint8_t i; 	
//	TimeBuff[0]=Read_Ds1302_Byte(0x8D);			// 年 	
//	TimeBuff[1]=Read_Ds1302_Byte(0x89);			// 月 	
//	TimeBuff[2]=Read_Ds1302_Byte(0x87);			// 日 	
//	TimeBuff[3]=Read_Ds1302_Byte(0x8B);			// 星期	
	TimeBuff[4]=Read_Ds1302_Byte(0x85);			// 时 	
	TimeBuff[5]=Read_Ds1302_Byte(0x83);			// 分 	
	TimeBuff[6]=(Read_Ds1302_Byte(0x81))&0x7F;		// 秒  	
	for(i=4;i<7;i++)		// BCD转十进制	
	{           		
		TimeBuff[i]=(TimeBuff[i]/16)*10+TimeBuff[i]%16;	
	}
}
