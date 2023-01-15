#include "delay.h"
#include <Intrins.h>//_nop_»úÆ÷ÖÜÆÚÑÓ³Ù

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
