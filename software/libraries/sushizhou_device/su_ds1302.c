#include <reg52.h>
#include <intrins.h>
#include "su_ds1302.h"

sbit SCK=P1^7;		
sbit SDA=P2^3;		
sbit RST=P1^3;   // DS1302��λ												

uint8_t TimeBuff[7]={17,9,1,6,18,30,40};				// ʱ������
// TimeBuff[0] ������ݣ���Χ00-99
// TimeBuff[1] �����·ݣ���Χ1-12
// TimeBuff[2] �������ڣ���Χ1-31
// TimeBuff[3] �������ڣ���Χ1-7
// TimeBuff[4] ����Сʱ����Χ00-23
// TimeBuff[5] ������ӣ���Χ00-59
// TimeBuff[6] �������ӣ���Χ00-59

void Write_Ds1302(unsigned  char temp)//�������� 
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

void Write_Ds1302_Byte( unsigned char address,unsigned char dat )//��������     
{
	RST=0;	_nop_();
	SCK=0;	_nop_();
	RST=1; 	_nop_();  
	Write_Ds1302(address);	
	Write_Ds1302(dat);		
	RST=0; 
}

unsigned char Read_Ds1302_Byte ( unsigned char address )//��������
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
// ��DS1302д��ʱ������
/*********************************************************/
void DS1302_Write_Time() 
{  
	uint8_t i;	
	uint8_t temp1;	
	uint8_t temp2;		
	for(i=0;i<7;i++)			// ʮ����תBCD��	
	{		
		temp1=(TimeBuff[i]/10)<<4;		
		temp2=TimeBuff[i]%10;		
		TimeBuff[i]=temp1+temp2;	
	}		
	Write_Ds1302_Byte(0x8E,0x00);					// �ر�д����
	Write_Ds1302_Byte(0x80,0x80);					// ��ͣʱ�� 	
	Write_Ds1302_Byte(0x8C,TimeBuff[0]);			// �� 	
	Write_Ds1302_Byte(0x88,TimeBuff[1]);			// �� 	
	Write_Ds1302_Byte(0x86,TimeBuff[2]);			// �� 	
	Write_Ds1302_Byte(0x8A,TimeBuff[3]);			// ����	
	Write_Ds1302_Byte(0x84,TimeBuff[4]);			// ʱ 	
	Write_Ds1302_Byte(0x82,TimeBuff[5]);			// ��	
	Write_Ds1302_Byte(0x80,TimeBuff[6]);			// ��	
	Write_Ds1302_Byte(0x80,TimeBuff[6]&0x7F);		// ����ʱ��	
	Write_Ds1302_Byte(0x8E,0x80);					// ��д����  
} 
/*********************************************************/
// ��DS1302����ʱ������
/*********************************************************/
void DS1302_Read_Time()  
{ 	
	uint8_t i; 	
	TimeBuff[0]=Read_Ds1302_Byte(0x8D);			// �� 	
	TimeBuff[1]=Read_Ds1302_Byte(0x89);			// �� 	
	TimeBuff[2]=Read_Ds1302_Byte(0x87);			// �� 	
	TimeBuff[3]=Read_Ds1302_Byte(0x8B);			// ����	
	TimeBuff[4]=Read_Ds1302_Byte(0x85);			// ʱ 	
	TimeBuff[5]=Read_Ds1302_Byte(0x83);			// �� 	
	TimeBuff[6]=(Read_Ds1302_Byte(0x81))&0x7F;		// ��  	
	for(i=0;i<7;i++)		// BCDתʮ����	
	{           		
		TimeBuff[i]=(TimeBuff[i]/16)*10+TimeBuff[i]%16;	
	}
}
