#ifndef _MAIN_H
#define	_MAIN_H

#include "su_common_typedef.h"

extern char distance_danwei,distance_canshu,temp_canshu;
extern uint8_t ui_page,canshu_page,gongchang_page;
//����ģʽ�µĲ���
extern int jiaozhunzhi;
extern uint16_t u_speed;//�������ڽ����е��ٶ�m/s
extern uint8_t dac_xiaxian;//DA����,����һλС�������������2�����޷�0.2����˼
extern uint8_t gongchang_led_flag;
//�����ı���
extern uint8_t key_now,key_down,key_old;

extern uint8_t xdata distance_lianxu[60];//�����ĳ���������
extern uint8_t distane_lianxu_cnt;


#endif
