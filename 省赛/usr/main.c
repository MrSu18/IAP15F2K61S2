#include <stc15f2k60s2.h>
#include <string.h>
#include "su_usart.h"
#include "su_common_typedef.h"
#include "su_ne555.h"
#include "su_digital_tube.h"
#include "su_ds1302.h"
#include "su_key.h"
#include "su_ds18b20.h"
#include "su_led.h"
#include "su_latch.h"
#include "su_pcf8591.h"

void DisplayTime(void);//�޸Ĺ���ʱ����������ܱ���
void DisplayHuiXian(void);//���Խ���
void DisplaySetParam(void);//���ò�������
void DisplayWenShiDu(void);//��ʪ�Ƚ���
void LEDChange(void);//LED�任����

uint8_t display_page=0,display_page_old=0;//�������ʾ�Ľ���S4����
uint8_t huixian_mode=0;//���Ե���ģʽ
uint8_t key_cnt=0;//��ʱ����������
uint16_t adc_cnt=0,display_page_cnt=0,data_cnt=0;
uint8_t key_now=0,key_old=0,key_down=0;//����
uint16_t temp_max=0,chufa_temp=0,temp_old=0,chufa_temp_old=0;//�¶�
uint8_t temp_param=30;//�¶Ȳ���
LED_t led;
uint8_t adc_result=0,last_adc_result=0;
uint16_t shidu=0,shidu_max=0,chufa_shidu=0,shidu_old=0,chufa_shidu_old=0;//ʪ��
uint8_t light_flag=0;//1��ʱ�����Ҫ��ʱ3S��
uint8_t chufa_num=0;//��������
uint8_t chufa_time_shi=0,chufa_time_fen=0;
uint8_t led_warm_flag=0;//�¶ȱ�����־����

void main (void)
{
	Select_Latch(5);//�رշ������ͼ̵���
	P04=0;P06=0;
	memset(&led,0xff,1);//��ʼ��ledΪ��
	DS1302_Write_Time();//DS1302��ʼ��
	while(temperature>800)//DS18B20��ʼ��
	{
		Read_DS18B20_temp();
	}
	Pcf8591_Adc_Init(0x01);//��AIN1��AD�ɼ�
	Ne555TimInit();//NE555�Ķ�ʱ��
	DS1302_Read_Time();
	LEDChange();
	Ne555CountInit();
	EA=1;//�������ж�
	
	while(1)
	{
#if	1
		if(data_cnt>=400)//0.5S��һ��
		{
			DS1302_Read_Time();
			Read_DS18B20_temp();
			temperature=(temperature+temp_old)/2;
			temp_old=temperature;
			if(frequency!=0)
			{
				shidu=(int)(0.04445*frequency+1.11)*10;
				shidu=(shidu+shidu_old)/2;
				shidu_old=shidu;
			}
			data_cnt=0;
			if(shidu_max<shidu) shidu_max=shidu;
			if(temperature>temp_max) temp_max=temperature;
		}
		if(light_flag==0)
		{
			if(adc_cnt>=300)//0.4S��һ��
			{
				adc_result=AdcRead();//��ס�ǽӽ�0���ſ��Ǵ���180
				
				if(last_adc_result>(adc_result+50))
				{
					chufa_num++;
					DS1302_Read_Time();
					chufa_time_shi=TimeBuff[4];chufa_time_fen=TimeBuff[5];
					Read_DS18B20_temp();
					chufa_temp=temperature;
					chufa_shidu=shidu;
					display_page_old=display_page;//����֮ǰ������
					display_page=3;
					if(chufa_num>=2)
					{
						if(chufa_temp_old<chufa_temp && chufa_shidu_old<chufa_shidu)
						{
							led.led6=0;
						}
						else
						{
							led.led6=1;
						}
						Select_Latch(4);
						P0=*(uint8_t*)&led;
					}
					chufa_temp_old=chufa_temp;chufa_shidu_old=chufa_shidu;//������һ���ڴ�����ʪ��
					light_flag=1;
				}
				last_adc_result=adc_result;
				adc_cnt=0;
			}
			//����
			if(key_cnt>=100)
			{
				//��ȡ����
				key_now=ReadKeyBoard();
				key_down=key_now&(key_now^key_old);
				key_old=key_now;
				//��Ӧ����
				switch(key_down)
				{
					case 4:
						display_page=(display_page+1)%3;
						LEDChange();
						break;
					case 5:
						if(display_page==1)//�����Խ���ʱ
						{
							huixian_mode=(huixian_mode+1)%3;
						}
						break;
					case 8:
						if(display_page==2 && temp_param<99)//���������ý���ʱ
						{
							temp_param++;
						}
						break;
					case 9:
						if(display_page==2 && temp_param>0)//���������ý���ʱ
						{
							temp_param--;
						}
						break;
					default:break;
				}
				key_cnt=0;
			}
			//�ɼ��¶ȴ����¶Ȳ���ʱ
			if(temperature>temp_param*10)
			{
				led_warm_flag=1;
			}
		}
		else
		{
			if(display_page_cnt>=3000)//3S����
			{
				light_flag=0;
				display_page=display_page_old;
				display_page_cnt=0;
			}
		}
		//��ʾ����
		switch(display_page)
		{
			case 0:
				DisplayTime();
				break;
			case 1:
				DisplayHuiXian();
				break;
			case 2:
				DisplaySetParam();
				break;
			case 3:
				DisplayWenShiDu();break;
			default:break;
		}
#endif
	}
}

