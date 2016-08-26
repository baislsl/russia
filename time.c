#include "main.h"

/* 计时变量，每秒钟增加18 */
unsigned int TimerCounter = 0;
void interrupt(*oldtimer)(void);
//自己设置的时钟中断处理器 
void interrupt newtimer(void)
{
	(*oldtimer)();
	TimerCounter++;
}
//设置新的时钟中断处理函数									
void SetTimer(void interrupt(*IntProc)(void))
{
	oldtimer = getvect(TIMER);
	disable();
	setvect(TIMER, IntProc);
	enable();
}

//恢复原来的时钟中断处理器 
void DeleteTimer()
{
	disable();
	setvect(TIMER,oldtimer);
	enable();
}
