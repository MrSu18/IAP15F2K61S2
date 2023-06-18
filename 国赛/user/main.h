#ifndef _MAIN_H
#define	_MAIN_H

#include "su_common_typedef.h"

extern char distance_danwei,distance_canshu,temp_canshu;
extern uint8_t ui_page,canshu_page,gongchang_page;
//工厂模式下的参数
extern int jiaozhunzhi;
extern uint16_t u_speed;//超声波在介质中的速度m/s
extern uint8_t dac_xiaxian;//DA下限,保留一位小数，所以这里的2就是限幅0.2的意思
extern uint8_t gongchang_led_flag;
//按键的变量
extern uint8_t key_now,key_down,key_old;

extern uint8_t xdata distance_lianxu[60];//连续的超声波数据
extern uint8_t distane_lianxu_cnt;


#endif
