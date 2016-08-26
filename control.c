#include "main.h"

int is_conflict(BLOCK *now,BLOCK *temp) {
    /*now��ָ��ǰ�ķ��飬��temp�ǵ�ǰ������һ���ƶ���õ��ķ��飬ֻ��temp��ĳһ���������е��ص�������now���ص�ʱ�Ż᷵��TRUE*/
	int i, j;
	for (i = 0; i < 4; i++) {
		if (temp->point[i].x<=0 || temp->point[i].x>=WIDTH + 1 || temp->point[i].y>=HEIGHT + 1) {//�������Խ�� 
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

//���BLOCK��������һ�������is_conflict���򷵻ط��� 
int is_stop(BLOCK *now) {
	BLOCK void_block = *now;//�����жϽ��в�����blockλ���Ƿ�Ϸ� 
	int i;
	for (i = 0; i < 4; i++) {
		void_block.point[i].y++;
	}
	return is_conflict(now, &void_block);
}

void keyleft(BLOCK *now) {
	BLOCK void_block = *now;//�����жϽ��в�����blockλ���Ƿ�Ϸ�
	int i;
	for (i = 0; i < 4; i++) {
		void_block.point[i].x--;
	}
	if (!is_conflict(now,&void_block)) {
		clear(now);
		*now = void_block;
		print(now);
	}
}//���� 

void keyright(BLOCK *now) {
	BLOCK void_block = *now;//�����жϽ��в�����blockλ���Ƿ�Ϸ�
	int i;
	for (i = 0; i < 4; i++) {
		void_block.point[i].x++;
	}
	if (!is_conflict(now,&void_block)) {
		clear(now);
		*now = void_block;
		print(now);
	}
}//����

void keydown(BLOCK *now) {
	BLOCK void_block = *now;//�����жϽ��в�����blockλ���Ƿ�Ϸ�
	int i;
	for (i = 0; i < 4; i++) {
		void_block.point[i].y++;
	}
	if (!is_conflict(now,&void_block)) {
		clear(now);
		*now = void_block;
		print(now);
	}
}//����

void turn(BLOCK *now) {
	POINT difference;
	BLOCK void_block = *now;//�����жϽ��в�����blockλ���Ƿ�Ϸ�
	int temp;
	int i;
	for (i = 1; i <= 3; i++) {
		//��������ĵ�� ���λ��
		difference.x = void_block.point[i].x - void_block.point[0].x;
		difference.y = void_block.point[i].y - void_block.point[0].y;
		//����任��y=x,x=-y 
		temp = difference.y;
		difference.y = difference.x;
		difference.x = -temp;
		//������������ 
		void_block.point[i].x = difference.x + void_block.point[0].x;
		void_block.point[i].y = difference.y + void_block.point[0].y;
	}
	if (!is_conflict(now,&void_block))
	{
		clear(now);
		*now = void_block;
		print(now);
	}//��ת
}

//�����ж���Ϸ�Ƿ���� 
int is_gameover(BLOCK *now) {
	int i;
	int key;
	/*ֻ���жϵ�ǰBLOCK�Ƿ���һ�����ڽ����Ϸ����⣨��Ҫ�ڵ�ǰblock�Ѿ�������ɺ���ã�*/
	for (i = 0; i < 4; i++) {
		if (now->point[i].y <= 1) {
			return draw_gameover();
		}
	}
	return FALSE;
}

//��Ϸ�˳����� 
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
