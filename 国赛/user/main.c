#include <STC15F2K60S2.H>
#include "main.h"
#include "su_usart.h"
#include "su_key.h"
#include "timer.h"
#include "su_ds18b20.h"
#include "su_digital_tube.h"
#include "su_ultrasonic.h"
#include "su_led.h"
#include <string.h>
#include "su_latch.h"
#include "delay.h"
#include "su_pcf8591.h"

uint8_t data test=0;
char distance_danwei=0,distance_canshu=40,temp_canshu=30;
uint8_t ui_page=0,canshu_page=0,gongchang_page=0;
//工厂模式下的参数
int jiaozhunzhi=0;
uint16_t u_speed=340;//超声波在介质中的速度m/s
uint8_t dac_xiaxian=10;//DA下限,保留一位小数，所以这里的2就是限幅0.2的意思
uint8_t gongchang_led_flag=0;
//按键的变量
uint8_t key_now=0,key_down=0,key_old=0;
uint8_t xdata distance_lianxu[60]={0};//连续的超声波数据
uint8_t distane_lianxu_cnt=0;

void CeJuUI();//测距界面
void CanShuUI();//参数界面
void GongChangUI();//工厂模式下的UI
int Limit(int x,int low,int up);//限幅

void main(void)
{
	uint8_t dac=0;
	float k=0,b=0,y=0;
	Select_Latch(5);
	P06=0;//蜂鸣器关
	P04=0;//继电器关
	Select_Latch(5);
	Delay10ms();
	//LED初始化
	memset(&led_object,0xff,sizeof(LED_t));
	LEDResponse(led_object);
	//定时器初始化
	Timer2Init();
	//串口初始化
	UartInit();
	//温度初始化
	while(temperature>=800)//温度传感器最开始读值是83.5
	{
		Read_DS18B20_temp();
	}
	Delay10ms();
	//开启全局中断
	EA=1;
	k=(float)((5-(float)(dac_xiaxian/10))/80);
	b=(float)(5-((5-(float)(dac_xiaxian/10))*1.125));
	while(1)
	{	
		test=1;
#if 1
		//DAC输出
		if(dac_flag==1)
		{
			y=k*distance_lianxu[distane_lianxu_cnt]+b;
			dac=y*256/5;
			PCF8591_Dac(dac);
//			printf("%bu\r\n",distance_lianxu[distane_lianxu_cnt]);
			distane_lianxu_cnt++;
			if(distane_lianxu_cnt==60)
			{
				shuchu_flag=0;
				distane_lianxu_cnt=0;
			}
			dac_flag=0;
		}
		if(sensor_flag==1)
		{
			Read_DS18B20_temp();
			distance=UltrasonicMeasure();
			distance+=jiaozhunzhi;
			distance=Limit(distance,0,255);
			//LED
			if(ui_page==0)
			{
				memset(&led_object,~distance,sizeof(LED_t));
			}
			if(-5<=distance && distance<=distance_canshu+5 && temperature<temp_canshu*10)
			{
				P06=0;//蜂鸣器关
				P04=1;//继电器关
				Select_Latch(5);
			}
			else
			{
				P06=0;//蜂鸣器关
				P04=0;//继电器关
				Select_Latch(5);
			}
			sensor_flag=0;
		}
		//按键读取
		if(key_flag==1)
		{
			key_now=ReadKeyBoard();
			key_down=key_now&(key_now^key_old);
			key_old=key_now;
			key_flag=0;
			if(jilu_flag==0)//记录的时候按键无效
			{
				switch(key_down)
				{
					case 4:
						ui_page=(ui_page+1)%3;
						//灯的表现形式
						if(ui_page==1)
						{
							memset(&led_object,0xff,sizeof(LED_t));
							led_object.led8=0;
						}
						else if(ui_page==2)
						{
							memset(&led_object,0xff,sizeof(LED_t));
							gongchang_led_flag=1;
						}
						break;
					case 5:
						switch(ui_page)
						{
							case 0:distance_danwei=!distance_danwei;break;
							case 1:canshu_page=!canshu_page;break;
							case 2:gongchang_page=(gongchang_page+1)%3;break;
							default:break;
						}
						break;
					case 8:
						switch(ui_page)
						{
							case 0:
								key_now=ReadKeyBoard();
								if(key_now!=10)
								{
									distane_lianxu_cnt=0;//DAC输出的时候就查询这个，如果这样是60说明前面有数据
									jilu_flag=1;
								}
								break;
							case 1:
								if(canshu_page==0)//在距离参数界面下
								{
									distance_canshu+=10;
									distance_canshu=Limit(distance_canshu,10,90);
								}
								else//在温度参数界面下
								{
									temp_canshu+=1;
									temp_canshu=Limit(temp_canshu,0,80);
								}
								break;
							case 2:
								if(gongchang_page==0)
								{
									jiaozhunzhi+=5;
									jiaozhunzhi=Limit(jiaozhunzhi,-90,90);
								}
								else if(gongchang_page==1)
								{
									u_speed+=10;
									u_speed=Limit(u_speed,10,9990);
								}
								else if(gongchang_page==2)
								{
									dac_xiaxian+=1;
									k=(5-dac_xiaxian)/80;
									b=5-(5-dac_xiaxian)*1.125;
									dac_xiaxian=Limit(dac_xiaxian,1,20);
								}
								break;
							default:break;
						}
						break;
					case 9:
						switch(ui_page)
						{
							case 0:
								distane_lianxu_cnt=0;//DAC输出的时候就查询这个，如果这样是60说明前面有数据
								shuchu_flag=1;
								break;
							case 1:
								if(canshu_page==0)//在距离参数界面下
								{
									distance_canshu-=10;
									distance_canshu=Limit(distance_canshu,10,90);
								}
								else//在温度参数界面下
								{
									temp_canshu-=1;
									temp_canshu=Limit(temp_canshu,0,80);
								}
								break;
							case 2:
								if(gongchang_page==0)
								{
									jiaozhunzhi-=5;
									jiaozhunzhi=Limit(jiaozhunzhi,-90,90);
								}
								else if(gongchang_page==1)
								{
									u_speed-=10;
									u_speed=Limit(u_speed,10,9990);
								}
								else if(gongchang_page==2)
								{
									dac_xiaxian-=1;
									dac_xiaxian=Limit(dac_xiaxian,1,20);
								}
								break;
							default:break;
						}
						break;
					default:break;
				}
			}
		}
		//交互响应
		switch(ui_page)
		{
			case 0:
				CeJuUI();
				break;
			case 1:
				CanShuUI();
				break;
			case 2:
				GongChangUI();
				break;
			default:break;
		}
#endif
	}
}

