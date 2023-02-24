#include "su_S12.h"
#include "su_ds1302.h"
#include "su_digital_tube.h"

void DeviceInit(void)
{
    //ʱ��ģ���ʼ��
    TimeBuff[4]=23;TimeBuff[5]=25;
	DS1302_Write_Time();//дһ�α���ʱ��ģ���������Կ�ʼ����
}

void DisplayTime(void)
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
