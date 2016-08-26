#include "main.h"


int condition[WIDTH + 2][HEIGHT + 2];//储存游戏面板信息 
int coloraddr[7] = { 7,1,2,3,4,5,6 };//储存不同形状BLOCK的颜色信息 
static int grade;//分数 


//画出整个游戏界面 
void InitializeGraph()
{
	int i, j;
	int gdriver = VGA, gmode = VGAHI, errorcode;
	/* 初始化图形模式*/
	if(flag==DO_NOTHING)   //判断是否刚开始游戏 
    {
        initgraph(&gdriver, &gmode, "");
        welcome();
    }
    
    if(flag==DO_NOTHING || flag==NEW_GAME) //判断是否需要清除游戏运行信息 
    {
       for (i = 0; i <= WIDTH + 1; i++)
    		for (j = 0; j <= HEIGHT + 1; j++)
    			condition[i][j] = BLACK; 		
	    grade = 0;
    } 
    
     
	setcolor(WHITE);
	cleardevice();
    
	/*绘制游戏主要界面的边框*/
	setlinestyle(4, 0xF3D0, 3);
	rectangle(SIZE, SIZE, SIZE*(WIDTH + 1), SIZE*(HEIGHT + 1));

	/*绘制分数边框及输出初始分数*/
	setfillstyle(1, 4);
	outtextxy(SIZE*(WIDTH + 3.5), SIZE*(HEIGHT / 2 + 2), "score");
	rectangle(SIZE*(WIDTH + 2.5), SIZE*(HEIGHT / 2 + 3), SIZE*(WIDTH + 6.5), SIZE*(HEIGHT / 2 + 5));
	outtextxy(SIZE*(WIDTH + 4.5), SIZE*(HEIGHT / 2 + 4), itoa(grade, "0000", 10));

	/*绘制下一个图案的边框*/
	outtextxy(SIZE*(WIDTH + 2.5), SIZE*(HEIGHT / 2 - 6), "Next block");
	rectangle(SIZE*(WIDTH + 2), SIZE*(HEIGHT / 2 - 5), SIZE*(WIDTH + 7), SIZE*(HEIGHT / 2));
	
	/*输出操作指南*/
	setcolor(GREEN);
	outtextxy(SIZE*(WIDTH + 2.5), SIZE*(HEIGHT / 2 + 7), "End: Pause");
	outtextxy(SIZE*(WIDTH + 2.5), SIZE*(HEIGHT / 2 + 8), "Ecs: Exit");
	outtextxy(SIZE*(WIDTH + 2.5), SIZE*(HEIGHT / 2 + 9), "Up: Rotate");
	
}

/*在制定位置绘制颜色值为color的正方形*/ 
void draw_square(int x, int y, int color)
{
	if ((x >= 1 && x <= WIDTH&&y >= 1 && y <= HEIGHT))
	{
		setfillstyle(1, color);
		bar(SIZE*x+1, SIZE*y+1, SIZE*(x + 1)-1, SIZE*(y + 1)-1);
		condition[x][y] = color;
	}
	else if (x >= WIDTH + 2)//这时输出的是next下一个图形的位置，数组condition的值不用改变
	{
		setfillstyle(1, color);
		bar(SIZE*x + 1, SIZE*y + 1, SIZE*(x + 1) - 1, SIZE*(y + 1) - 1);
	}
}

//画出正在下落的BLOCK 
void print(BLOCK *p)
{
	int i;
	for (i = 0; i < 4; i++) draw_square(p->point[i].x, p->point[i].y, p->nColor);
}

//擦除正在下落的BLOCK 
void clear(BLOCK *p)
{
	int i;
	for (i = 0; i < 4; i++)
		draw_square(p->point[i].x, p->point[i].y, BLACK);
}

//画出下一个BLOCK 
void print_next(BLOCK *next)
{
	int i;
	/*输出下一个前先将输出区清空*/
	setfillstyle(1, BLACK);
	bar(SIZE*(WIDTH + 2) + 1, SIZE*(HEIGHT / 2 - 5) + 1, SIZE*(WIDTH + 7) - 1, SIZE*(HEIGHT / 2) - 1);
	for (i = 0; i < 4; i++)
		draw_square(WIDTH + 4 + next->point[i].x-next->point[0].x, HEIGHT / 2 - 3 + next->point[i].y - next->point[0].y, next->nColor);
}

//分数增加一并且在屏幕上画出 
void add_grade()
{
	/*先将原先的分数清除掉*/
	setcolor(WHITE);
	setfillstyle(1, BLACK);
	bar(SIZE*(WIDTH + 2.5) + 1, SIZE*(HEIGHT / 2 + 3) + 1, SIZE*(WIDTH + 6.5) - 1, SIZE*(HEIGHT / 2 + 5) - 1);

	/*输出新的分数*/
	outtextxy(SIZE*(WIDTH + 4.5), SIZE*(HEIGHT / 2 + 4), itoa(++grade, "0000", 10));
}

/*初始欢迎界面*/ 
void welcome(){
    int key;
    setcolor(BROWN); 
	cleardevice();
	outtextxy(SIZE*12,SIZE*10,"Russia Blocks");
	outtextxy(SIZE*12,SIZE*12,"Enter: Start  Game");
	outtextxy(SIZE*12,SIZE*13,"Esc: Exit");
	while(1){
        if (bioskey(1))
    			key = bioskey(0);
	    else key = 0;
        if(key == ENTER)
            break;
        else if (key == ESC){
            closegraph(); 
            exit(0);//直接退出游戏
        }
	}
}

//输出当前游戏面板状态
void draw_condition(){
    int x,y;
    for (x=1; x<=WIDTH; x++)
        {
		    for (y=1; y<=HEIGHT; y++)
			    draw_square(x, y, condition[x][y]);        
        } 
}
int draw_gameover()
{
	int key;
	delay(1000);
	setcolor(RED);
	outtextxy(SIZE * 13, SIZE * 9, "Game Over!");
	setcolor(GREEN);
	outtextxy(SIZE * 12, SIZE * 10, "Enter: New Game");
	outtextxy(SIZE * 13, SIZE * 11, "Esc: Exit");

	while (1) {
		if (bioskey(1))
			key = bioskey(0);
		else key = 0;
		if (key == ENTER)
			return NEW_GAME;
		else if (key == ESC) {
			return EXIT;
		}
	}
}
