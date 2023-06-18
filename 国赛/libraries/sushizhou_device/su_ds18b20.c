#include "su_ds18b20.h"
#include "reg52.h"
#include "onewire.h"
#include "su_common_typedef.h"

int temperature=830;


void Read_DS18B20_temp()
{
	unsigned char LSB=0,MSB=0;
	int temp;
	
	init_ds18b20();
	Write_DS18B20(0xCC);
    Write_DS18B20(0x44); //�����¶�ת��
//	Delay_OneWire(200);
	
	init_ds18b20();
    Write_DS18B20(0xCC);
    Write_DS18B20(0xBE); //��ȡ�Ĵ���
	
	LSB=Read_DS18B20();	//���ֽ�
	MSB=Read_DS18B20();	//���ֽ�
	
	temp=MSB<<8|LSB;//�Ѹߵ��ֽں��������16λ����
	
	temperature=(int)(temp*0.0625*10);//����ʮ��Ϊ�˷�������,�������һλС��������10���������λ��100
}