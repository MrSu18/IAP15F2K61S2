#ifndef _SU_S12_H
#define _SU_S12_H

#include "su_common_typedef.h"//�������Ͷ���

extern uint8_t key_value;
extern int cnt1,cnt2,cnt3;//��ȡ�������ļ���������ȡ�����ļ��������������ʾ�ļ�����
extern uint8_t digitaltube_show[8];//���ڴ���������ʾ�����������޸��������ʾ��ֵ

void DeviceInit(void);//��������豸��ʼ��
void DisplayTime(void);//�����������ʾ��ĿҪ���ʱ��
void DisplayTemperature(void);//�¶���ʾ����
void DisplaySetParameter(void);//�������õ���ʾ����
void S13Function(void);

#endif
