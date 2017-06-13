#ifndef ADCHANGE_H_
#define ADCHANGE_H_

#define AD_DATAPORT P2//定义AD芯片的数据输出口为P2

sbit ADC_A=P1^5;//AD芯片三态地址位选择，决定使用八通道数据采集口中的通道标号
sbit ADC_B=P1^6;
sbit ADC_C=P1^7;


sbit ADC_START=P3^4;//芯片其他端口定义
sbit ADC_EOC=P3^5;
sbit ADC_OE=P3^6;
sbit ADC_CLOCK=P3^7;

//uint MAD_TIMER=0;

/*********************************
名称：AD初始化
作用：AD转换端口以及定时器初始化
*********************************/
void FAD_INITIAL()
{
	EA=1;
	TMOD=0x21;//设置定时器以及中断的工作方式，其中定时器1的工作方式为8位自动装初值，定时器0的工作方式为16定时

	ET0=0;
	TR0=1;
	TH0=255;//(65535-20)/256;
	TL0=236;//(65535-20)%256设置20US触发一次,即频率为50KHZ

	ET1=0;
	TR1=1;
	TH1=0XFD;
	TL1=0XFA;//设置定时器1的初值，这里主要决定通信的波特率为9600

	ADC_CLOCK=0;//AD芯片的其他端口初始化
	ADC_A=0;
	ADC_B=0;
	ADC_C=0;
	ADC_OE=0;
	ADC_START=0;

}

/*********************************
名称：AD时钟触发
作用：中断服务程序，对ADC0808的时钟端口输入50khz的脉冲，使芯片正常工作
*********************************/
void FAD_CLOCK()interrupt 1//
{
	TH0=255;
	TL0=236;
	ADC_CLOCK=!ADC_CLOCK;//输出脉冲
}

/*void FAD_TIMER()interrupt 3
{
	TH1=0XFD;
	TL1=0XFA;
	MAD_TIMER=1;
}*/
/*********************************
名称：AD转换主程序
作用：模数转换，将传感器的值返回
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
