/*��ʮ����������main.c*/
#include "su_S13_national.h"
#include "su_ne555.h"
#include "su_digital_tube.h"

void FrequencyUI(void);//Ƶ����ʾ����

void main(void)
{
    //NE555��ʼ��
    Ne555CountInit();
    Ne555TimInit();
    while (1)
    {
        ;
    }
    
}

void FrequencyUI(void)//Ƶ����ʾ����
{
    digitaltube_show[0]=0x71;
    digitaltube_show[1]=0x00;
}
