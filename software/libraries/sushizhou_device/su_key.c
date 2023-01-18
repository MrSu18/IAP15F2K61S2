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

