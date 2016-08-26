#include "main.h"

/* ��ʱ������ÿ��������18 */
unsigned int TimerCounter = 0;
void interrupt(*oldtimer)(void);
//�Լ����õ�ʱ���жϴ����� 
void interrupt newtimer(void)
{
	(*oldtimer)();
	TimerCounter++;
}
//�����µ�ʱ���жϴ�����									
void SetTimer(void interrupt(*IntProc)(void))
{
	oldtimer = getvect(TIMER);
	disable();
	setvect(TIMER, IntProc);
	enable();
}

//�ָ�ԭ����ʱ���жϴ����� 
void DeleteTimer()
{
	disable();
	setvect(TIMER,oldtimer);
	enable();
}
