#ifndef _MAIN_H_
#define _MAIN_H_

#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include "graphics.h" /*ϵͳ�ṩ��ͷ�ļ�*/
#include <time.h>




#define TIMER 0x1c /*����ʱ���жϵ��жϺ�*/

#define VK_LEFT  0x4b00/*���Ƽ�*/
#define VK_RIGHT 0x4d00/*���Ƽ�*/
#define VK_DOWN  0x5000 /*���ټ�*/
#define VK_UP    0x4800 /*���μ�*/
#define END   0x4f00 /*��ͣ��*/
#define ESC   0x011b
#define ENTER 0x1c0d

#define SIZE 20 /*����ı߳���20�����ص�*/
#define WIDTH 10 /*��Ϸ���Ŀ�ȣ��Է���Ŀ��Ϊ��λ*/
#define HEIGHT 20/*��Ϸ���ĸ߶ȣ��Է���Ŀ��Ϊ��λ*/

/*flag��ȡֵ*/
#define RESUME 30
#define EXIT 31
#define NEW_GAME 32
#define DO_NOTHING -1

#define FALSE 0
#define TRUE 1




		
/******************************************ȫ�ֱ���**************************************/
typedef struct
{
	int x, y;
}POINT;		
typedef struct
{
	POINT point[4];//�󷽿���ĸ��㣬����point[0]��ʾ����center
	int nColor;
	int shape;//��ʾ��BLOCK����״��shape��ȡֵΪ0,1,2,3,4,5,6
}BLOCK; /*����ĳһ��״��Ϣ�Ľṹ��*/

/*(��2�ദ������Ϊ�߽�)����ÿһ������ǰ��״̬,condition[x][y]���ǵ�ǰ����ɫ��ֵ*/
extern int condition[WIDTH + 2][HEIGHT + 2];
/*p->shape��Ӧ����ɫ����coloraddr[p->shape]*/
extern int coloraddr[7];
/* ��ʱ������ÿ��������18 */
extern unsigned int TimerCounter; 
extern int flag;   /*���ڿ�������*/ 
extern POINT array[7][4];
/*********************************************************************************
*array[shape][number]��ʾͼ�����������(center.x,center.y)��ƫ�Ƶ�ַ,
*����shape��ʾ��״����7����״����number��ʾ��4����
*��center.x+array[shape][i].x , center.y+array[shape][i].y)���ǵ�i���������
**********************************************************************************/
		




/******************************************����**************************************/
/*��Ϸ����*/
void start_game();//�������岿�֣����������Ҽ������벢����ִ����Щ������keyleft,keyright,keydown,turn,keyexit��)
				  //ͬʱҪ�ж��Ƿ�is_stop,is_fullline
				  //��Ҫ������һ���������ĳ���


/*���ƺ���*/
void keyleft(BLOCK *now);//����
void keyright(BLOCK *now);//����
void keydown(BLOCK *now);//����
void turn(BLOCK *now);//��ת
int keyexit();  //�����˳����� 
int is_stop(BLOCK *now);//���鵱ǰblcok�Ƿ��Ѿ��Ӵ����ף����Ƿ���TRUE�����򷵻�FALSE
int is_gameover(BLOCK *p);//�ж���Ϸ�Ƿ����������ֱ�������������
int is_fullline();//����Ƿ���һ���Ѿ�ǡ���������еĻ���������������,û�з���FALSE
void delete_line(int line_num);//��ȥ�Ѿ�������line_num�У�ͬʱ���·���
					  
/*��ʱ������*/					  
void SetTimer(void interrupt(*IntProc)(void));
void interrupt newtimer(void);
void DeleteTimer();


/*ͼ�κ���*/ 
void add_grade();//�ѻ������һ
void InitializeGraph();//��ʼ����Ϸ����
void print(BLOCK *p);//���ָ��p����Ĵ󷽿�
void print_next(BLOCK *next);//�����һ���������Ĵ󷽿鵽ָ��λ��
void draw_square(int x, int y, int color);//�ڵ㣨x��y����������ɫcolor
void clear(BLOCK *p);
void initialize_block(BLOCK *p);
void welcome();
void draw_condition();
int draw_gameover();

#endif
