#ifndef _SU_S12_H
#define _SU_S12_H

#include "su_common_typedef.h"//数据类型定义

extern uint8_t key_value;
extern int cnt1,cnt2,cnt3;//读取传感器的计数器，读取按键的计数器，数码管显示的计数器
extern uint8_t digitaltube_show[8];//用于存放数码管显示的数字用于修改数码管显示的值

void DeviceInit(void);//所有相关设备初始化
void DisplayTime(void);//在数码管中显示题目要求的时间
void DisplayTemperature(void);//温度显示界面
void DisplaySetParameter(void);//参数设置的显示界面
void S13Function(void);

#endif