void DisplayTime(void)//�޸Ĺ���ʱ����������ܱ���
{
	//�̶���ʾ
	digitaltube_show[2]=digitaltube_show[5]=t_display[17];//'-'
	//ʱ
	digitaltube_show[0]=t_display[TimeBuff[4]/10];digitaltube_show[1]=t_display[TimeBuff[4]%10];
	//��
	digitaltube_show[3]=t_display[TimeBuff[5]/10];digitaltube_show[4]=t_display[TimeBuff[5]%10];
	//��
	digitaltube_show[6]=t_display[TimeBuff[6]/10];digitaltube_show[7]=t_display[TimeBuff[6]%10];
}

void DisplayHuiXian(void)//���Խ���
{
	switch(huixian_mode)
	{
		case 0://�¶Ȼ���
			digitaltube_show[0]=0x39;//'C'
			digitaltube_show[1]=0x00;//'black'
			if(chufa_num==0)
			{
				digitaltube_show[2]=digitaltube_show[3]=digitaltube_show[4]=digitaltube_show[5]=digitaltube_show[6]=digitaltube_show[7]=0x00;//'black'
			}
			else
			{
				digitaltube_show[2]=t_display[temp_max/100];
				digitaltube_show[3]=t_display[temp_max/10%10];
				digitaltube_show[4]=0x40;//'-'
				digitaltube_show[5]=t_display[temperature/100];
				digitaltube_show[6]=t_display[temperature/10%10+32];
				digitaltube_show[7]=t_display[temperature%10];
			}
			break;
		case 1://ʪ�Ȼ���
			digitaltube_show[0]=0x76;//'H'
			digitaltube_show[1]=0x00;//'black'
			if(chufa_num==0)
			{
				digitaltube_show[2]=digitaltube_show[3]=digitaltube_show[4]=digitaltube_show[5]=digitaltube_show[6]=digitaltube_show[7]=0x00;//'black'
			}	
			else
			{
				digitaltube_show[2]=t_display[shidu_max/100];
				digitaltube_show[3]=t_display[shidu_max/10%10];
				digitaltube_show[4]=0x40;//'-'
				digitaltube_show[5]=t_display[shidu/100];
				digitaltube_show[6]=t_display[shidu/10%10+32];
				digitaltube_show[7]=t_display[shidu%10];
			}
			break;
		case 2:
			digitaltube_show[0]=0x71;//'F'
			digitaltube_show[1]=t_display[chufa_num/10];
			digitaltube_show[2]=t_display[chufa_num%10];
			if(chufa_num==0)
			{
				digitaltube_show[3]=digitaltube_show[4]=digitaltube_show[5]=digitaltube_show[6]=digitaltube_show[7]=0x00;//'black'
			}
			else
			{
				digitaltube_show[3]=t_display[chufa_time_shi/10];
				digitaltube_show[4]=t_display[chufa_time_shi%10];
				digitaltube_show[5]=0x40;//'-'
				digitaltube_show[6]=t_display[chufa_time_fen/10];
				digitaltube_show[7]=t_display[chufa_time_fen%10];
			}
			break;
		default:break;
	}
}

void DisplaySetParam(void)//���ò�������
{
	digitaltube_show[0]=0x73;//'P'
	digitaltube_show[1]=digitaltube_show[2]=digitaltube_show[3]=digitaltube_show[4]=digitaltube_show[5]=0x00;//'black'
	digitaltube_show[6]=t_display[temp_param/10];
	digitaltube_show[7]=t_display[temp_param%10];
}

void DisplayWenShiDu(void)//��ʪ�Ƚ���
{
	digitaltube_show[0]=0x79;//'E'
	digitaltube_show[1]=0x00;//'black'
	digitaltube_show[2]=0x00;//'black'
	digitaltube_show[3]=t_display[chufa_temp/100];
	digitaltube_show[4]=t_display[chufa_temp/10%10];
	digitaltube_show[5]=0x40;//'-'
	if(frequency==0)
	{
		digitaltube_show[6]=0x77;
		digitaltube_show[7]=0x77;
	}
	else
	{
		digitaltube_show[6]=t_display[chufa_shidu/100];
		digitaltube_show[7]=t_display[chufa_shidu/10%10];
	}
}

void LEDChange(void)//LED�任����
{
	switch(display_page)
	{
		case 0:
			led.led1=0;led.led2=1;led.led3=1;
			Select_Latch(4);
			P0=*(uint8_t*)&led;
			break;
		case 1:
			led.led1=1;led.led2=0;led.led3=1;
			Select_Latch(4);
			P0=*(uint8_t*)&led;
			break;
		case 2:
			led.led1=1;led.led2=1;led.led3=0;
			Select_Latch(4);
			P0=*(uint8_t*)&led;
			break;
		default:break;
	}
}
