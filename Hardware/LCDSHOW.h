#ifndef LCDSHOW_H_
#define LCDSHOW_H_


#define LCD_DATAPORT P0//数码管数据端口


sbit LCD_WEI_1=P1^0;//数码管位定义，决定哪个数码管亮
sbit LCD_WEI_2=P1^1;
sbit LCD_WEI_3=P1^2;
sbit LCD_WEI_4=P1^3;

uchar code MLCD_TABLE[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xBF,0xff};//数码管8位LED的定义，使显示相应的数字


uint LCD_DATA_BAI=0,LCD_DATA_SHI=0,LCD_DATA_GE=0;//数码管百十个的数据

/*********************************
名称：数码管显示
作用；将数据在数码管上显示出来
*********************************/
void FLCD_DISPLAY()
{
	LCD_DATAPORT=0XFF;//在第一位显示百位数字
	LCD_WEI_1=0;
	LCD_WEI_2=1;
	LCD_WEI_3=1;
	LCD_WEI_4=1;
	LCD_DATAPORT=MLCD_TABLE[LCD_DATA_BAI];
	FTIME_10US(3);
	LCD_DATAPORT=0XFF;
	
	LCD_WEI_1=1;//在第二位显示十位数字
	LCD_WEI_2=0;
	LCD_WEI_3=1;
	LCD_WEI_4=1;
	LCD_DATAPORT=MLCD_TABLE[LCD_DATA_SHI];
	FTIME_10US(2);
	LCD_DATAPORT=0XFF;


	LCD_WEI_1=1;//在第三位显示个位数字
	LCD_WEI_2=1;
	LCD_WEI_3=0;
	LCD_WEI_4=1;
	LCD_DATAPORT=MLCD_TABLE[LCD_DATA_GE];
}
#endif
