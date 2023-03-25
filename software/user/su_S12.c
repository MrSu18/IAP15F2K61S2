#include "su_S12.h"
#include "su_ds18b20.h"//温度传感器
#include "su_ds1302.h"//实时时钟模块
#include "su_digital_tube.h"//数码管显示
#include "delay.h"


void DeviceInit(void)
{
    //时钟模块初始化
    TimeBuff[4]=23;TimeBuff[5]=25;
	DS1302_Write_Time();//写一次避免时钟模块里面足以开始不对
	//温度传感器初始化
	//单总线读取，不需要初始化
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
    float temperature=0;//温度
	int intege=0;//整数小数
    temperature=Read_DS18B20_temp();
	intege=(int)(temperature*10);
	
    DigitalTubeDisplay(1,25);//U
    DigitalTubeDisplay(2,1);
    DigitalTubeDisplay(3,16);//熄灭
    DigitalTubeDisplay(4,16);
    DigitalTubeDisplay(5,16);
    DigitalTubeDisplay(6,intege/100);
    DigitalTubeDisplay(7,intege/10%10+30);
    DigitalTubeDisplay(8,intege%10);
	
	DigitalTubeDisplay(4,16);//多给一位没用的一位显示，避免最后一位很亮
}

void DisplaySetParameter(void)//参数设置的显示界面
{
	unsigned char temperature=0;//温度
    temperature=rd_temperature();
	
	DigitalTubeDisplay(1,25);//U
	DigitalTubeDisplay(2,3);//U
	DigitalTubeDisplay(3,16);//熄灭
    DigitalTubeDisplay(4,16);
    DigitalTubeDisplay(5,16);
	DigitalTubeDisplay(6,16);
	DigitalTubeDisplay(7,temperature/10);
    DigitalTubeDisplay(8,temperature%10);
	
	DigitalTubeDisplay(4,16);//多给一位没用的一位显示，避免最后一位很亮
}
