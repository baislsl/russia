#include "main.h"

int flag;

//��Ų�ͬBLOCK����״��Ϣ 
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
											
/*initialize��ָ��pָ��Ľṹ���г�ʼ��*/											
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
	/*���ȷ����ת����*/
	rands = rand() % 4;
	while (rands--)
	{
		int temp;
		POINT difference;
		for (i = 1; i <= 3; i++) {
			//��������ĵ�� ���λ��
			difference.x = p->point[i].x - p->point[0].x;
			difference.y = p->point[i].y - p->point[0].y;
			//����任��y=x,x=-y 
			temp = difference.y;
			difference.y = difference.x;
			difference.x = -temp;
			//������������ 
			p->point[i].x = difference.x + p->point[0].x;
			p->point[i].y = difference.y + p->point[0].y;
		}
	}
}

/*ɾ��ָ����*/
void delete_line(int line_num)
{
	int k, i;
	for (k = line_num; k > 1; k--)
	{
		/*�ѵ�line_num-1�е�������ɫ��䵽line_num��*/
		for (i = 1; i <= WIDTH; i++)
		{
			draw_square(i, k, condition[i][k - 1]);
		}
	}
	/*����һ�У���Ϸ�������Ϸ�һ�У�ȫ�����*/
	for (i = 1; i <= WIDTH; i++)
	{
		draw_square(i, 1, BLACK);
	}
}

//�ж��Ƿ������в��ҷ�����Ͳ����к�
int is_fullline()
{
	int line_num, k;
	for (line_num = HEIGHT; line_num >= 1; line_num--)
	{
		/*�жϵ�line_num���Ƿ�������*/
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
	/*��Ϸ���岿��*/
	int key;
	BLOCK *now, *next;/*��now����ǰ�ƶ���block��next��ʾ��һ��������block*/
    SetTimer(newtimer);
	srand(time(NULL));
	now = (BLOCK*)malloc(sizeof(BLOCK));
	next = (BLOCK*)malloc(sizeof(BLOCK));
	initialize_block(now);
	print(now);
	initialize_block(next);
	print_next(next);

	TimerCounter = 0;
	flag = DO_NOTHING;   //��֤��Ϸ���� 
	while (1)
	{
		if (bioskey(1))
			key = bioskey(0);
		else key = 0;
		switch (key)
		{
		case VK_LEFT:keyleft(now); break;//����
		case VK_RIGHT:keyright(now); break;//����
		case VK_DOWN:keydown(now); break;//�����ƶ�
		case VK_UP:turn(now); break;//��ת
		case END:bioskey(0); break;//��ͣ
		case ESC:flag = keyexit(); break;//�����˳����� 
		}
		
		if(flag==EXIT || flag==NEW_GAME){
		    return;  //��������һ 
        }
        else if(flag == RESUME) //�ָ���Ϸ���� 
        {
            InitializeGraph(); //������Ϸ���� 
            flag = DO_NOTHING; //��֤��Ϸ���� 
            draw_condition();  //������Ϸ��� 
            print(now);        //������ǰ����
            print_next(next);  //������һ��������ʾ 
            TimerCounter = 0;
        }

		/*�Ƿ�Ҫ����*/
		if (TimerCounter > 9)
		{   
 	        if (is_stop(now))//�ж��Ƿ��Ѿ�����
    		{
    			int k;
				if (k = is_gameover(now)) 
				{
					flag = k;
		            return;  //�������ڶ� 
                }
    		  /*����ͬʱ�ж���������������Ҫ��while���ϼ�⵽û��Ϊֹ*/
    			while (k = is_fullline())
    			{
    				delete_line(k);
    				add_grade();
    			}
    			*now = *next;
				/*�ж������ɵ��Ƿ�û����ǰ���Ѿ��͵�ǰ���еķ����ص�*/
				for (k = 0; k < 4; k++)
				{
					if (condition[now->point[k].x][now->point[k].y] != BLACK)
					{
						print(now);
						flag = draw_gameover();
						return;//����������
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
    //��ʼ����Ϸ 
    flag = DO_NOTHING;
    InitializeGraph();
    start_game();
    
    //�ж��û�ѡ���˳��������¿�ʼ 
    while(1){
        switch(flag){
            case NEW_GAME:
                DeleteTimer();
            	InitializeGraph();/////��ʼ����Ϸ����
                start_game();
                break;
            case EXIT:
                closegraph();
                exit(0); //�˳����� 
        }
    } 
}
