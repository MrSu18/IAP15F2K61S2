#include <stc15f2k60s2.h>

//LED������
#define	ENABLE_LED_LATCH	P2 = (P2&0x1f)|0x80	//ʹ��LED��Ӧ������������Ϊ͸��ģʽ P2 & (0001 1111) | (1000 0000)
//״̬�궨��
#define	ON	0
#define	OFF	1
//LED���غ궨��
#define LED1(N)	P00=(N)?1:0
#define LED2(N)	P01=(N)?1:0
#define LED3(N)	P02=(N)?1:0
#define LED4(N)	P03=(N)?1:0
#define LED5(N)	P04=(N)?1:0
#define LED6(N)	P05=(N)?1:0
#define LED7(N)	P06=(N)?1:0
#define LED8(N)	P07=(N)?1:0
