#include <stc15f2k60s2.h>

//LED锁存器
#define	ENABLE_LED_LATCH	P2 = (P2&0x1f)|0x80	//使能LED对应的锁存器设置为透传模式 P2 & (0001 1111) | (1000 0000)
//状态宏定义
#define	ON	0
#define	OFF	1
//LED开关宏定义
#define LED1(N)	P00=(N)?1:0
#define LED2(N)	P01=(N)?1:0
#define LED3(N)	P02=(N)?1:0
#define LED4(N)	P03=(N)?1:0
#define LED5(N)	P04=(N)?1:0
#define LED6(N)	P05=(N)?1:0
#define LED7(N)	P06=(N)?1:0
#define LED8(N)	P07=(N)?1:0