void CeJuUI()//测距界面
{
	uint8_t disiwei=distance/1000%10,diwuwei=distance/100%10,diliuwei=distance/10%10,diqiwei=distance%10;
	//温度
	if(temperature>800)//温度大于80的时候不显示
	{
		digitaltube_show[0]=digitaltube_show[1]=digitaltube_show[2]=0x00;
	}
	digitaltube_show[0]=t_display[temperature/100%10];
	digitaltube_show[1]=float_display[temperature/10%10];
	digitaltube_show[2]=t_display[temperature%10];
	//分隔符
	digitaltube_show[3]=0x40;//'-'
	//距离
	if(disiwei==0 && distance<1000) disiwei=0x00;
	else	disiwei=t_display[disiwei];
	if(distance_danwei==0)//单位为cm的时候
	{
		if(diwuwei==0 && distance<100) diwuwei=0x00;
		else diwuwei=t_display[diwuwei];
		if(diliuwei==0 && distance<10) diliuwei=0x00;
		else diliuwei=t_display[diliuwei];
		if(diqiwei==0 && distance==0) diqiwei=0x00;
		else diqiwei=t_display[diqiwei];
	}
	else//单位为m的时候
	{
		if(diwuwei==0 && distance<100) diwuwei=0xBF;
		else diwuwei=float_display[diwuwei];
		if(diliuwei==0 && distance<10) diliuwei=0x3F;
		else diliuwei=t_display[diliuwei];
		if(diqiwei==0 && distance==0) diqiwei=0x3F;
		else diqiwei=t_display[diqiwei];
	}
	digitaltube_show[4]=disiwei;
	digitaltube_show[5]=diwuwei;
	digitaltube_show[6]=diliuwei;
	digitaltube_show[7]=diqiwei;
}

