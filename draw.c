#include "main.h"


int condition[WIDTH + 2][HEIGHT + 2];//������Ϸ�����Ϣ 
int coloraddr[7] = { 7,1,2,3,4,5,6 };//���治ͬ��״BLOCK����ɫ��Ϣ 
static int grade;//���� 


//����������Ϸ���� 
void InitializeGraph()
{
	int i, j;
	int gdriver = VGA, gmode = VGAHI, errorcode;
	/* ��ʼ��ͼ��ģʽ*/
	if(flag==DO_NOTHING)   //�ж��Ƿ�տ�ʼ��Ϸ 
    {
        initgraph(&gdriver, &gmode, "");
        welcome();
    }
    
    if(flag==DO_NOTHING || flag==NEW_GAME) //�ж��Ƿ���Ҫ�����Ϸ������Ϣ 
    {
       for (i = 0; i <= WIDTH + 1; i++)
    		for (j = 0; j <= HEIGHT + 1; j++)
    			condition[i][j] = BLACK; 		
	    grade = 0;
    } 
    
     
	setcolor(WHITE);
	cleardevice();
    
	/*������Ϸ��Ҫ����ı߿�*/
	setlinestyle(4, 0xF3D0, 3);
	rectangle(SIZE, SIZE, SIZE*(WIDTH + 1), SIZE*(HEIGHT + 1));

	/*���Ʒ����߿������ʼ����*/
	setfillstyle(1, 4);
	outtextxy(SIZE*(WIDTH + 3.5), SIZE*(HEIGHT / 2 + 2), "score");
	rectangle(SIZE*(WIDTH + 2.5), SIZE*(HEIGHT / 2 + 3), SIZE*(WIDTH + 6.5), SIZE*(HEIGHT / 2 + 5));
	outtextxy(SIZE*(WIDTH + 4.5), SIZE*(HEIGHT / 2 + 4), itoa(grade, "0000", 10));

	/*������һ��ͼ���ı߿�*/
	outtextxy(SIZE*(WIDTH + 2.5), SIZE*(HEIGHT / 2 - 6), "Next block");
	rectangle(SIZE*(WIDTH + 2), SIZE*(HEIGHT / 2 - 5), SIZE*(WIDTH + 7), SIZE*(HEIGHT / 2));
	
	/*�������ָ��*/
	setcolor(GREEN);
	outtextxy(SIZE*(WIDTH + 2.5), SIZE*(HEIGHT / 2 + 7), "End: Pause");
	outtextxy(SIZE*(WIDTH + 2.5), SIZE*(HEIGHT / 2 + 8), "Ecs: Exit");
	outtextxy(SIZE*(WIDTH + 2.5), SIZE*(HEIGHT / 2 + 9), "Up: Rotate");
	
}

/*���ƶ�λ�û�����ɫֵΪcolor��������*/ 
void draw_square(int x, int y, int color)
{
	if ((x >= 1 && x <= WIDTH&&y >= 1 && y <= HEIGHT))
	{
		setfillstyle(1, color);
		bar(SIZE*x+1, SIZE*y+1, SIZE*(x + 1)-1, SIZE*(y + 1)-1);
		condition[x][y] = color;
	}
	else if (x >= WIDTH + 2)//��ʱ�������next��һ��ͼ�ε�λ�ã�����condition��ֵ���øı�
	{
		setfillstyle(1, color);
		bar(SIZE*x + 1, SIZE*y + 1, SIZE*(x + 1) - 1, SIZE*(y + 1) - 1);
	}
}

//�������������BLOCK 
void print(BLOCK *p)
{
	int i;
	for (i = 0; i < 4; i++) draw_square(p->point[i].x, p->point[i].y, p->nColor);
}

//�������������BLOCK 
void clear(BLOCK *p)
{
	int i;
	for (i = 0; i < 4; i++)
		draw_square(p->point[i].x, p->point[i].y, BLACK);
}

//������һ��BLOCK 
void print_next(BLOCK *next)
{
	int i;
	/*�����һ��ǰ�Ƚ���������*/
	setfillstyle(1, BLACK);
	bar(SIZE*(WIDTH + 2) + 1, SIZE*(HEIGHT / 2 - 5) + 1, SIZE*(WIDTH + 7) - 1, SIZE*(HEIGHT / 2) - 1);
	for (i = 0; i < 4; i++)
		draw_square(WIDTH + 4 + next->point[i].x-next->point[0].x, HEIGHT / 2 - 3 + next->point[i].y - next->point[0].y, next->nColor);
}

//��������һ��������Ļ�ϻ��� 
void add_grade()
{
	/*�Ƚ�ԭ�ȵķ��������*/
	setcolor(WHITE);
	setfillstyle(1, BLACK);
	bar(SIZE*(WIDTH + 2.5) + 1, SIZE*(HEIGHT / 2 + 3) + 1, SIZE*(WIDTH + 6.5) - 1, SIZE*(HEIGHT / 2 + 5) - 1);

	/*����µķ���*/
	outtextxy(SIZE*(WIDTH + 4.5), SIZE*(HEIGHT / 2 + 4), itoa(++grade, "0000", 10));
}

/*��ʼ��ӭ����*/ 
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
            exit(0);//ֱ���˳���Ϸ
        }
	}
}

//�����ǰ��Ϸ���״̬
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
