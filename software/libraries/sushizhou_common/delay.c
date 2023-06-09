#include "delay.h"
#include <Intrins.h>//_nop_»úÆ÷ÖÜÆÚÑÓ³Ù

void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 23;
	j = 205;
	k = 120;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Delay100ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 144;
	k = 71;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Delay10ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 20;
	j = 113;
	do
	{
		while (--j);
	} while (--i);
}



void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delay2ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 4;
	j = 225;
	do
	{
		while (--j);
	} while (--i);
}


void Delay200ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 2;
	j = 134;
	k = 20;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay50ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 98;
	j = 67;
	do
	{
		while (--j);
	} while (--i);
}
