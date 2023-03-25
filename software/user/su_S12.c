#include "su_S12.h"
#include "su_ds18b20.h"//�¶ȴ�����
#include "su_ds1302.h"//ʵʱʱ��ģ��
#include "su_digital_tube.h"//�������ʾ


void DeviceInit(void)
{
    //ʱ��ģ���ʼ��
    TimeBuff[4]=23;TimeBuff[5]=25;
	DS1302_Write_Time();//дһ�α���ʱ��ģ���������Կ�ʼ����
	//�¶ȴ�������ʼ��
	//�����߶�ȡ������Ҫ��ʼ��
}

void DisplayTime(void)//ʱ����ʾ����
{
    DS1302_Read_Time();
    DigitalTubeDisplay(1,25);
    DigitalTubeDisplay(2,2);
    DigitalTubeDisplay(3,16);
    DigitalTubeDisplay(4,TimeBuff[4]/10);
    DigitalTubeDisplay(5,TimeBuff[4]%10);
    DigitalTubeDisplay(6,17);
    DigitalTubeDisplay(7,TimeBuff[5]/10);
    DigitalTubeDisplay(8,TimeBuff[5]%10);
}

void DisplayTemperature(void)//�¶���ʾ����
{
    float temperature=0;//�¶�
    temperature=Read_DS18B20_temp();
    DigitalTubeDisplay(1,25);//U
    DigitalTubeDisplay(2,1);
    DigitalTubeDisplay(3,16);//Ϩ��
    DigitalTubeDisplay(4,16);
    DigitalTubeDisplay(5,16);
//    DigitalTubeDisplay(6,temperature/10);
//    DigitalTubeDisplay(7,temperature%10+30);
    //DigitalTubeDisplay(8,temperature/100);
}
