#include <stc15f2k60s2.h>
#include "su_key.h"

//��������ɨ�躯��
//ʹ�õ�ʱ���ж�������(ReadKey()!=0xff),�ȴ������ͷ�Ҳ�����
uint8_t ReadKey(void)
{
    uint8_t temp;
    uint8_t key_value = 0xff;
    
    temp = P3&0x0f;//�Ѹ���λ����
    switch(temp)
    {
        case 0x0e:
			key_value = 1;  //S7
            break;    
        case 0x0d:
			key_value = 2;  //S6
            break;    
        case 0x0b:
			key_value = 3;  //S5
            break;    
        case 0x07:
			key_value = 4;  //S4
            break;    
    }
    return key_value;
}

/****************************************�����������Գ���***************************************
void main(void)
{
	uint8_t temp;
    ENABLE_LED_LATCH;
	while (1)
    {
		temp=ReadKey();
		if(temp!=0xff)
		{
			Delay10ms();
			temp=ReadKey();
			if(temp!=0xff)
			{
				switch(temp)
				{
					case 1: LED1=!LED1;break;
					case 2: LED2=!LED2;break;
					case 3: LED3=!LED3;break;
					case 4: LED4=!LED4;break;
					default: LED5=!LED5;break;
				}
				while(ReadKey()!=0xff);
			}
		}
    }
}
************************************************************************************************/

//��ȡ�������
uint8_t	ReadKeyBoard(void)
{
	uint8_t key_value = 0xff;
	P30=P31=P32=P33=P34=P35=P42=P44=1;
	P30=0;
	if(P34==0)
	{
		key_value=1;
	}
	else if(P35==0)
	{
		key_value=2;
	}
	else if(P42==0)
	{
		key_value=3;
	}
	else if(P44==0)
	{
		key_value=4;
	}
	
	return key_value;
}

/****************************************���󰴼����Գ���***************************************
void main(void)
{
	uint8_t temp;
    ENABLE_LED_LATCH;
	while (1)
    {
		temp=ReadKeyBoard();
		if(temp!=0xff)
		{
			Delay10ms();
			temp=ReadKeyBoard();
			if(temp!=0xff)
			{
				switch(temp)
				{
					case 1: LED1=!LED1;break;
					case 2: LED2=!LED2;break;
					case 3: LED3=!LED3;break;
					case 4: LED4=!LED4;break;
					default: LED5=!LED5;break;
				}
				while(ReadKeyBoard()!=0xff);
			}
		}
		else
		{
			LED6=!LED6;
			Delay500ms();
		}
    }
}
************************************************************************************************/
