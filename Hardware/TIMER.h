/*********************************
���ƣ���ʱ
���ã���ͣ��ͬʱ�䣬���ڻ���
*********************************/
#ifndef TIMER_H_
#define TIMER_H_

/*void FTIME_100US(uint t)
{
	uint i=0,j=0;
	for (i=0;i<t;i++)
		for(j=0;j<11;j++);
}
*/
void FTIME_1MS(uint t)
{
	uint i=0,j=0;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);
}

void FTIME_10US(uint t)
{
	uint i=0;
	for(i=0;i<t;i++);
}


#endif
