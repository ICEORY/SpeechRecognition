#ifndef LCDSHOW_H_
#define LCDSHOW_H_


#define LCD_DATAPORT P0//��������ݶ˿�


sbit LCD_WEI_1=P1^0;//�����λ���壬�����ĸ��������
sbit LCD_WEI_2=P1^1;
sbit LCD_WEI_3=P1^2;
sbit LCD_WEI_4=P1^3;

uchar code MLCD_TABLE[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xBF,0xff};//�����8λLED�Ķ��壬ʹ��ʾ��Ӧ������


uint LCD_DATA_BAI=0,LCD_DATA_SHI=0,LCD_DATA_GE=0;//����ܰ�ʮ��������

/*********************************
���ƣ��������ʾ
���ã������������������ʾ����
*********************************/
void FLCD_DISPLAY()
{
	LCD_DATAPORT=0XFF;//�ڵ�һλ��ʾ��λ����
	LCD_WEI_1=0;
	LCD_WEI_2=1;
	LCD_WEI_3=1;
	LCD_WEI_4=1;
	LCD_DATAPORT=MLCD_TABLE[LCD_DATA_BAI];
	FTIME_10US(3);
	LCD_DATAPORT=0XFF;
	
	LCD_WEI_1=1;//�ڵڶ�λ��ʾʮλ����
	LCD_WEI_2=0;
	LCD_WEI_3=1;
	LCD_WEI_4=1;
	LCD_DATAPORT=MLCD_TABLE[LCD_DATA_SHI];
	FTIME_10US(2);
	LCD_DATAPORT=0XFF;


	LCD_WEI_1=1;//�ڵ���λ��ʾ��λ����
	LCD_WEI_2=1;
	LCD_WEI_3=0;
	LCD_WEI_4=1;
	LCD_DATAPORT=MLCD_TABLE[LCD_DATA_GE];
}
#endif