void CanShuUI()//参数界面
{
	digitaltube_show[0]=0x73;
	digitaltube_show[1]=t_display[canshu_page+1];
	digitaltube_show[2]=digitaltube_show[3]=digitaltube_show[4]=digitaltube_show[5]=0x00;
	if(canshu_page==0)
	{
		digitaltube_show[6]=t_display[distance_canshu/10%10];
		digitaltube_show[7]=t_display[distance_canshu%10];
	}
	else
	{
		digitaltube_show[6]=t_display[temp_canshu/10%10];
		digitaltube_show[7]=t_display[temp_canshu%10];
	}
}

void GongChangUI()//工厂模式下的UI
{
	digitaltube_show[0]=0x71;
	digitaltube_show[1]=t_display[gongchang_page+1];
	switch(gongchang_page)
	{
		case 0://校准值设置
			digitaltube_show[2]=digitaltube_show[3]=digitaltube_show[4]=0x00;
			if(jiaozhunzhi>=0)
			{
				if(jiaozhunzhi<10)
				{
					digitaltube_show[5]=0x00;
					digitaltube_show[6]=0x00;
					digitaltube_show[7]=t_display[jiaozhunzhi%10];
				}
				else if(jiaozhunzhi<100)
				{
					digitaltube_show[5]=0x00;
					digitaltube_show[6]=t_display[jiaozhunzhi/10%10];
					digitaltube_show[7]=t_display[jiaozhunzhi%10];
				}
				else
				{
					digitaltube_show[5]=t_display[jiaozhunzhi/100%10];
					digitaltube_show[6]=t_display[jiaozhunzhi/10%10];
					digitaltube_show[7]=t_display[jiaozhunzhi%10];
				}
			}
			else
			{
				if(jiaozhunzhi<=-10)
				{
					digitaltube_show[5]=0x40;
					digitaltube_show[6]=t_display[(-jiaozhunzhi)/10%10];
					digitaltube_show[7]=t_display[(-jiaozhunzhi)%10];
				}
				else
				{
					digitaltube_show[5]=0x00;
					digitaltube_show[6]=0x40;
					digitaltube_show[7]=t_display[(-jiaozhunzhi)%10];
				}
			}
			break;
		case 1:
			digitaltube_show[2]=digitaltube_show[3]=0x00;
			if(u_speed<10)
			{
				digitaltube_show[4]=0x00;
				digitaltube_show[5]=0x00;
				digitaltube_show[6]=0x00;
				digitaltube_show[7]=t_display[u_speed%10];
			}
			else if(u_speed<100)
			{
				digitaltube_show[4]=0x00;
				digitaltube_show[5]=0x00;
				digitaltube_show[6]=t_display[u_speed/10%10];
				digitaltube_show[7]=t_display[u_speed%10];
			}
			else if(u_speed<1000)
			{
				digitaltube_show[4]=0x00;
				digitaltube_show[5]=t_display[u_speed/100%10];
				digitaltube_show[6]=t_display[u_speed/10%10];
				digitaltube_show[7]=t_display[u_speed%10];
			}
			else 
			{
				digitaltube_show[4]=t_display[u_speed/1000%10];
				digitaltube_show[5]=t_display[u_speed/100%10];
				digitaltube_show[6]=t_display[u_speed/10%10];
				digitaltube_show[7]=t_display[u_speed%10];
			}
			break;
		case 2:
			digitaltube_show[2]=digitaltube_show[3]=digitaltube_show[4]=digitaltube_show[5]=0x00;
			digitaltube_show[6]=float_display[dac_xiaxian/10%10];
			digitaltube_show[7]=t_display[dac_xiaxian%10];
			break;
		default:break;
	}
}

int Limit(int x,int low,int up)//限幅
{
	if(x>up) x=up;
	else if(x<low) x=low;
	return x;
}
