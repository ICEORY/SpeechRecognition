/*****************************
��������������ʼ��
���ܣ����ж��Լ���ʱ��������Ӧ��
	  �趨���Ա���д���ͨ��
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
������������ͨ��������
���ܣ�������λ�����͵����ݽ�����Ӧ���ж�
	  �Ӷ�������Ӧ�Ķ������緢���¶�����
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

