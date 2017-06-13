#include <reg52.h>

#define uint unsigned int
#define uchar unsigned char
uint MAD_DATA=0;
#include "TIMER.h"
#include "ADCHANGE.h"
#include "LCDSHOW.h"
#include "SENDDATA.h"

void main()
{
	FAD_INITIAL();//����AD��ʼ��
	FSEND_INITIAL();//�������ݷ��ͳ�ʼ��
	while(1)
	{
		MAD_DATA=FAD_CHANGE();//��ȡ����

		LCD_DATA_BAI=MAD_DATA/100;//�����ݷֽ�Ϊ��ʮ��λ
		LCD_DATA_SHI=MAD_DATA%100/10;
		LCD_DATA_GE=MAD_DATA%10;

		FSEND_DATA(LCD_DATA_BAI,LCD_DATA_SHI,LCD_DATA_GE);//�������ݸ�PC
		//FLCD_DISPLAY();
		FTIME_1MS(2);
	}
}
