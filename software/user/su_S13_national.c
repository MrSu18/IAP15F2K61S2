/*第十三届国赛题的main.c*/
#include "su_S13_national.h"
#include "su_ne555.h"
#include "su_digital_tube.h"

void FrequencyUI(void);//频率显示界面

void main(void)
{
    //NE555初始化
    Ne555CountInit();
    Ne555TimInit();
    while (1)
    {
        ;
    }
    
}

void FrequencyUI(void)//频率显示界面
{
    digitaltube_show[0]=0x71;
    digitaltube_show[1]=0x00;
}
