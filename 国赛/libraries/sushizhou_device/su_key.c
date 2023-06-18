#include <stc15f2k60s2.h>
#include "su_key.h"

//��������ɨ�躯��
//ʹ�õ�ʱ���ж�������(ReadKey()!=0xff),�ȴ������ͷ�Ҳ�����
uint8_t ReadKey(void)
{
    uint8_t temp;
    uint8_t key_value = 0;
    
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


//��ȡ�������
//���Ҫ��ⰴ���ɿ�����ô�����key_valueӦ��Ĭ����255��Ȼ�����а���key_up=~key_down
uint8_t	ReadKeyBoard(void)
{
	uint8_t key_value = 0;
	P30=P31=P32=P33=P34=P35=P42=P44=1;
	//������
	P32=0;
	if(P42==0)
	{
		key_value=9;
		P32=1;
		//���S8
		P33=0;
		if(P42==0)//˵����һ���µ�
		{
			key_value=10;
		}
		P33=1;
		return key_value;
	}
	else if(P44==0)
	{
		key_value=5;
	}
	P32=1;
	//������
	P33=0;
	if(P42==0)
	{
		key_value=8;
		P33=1;
		//���S9
		P32=0;
		if(P42==0)//˵����һ���µ�
		{
			key_value=10;
		}
		P32=1;
		return key_value;
	}
	else if(P44==0)
	{
		key_value=4;
	}
	P33=1;
	
	return key_value;
}



