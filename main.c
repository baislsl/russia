#include "main.h"

int flag;

//存放不同BLOCK的形状信息 
POINT array[7][4] =
{
	{ { 0,0 },{ -1,0 },{ 1,0 },{ 2,0 } },
	{ { 0,0 },{ 0,-1 },{ 1,0 },{ 2,0 } },
	{ { 0,0 },{ -2,0 },{ -1,0 },{ 0,-1 } },
	{ { 0,0 },{ 0,-1 },{ 1,0 },{ 1,1 } },
	{ { 0,0 },{ 0,1 },{ 1,0 },{ 1,-1 } },
	{ { 0,0 },{ 0,1 },{ 1,0 },{ 1,1 } },
	{ { 0,0 },{ -1,0 },{ 0,-1 },{ 0,1 } }
};
											
/*initialize对指针p指向的结构进行初始化*/											
void initialize_block(BLOCK *p)
{
	int i, rands;
	p->point[0].y = 1;
	p->point[0].x = WIDTH / 2;
	p->shape = rand() % 7;
	p->nColor = coloraddr[p->shape];
	for (i = 1; i <= 3; i++)
	{
		p->point[i].x = p->point[0].x + array[p->shape][i].x;
		p->point[i].y = p->point[0].y + array[p->shape][i].y;
	}
	/*随机确定旋转方向*/
	rands = rand() % 4;
	while (rands--)
	{
		int temp;
		POINT difference;
		for (i = 1; i <= 3; i++) {
			//求出对中心点的 相对位置
			difference.x = p->point[i].x - p->point[0].x;
			difference.y = p->point[i].y - p->point[0].y;
			//坐标变换（y=x,x=-y 
			temp = difference.y;
			difference.y = difference.x;
			difference.x = -temp;
			//加上中心坐标 
			p->point[i].x = difference.x + p->point[0].x;
			p->point[i].y = difference.y + p->point[0].y;
		}
	}
}

/*删除指定行*/
void delete_line(int line_num)
{
	int k, i;
	for (k = line_num; k > 1; k--)
	{
		/*把第line_num-1行的所有颜色填充到line_num中*/
		for (i = 1; i <= WIDTH; i++)
		{
			draw_square(i, k, condition[i][k - 1]);
		}
	}
	/*将第一行（游戏方框最上方一行）全部填黑*/
	for (i = 1; i <= WIDTH; i++)
	{
		draw_square(i, 1, BLACK);
	}
}

//判断是否有满行并且返回最低部的行号
int is_fullline()
{
	int line_num, k;
	for (line_num = HEIGHT; line_num >= 1; line_num--)
	{
		/*判断第line_num行是否填满了*/
		for (k = 1; k <= WIDTH; k++)
		{
			if (condition[k][line_num] == BLACK) break;
		}
		if (k == WIDTH + 1) return line_num;
	}
	return FALSE;
}


void start_game()
{
	/*游戏主体部分*/
	int key;
	BLOCK *now, *next;/*用now代表当前移动的block，next表示下一个出来的block*/
    SetTimer(newtimer);
	srand(time(NULL));
	now = (BLOCK*)malloc(sizeof(BLOCK));
	next = (BLOCK*)malloc(sizeof(BLOCK));
	initialize_block(now);
	print(now);
	initialize_block(next);
	print_next(next);

	TimerCounter = 0;
	flag = DO_NOTHING;   //保证游戏进行 
	while (1)
	{
		if (bioskey(1))
			key = bioskey(0);
		else key = 0;
		switch (key)
		{
		case VK_LEFT:keyleft(now); break;//左移
		case VK_RIGHT:keyright(now); break;//右移
		case VK_DOWN:keydown(now); break;//向下移动
		case VK_UP:turn(now); break;//翻转
		case END:bioskey(0); break;//暂停
		case ESC:flag = keyexit(); break;//进入退出界面 
		}
		
		if(flag==EXIT || flag==NEW_GAME){
		    return;  //函数出口一 
        }
        else if(flag == RESUME) //恢复游戏界面 
        {
            InitializeGraph(); //画出游戏界面 
            flag = DO_NOTHING; //保证游戏进行 
            draw_condition();  //画出游戏面板 
            print(now);        //画出当前方块
            print_next(next);  //画出下一个方块提示 
            TimerCounter = 0;
        }

		/*是否要下落*/
		if (TimerCounter > 9)
		{   
 	        if (is_stop(now))//判断是否已经到底
    		{
    			int k;
				if (k = is_gameover(now)) 
				{
					flag = k;
		            return;  //函数出口二 
                }
    		  /*可能同时有多行填满，所以需要用while不断检测到没有为止*/
    			while (k = is_fullline())
    			{
    				delete_line(k);
    				add_grade();
    			}
    			*now = *next;
				/*判断新生成的是否没下落前就已经和当前已有的方块重叠*/
				for (k = 0; k < 4; k++)
				{
					if (condition[now->point[k].x][now->point[k].y] != BLACK)
					{
						print(now);
						flag = draw_gameover();
						return;//函数出口三
					}
				}
				print(now);
    			initialize_block(next);
    			print_next(next);
    		}
			else
    		    keydown(now);

			TimerCounter = 0;
			
		}
	}
}

void main(void)
{   
    //初始化游戏 
    flag = DO_NOTHING;
    InitializeGraph();
    start_game();
    
    //判断用户选择退出还是重新开始 
    while(1){
        switch(flag){
            case NEW_GAME:
                DeleteTimer();
            	InitializeGraph();/////初始化游戏界面
                start_game();
                break;
            case EXIT:
                closegraph();
                exit(0); //退出程序 
        }
    } 
}
