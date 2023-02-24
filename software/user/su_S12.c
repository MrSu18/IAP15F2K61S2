#include "su_S12.h"
#include "su_ds1302.h"
#include "su_digital_tube.h"
#include "su_ds18b20.h"

void DeviceInit(void)
{
    //时钟模块初始化
    TimeBuff[4]=23;TimeBuff[5]=25;
	DS1302_Write_Time();//写一次避免时钟模块里面足以开始不对
}

void DisplayTime(void)//时间显示界面
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

void DisplayTemperature(void)//温度显示界面
{
    uint8_t temperature=0;//温度
    temperature=rd_temperature();
    DigitalTubeDisplay(1,25);//U
    DigitalTubeDisplay(2,1);
    DigitalTubeDisplay(3,16);//熄灭
    DigitalTubeDisplay(4,16);
    DigitalTubeDisplay(5,16);
    DigitalTubeDisplay(6,temperature/10);
    DigitalTubeDisplay(7,temperature%10+30);
    //DigitalTubeDisplay(8,temperature/100);
}
