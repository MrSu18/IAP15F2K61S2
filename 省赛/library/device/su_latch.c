#include "su_latch.h"
#include <stc15f2k60s2.h>


void Select_Latch(int num)//选择使能几号锁存器
{
	switch(num)
	{
		case 4:P2=(P2&0x1F)|0x80;break;		//LED锁存器
		case 5:P2=(P2&0x1F)|0xA0;break;		//蜂鸣器继电器锁存器
		case 6:P2=(P2&0x1F)|0xC0;break;		//数码管位选锁存器
		case 7:P2=(P2&0x1F)|0xE0;break;		//数码管段选锁存器
		default:break;
	}
}
