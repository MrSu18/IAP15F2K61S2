#include "su_latch.h"
#include <stc15f2k60s2.h>

void Select_Latch(int num)//ѡ��ʹ�ܼ���������
{
	switch(num)
	{
		case 4:P2=(P2&0x1F)|0x80;break;		//LED������
		case 5:P2=(P2&0x1F)|0xA0;break;		//
		case 6:P2=(P2&0x1F)|0xC0;break;		//�����λѡ������
		case 7:P2=(P2&0x1F)|0xE0;break;		//����ܶ�ѡ������
		default:break;
	}
}
