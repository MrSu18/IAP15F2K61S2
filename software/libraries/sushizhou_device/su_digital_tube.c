#include "su_digital_tube.h"
#include <reg52.h>
#include "su_common_typedef.h"
#include "delay.h"

//数码管位数端口
sbit com1=P0^0;
sbit com2=P0^1;
sbit com3=P0^2;
sbit com4=P0^3;
sbit com5=P0^4;
sbit com6=P0^5;
sbit com7=P0^6;
sbit com8=P0^7;

uint8_t code t_display[]={                       //标准字库
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black  -     H    J    K    L    N    o   P    U     t    G    Q    r   M    y
    0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e,
    0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46};    //0. 1. 2. 3. 4. 5. 6. 7. 8. 9. -1

uint8_t code T_COM[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; //位选

void DigitalTubeDisplay(uint8_t com,uint8_t num)//数码管显示
{
	ENABLE_DIGITALTUBE_WEIXUAN_LATCH;//Y6C有效，P0控制显示哪一位
	P0=T_COM[com-1];          //P0=0000 0001，选通第一位（最左边一位）
	ENABLE_DIGITALTUBE_DUANGXUAN_LATCH;//Y7C有效，P0控制显示哪一个数字
	P0=~t_display[num];	//给P0输入数字1的段码，让数码管显示1
	Delay2ms();	//演示两毫秒视觉停留
}
