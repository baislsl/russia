#ifndef _MAIN_H_
#define _MAIN_H_

#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include "graphics.h" /*系统提供的头文件*/
#include <time.h>




#define TIMER 0x1c /*定义时钟中断的中断号*/

#define VK_LEFT  0x4b00/*左移键*/
#define VK_RIGHT 0x4d00/*右移键*/
#define VK_DOWN  0x5000 /*加速键*/
#define VK_UP    0x4800 /*变形键*/
#define END   0x4f00 /*暂停键*/
#define ESC   0x011b
#define ENTER 0x1c0d

#define SIZE 20 /*方块的边长是20个象素点*/
#define WIDTH 10 /*游戏面板的宽度，以方块的宽度为单位*/
#define HEIGHT 20/*游戏面板的高度，以方块的宽度为单位*/

/*flag的取值*/
#define RESUME 30
#define EXIT 31
#define NEW_GAME 32
#define DO_NOTHING -1

#define FALSE 0
#define TRUE 1




		
/******************************************全局变量**************************************/
typedef struct
{
	int x, y;
}POINT;		
typedef struct
{
	POINT point[4];//大方块的四个点，其中point[0]表示中心center
	int nColor;
	int shape;//表示该BLOCK的形状，shape的取值为0,1,2,3,4,5,6
}BLOCK; /*保存某一形状信息的结构体*/

/*(加2多处两行作为边界)储存每一个方格当前的状态,condition[x][y]就是当前的颜色的值*/
extern int condition[WIDTH + 2][HEIGHT + 2];
/*p->shape对应的颜色就是coloraddr[p->shape]*/
extern int coloraddr[7];
/* 计时变量，每秒钟增加18 */
extern unsigned int TimerCounter; 
extern int flag;   /*用于控制流程*/ 
extern POINT array[7][4];
/*********************************************************************************
*array[shape][number]表示图形相对于中心(center.x,center.y)的偏移地址,
*其中shape表示形状（共7种形状），number表示共4个点
*（center.x+array[shape][i].x , center.y+array[shape][i].y)就是第i个点的坐标
**********************************************************************************/
		




/******************************************函数**************************************/
/*游戏流程*/
void start_game();//程序主体部分，这里接受玩家键盘输入并决定执行哪些操作（keyleft,keyright,keydown,turn,keyexit等)
				  //同时要判断是否is_stop,is_fullline
				  //还要处理下一个随机方块的出现


/*控制函数*/
void keyleft(BLOCK *now);//向左
void keyright(BLOCK *now);//向右
void keydown(BLOCK *now);//向下
void turn(BLOCK *now);//翻转
int keyexit();  //进入退出界面 
int is_stop(BLOCK *now);//检验当前blcok是否已经接触到底，若是返回TRUE，否则返回FALSE
int is_gameover(BLOCK *p);//判断游戏是否结束，若是直接输出结束界面
int is_fullline();//检测是否有一行已经恰好填满，有的话返回填满的行数,没有返回FALSE
void delete_line(int line_num);//消去已经填满第line_num行，同时更新分数
					  
/*计时器函数*/					  
void SetTimer(void interrupt(*IntProc)(void));
void interrupt newtimer(void);
void DeleteTimer();


/*图形函数*/ 
void add_grade();//已获分数加一
void InitializeGraph();//初始化游戏界面
void print(BLOCK *p);//输出指针p代表的大方块
void print_next(BLOCK *next);//输出下一个将出来的大方块到指定位置
void draw_square(int x, int y, int color);//在点（x，y）出填上颜色color
void clear(BLOCK *p);
void initialize_block(BLOCK *p);
void welcome();
void draw_condition();
int draw_gameover();

#endif
