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
	FAD_INITIAL();//调用AD初始化
	FSEND_INITIAL();//调用数据发送初始化
	while(1)
	{
		MAD_DATA=FAD_CHANGE();//获取数据

		LCD_DATA_BAI=MAD_DATA/100;//将数据分解为百十个位
		LCD_DATA_SHI=MAD_DATA%100/10;
		LCD_DATA_GE=MAD_DATA%10;

		FSEND_DATA(LCD_DATA_BAI,LCD_DATA_SHI,LCD_DATA_GE);//发送数据给PC
		//FLCD_DISPLAY();
		FTIME_1MS(2);
	}
}
