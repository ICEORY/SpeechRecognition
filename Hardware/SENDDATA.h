/*****************************
函数名：联机初始化
功能：对中断以及定时器进行相应的
	  设定，以便进行串口通信
******************************/
uchar code SEND_TABLE[10]="0123456789";
void FSEND_INITIAL()
{
	TMOD=0X21;
	SM0=0;
	SM1=1;
	TH1=0xfd;
	TL1=0xfa;
}

/****************************************
函数名：串口通信主程序
功能：根据上位机发送的数据进行相应的判断
	  从而做出相应的动作，如发送温度数据
*****************************************/
void FSEND_DATA(uint SEND_BAI,uint SEND_SHI,uint SEND_GE)
{
	TI=0;
	SBUF='A';
	while(!TI);


	TI=0;
	SBUF=SEND_TABLE[SEND_BAI];
	while(!TI);

	TI=0;
	SBUF=SEND_TABLE[SEND_SHI];
	while(!TI);

	TI=0;
	SBUF=SEND_TABLE[SEND_GE];
	while(!TI);
	TI=0;

}

