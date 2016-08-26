#include "main.h"

int is_conflict(BLOCK *now,BLOCK *temp) {
    /*now是指当前的方块，而temp是当前方块做一个移动后得到的方块，只有temp的某一个点与现有的重叠并且与now不重叠时才会返回TRUE*/
	int i, j;
	for (i = 0; i < 4; i++) {
		if (temp->point[i].x<=0 || temp->point[i].x>=WIDTH + 1 || temp->point[i].y>=HEIGHT + 1) {//如果数组越界 
			return TRUE;
		}
		else if (condition[temp->point[i].x][temp->point[i].y] != BLACK) { 
			for (j = 0; j < 4; j++)
			{
				if (now->point[j].x == temp->point[i].x&&now->point[j].y == temp->point[i].y) break;
			}
			if (j == 4) return TRUE;
		}
	}
	return FALSE;
}

//如果BLOCK整体下移一格后满足is_conflict，则返回非零 
int is_stop(BLOCK *now) {
	BLOCK void_block = *now;//用于判断进行操作后block位置是否合法 
	int i;
	for (i = 0; i < 4; i++) {
		void_block.point[i].y++;
	}
	return is_conflict(now, &void_block);
}

void keyleft(BLOCK *now) {
	BLOCK void_block = *now;//用于判断进行操作后block位置是否合法
	int i;
	for (i = 0; i < 4; i++) {
		void_block.point[i].x--;
	}
	if (!is_conflict(now,&void_block)) {
		clear(now);
		*now = void_block;
		print(now);
	}
}//向左 

void keyright(BLOCK *now) {
	BLOCK void_block = *now;//用于判断进行操作后block位置是否合法
	int i;
	for (i = 0; i < 4; i++) {
		void_block.point[i].x++;
	}
	if (!is_conflict(now,&void_block)) {
		clear(now);
		*now = void_block;
		print(now);
	}
}//向右

void keydown(BLOCK *now) {
	BLOCK void_block = *now;//用于判断进行操作后block位置是否合法
	int i;
	for (i = 0; i < 4; i++) {
		void_block.point[i].y++;
	}
	if (!is_conflict(now,&void_block)) {
		clear(now);
		*now = void_block;
		print(now);
	}
}//向下

void turn(BLOCK *now) {
	POINT difference;
	BLOCK void_block = *now;//用于判断进行操作后block位置是否合法
	int temp;
	int i;
	for (i = 1; i <= 3; i++) {
		//求出对中心点的 相对位置
		difference.x = void_block.point[i].x - void_block.point[0].x;
		difference.y = void_block.point[i].y - void_block.point[0].y;
		//坐标变换（y=x,x=-y 
		temp = difference.y;
		difference.y = difference.x;
		difference.x = -temp;
		//加上中心坐标 
		void_block.point[i].x = difference.x + void_block.point[0].x;
		void_block.point[i].y = difference.y + void_block.point[0].y;
	}
	if (!is_conflict(now,&void_block))
	{
		clear(now);
		*now = void_block;
		print(now);
	}//翻转
}

//用于判断游戏是否结束 
int is_gameover(BLOCK *now) {
	int i;
	int key;
	/*只需判断当前BLOCK是否有一点是在界面上方以外（需要在当前block已经下落完成后调用）*/
	for (i = 0; i < 4; i++) {
		if (now->point[i].y <= 1) {
			return draw_gameover();
		}
	}
	return FALSE;
}

//游戏退出界面 
int keyexit() {
    int key;
    cleardevice();
	setcolor(CYAN); 
	outtextxy(SIZE*12,SIZE*10,"Down: Resume");
	outtextxy(SIZE*12,SIZE*12,"Enter: New Game");
	outtextxy(SIZE*12,SIZE*14,"Esc: Exit");
	
	while(1){
        if (bioskey(1))
    			key = bioskey(0);
	    else key = 0;
        if(key == ENTER)
            return NEW_GAME;
        else if(key == VK_DOWN)
            return RESUME;
        else if (key == ESC){
			return EXIT;
        }
	}
	
}
