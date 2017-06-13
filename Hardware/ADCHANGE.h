#ifndef ADCHANGE_H_
#define ADCHANGE_H_

#define AD_DATAPORT P2//����ADоƬ�����������ΪP2

sbit ADC_A=P1^5;//ADоƬ��̬��ַλѡ�񣬾���ʹ�ð�ͨ�����ݲɼ����е�ͨ�����
sbit ADC_B=P1^6;
sbit ADC_C=P1^7;


sbit ADC_START=P3^4;//оƬ�����˿ڶ���
sbit ADC_EOC=P3^5;
sbit ADC_OE=P3^6;
sbit ADC_CLOCK=P3^7;

//uint MAD_TIMER=0;

/*********************************
���ƣ�AD��ʼ��
���ã�ADת���˿��Լ���ʱ����ʼ��
*********************************/
void FAD_INITIAL()
{
	EA=1;
	TMOD=0x21;//���ö�ʱ���Լ��жϵĹ�����ʽ�����ж�ʱ��1�Ĺ�����ʽΪ8λ�Զ�װ��ֵ����ʱ��0�Ĺ�����ʽΪ16��ʱ

	ET0=0;
	TR0=1;
	TH0=255;//(65535-20)/256;
	TL0=236;//(65535-20)%256����20US����һ��,��Ƶ��Ϊ50KHZ

	ET1=0;
	TR1=1;
	TH1=0XFD;
	TL1=0XFA;//���ö�ʱ��1�ĳ�ֵ��������Ҫ����ͨ�ŵĲ�����Ϊ9600

	ADC_CLOCK=0;//ADоƬ�������˿ڳ�ʼ��
	ADC_A=0;
	ADC_B=0;
	ADC_C=0;
	ADC_OE=0;
	ADC_START=0;

}

/*********************************
���ƣ�ADʱ�Ӵ���
���ã��жϷ�����򣬶�ADC0808��ʱ�Ӷ˿�����50khz�����壬ʹоƬ��������
*********************************/
void FAD_CLOCK()interrupt 1//
{
	TH0=255;
	TL0=236;
	ADC_CLOCK=!ADC_CLOCK;//�������
}

/*void FAD_TIMER()interrupt 3
{
	TH1=0XFD;
	TL1=0XFA;
	MAD_TIMER=1;
}*/
/*********************************
���ƣ�ADת��������
���ã�ģ��ת��������������ֵ����
*********************************/
uint FAD_CHANGE()//
{
	uint MDATA=0;
	ET0=1;
	ADC_START=0;
	ADC_OE=0;

	ADC_START=1;
	ADC_START=0;	
	while(!ADC_EOC);
	ADC_OE=1;
	MDATA=AD_DATAPORT;
	ADC_OE=0;
	ET0=0;
	return MDATA;
}
#endif
