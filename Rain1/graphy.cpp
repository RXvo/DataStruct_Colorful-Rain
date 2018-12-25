#include<graphics.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<process.h>    //���߳�
#include<stdlib.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define MAX 100	
#define STEP 60
POINT point;           //windows�Զ���Ľṹ��  ��
HWND hwnd;             //���ھ��
int sleeptime;         //��������ʱ��

typedef struct Rain {
	int x0, y0;//��ε���ʼλ�� 
	int x, y;//��ε���ֹλ�� 
	int step;//���� 
	COLORREF color;//��ε���ɫ 
	//��εĻ�������Ĳ��� 
	int left; 
	int top; 
	int right; 
	int bottom; 
	double stangle; 
	double endangle; 
}Rain;
Rain graph[MAX];
typedef struct Leaf{
	int left;
	int top;
	int right;
	int bottom;
	int x1,y1,x2,y2,x3,y3,x4,y4;
	COLORREF fillcolor;
	COLORREF linecolor;
}Leaf;
typedef struct Thunder
{
    int x0, y0;//����λ��
    int x1, y1;
    int x2, y2;
    int x3, y3;
    int x4, y4;
    int x5, y5;
    int x6, y6;
    int x7, y7;
    int x8, y8;
    int x9, y9;
}Thunder;


//��Ҷ���� 
void draw_leaf(int left, int top, int right, int bottom, COLORREF fillcolor, COLORREF linecolor) 
{ 
	//����Ҷ����Բ���� 
	setfillcolor(fillcolor); 
	setcolor(fillcolor); 
	fillellipse(left, top, right, bottom); 
	//����Ҷ�е��������� 
	setlinecolor(linecolor); 
	setlinestyle(PS_SOLID, 2); 
	int ox = (left + right) / 2; 
	int oy = (top + bottom) / 2; 
	line(ox - 20, oy - 10, ox + 20, oy + 10); 
	line(ox - 20, oy + 10, ox + 20, oy - 10); 
	setlinecolor(linecolor); 
}


//�������� 
void pool() 
{ 
	int R,G,B;
	R=151;
	G=255;
	B=255;
	setfillcolor(RGB(R,G,B));
	setcolor(RGB(R,G,B));
	fillrectangle(0, 500, 600, 800);
	//���Ƴ����еĺ�Ҷ 
	draw_leaf(450, 550, 550, 600, GREEN, BLACK); 
	draw_leaf(380, 570, 480, 620, GREEN, BLACK); 
}

//Rain
void InitRain(int i)
{
	int R,G,B;
	graph[i].x0 = rand()%600;
	graph[i].y0 = rand()%453;
	graph[i].left = graph[i].x0;
	graph[i].top = graph[i].y0;
	graph[i].right = graph[i].left + 1;
	graph[i].bottom = graph[i].top +45;
	graph[i].stangle = 4.28;
	graph[i].endangle = 5.22;
	graph[i].step = STEP;
	R = rand()%255;
	G = rand()%255;
	B = rand()%255;
	graph[i].color = RGB(R,G,B);
}

void DropRain(int i)
{
	// ����ԭ��
	setfillcolor(0);//��������ɫ(�����) 
	setlinecolor(0);//��������ɫ(�����) 
	fillpie(graph[i].left,graph[i].top,graph[i].right,graph[i].bottom,graph[i].stangle,graph[i].endangle);//�������
 
	// ������λ��
	graph[i].top += graph[i].step;
	graph[i].bottom += graph[i].step;
	if (graph[i].bottom > 500)	InitRain(i);
 
	// ��new
	setfillcolor(graph[i].color);//��������ɫ(�����) 
	setlinecolor(graph[i].color);//��������ɫ(�����) 
	fillpie(graph[i].left,graph[i].top,graph[i].right,graph[i].bottom,graph[i].stangle,graph[i].endangle);//�������
	
}

//Thunder
void thunder()
{
    int x = rand() % 500;// +20;
    int y = rand() % 100;//+10;
    double stepx = rand() % 2;
    Thunder one;
    one.x0 = x + 0 * stepx; one.y0 = y + 0 * stepx;
    one.x1 = x + 60 * stepx; one.y1 = y + 40 * stepx;
    one.x2 = x + 50 * stepx; one.y2 = y + 60 * stepx;
    one.x3 = x + 70 * stepx; one.y3 = y + 80 * stepx;
    one.x4 = x + 50 * stepx; one.y4 = y + 100 * stepx;
    one.x5 = x + 80 * stepx; one.y5 = y + 140 * stepx;
    one.x6 = x + 40 * stepx; one.y6 = y + 100 * stepx;
    one.x7 = x + 50 * stepx; one.y7 = y + 80 * stepx;
    one.x8 = x + 30 * stepx; one.y8 = y + 70 * stepx;
    one.x9 = x + 40 * stepx; one.y9 = y + 40 * stepx;
    POINT thunder[] = {
        { one.x0,one.y0 },
        { one.x1,one.y1 },
        { one.x2,one.y2 },
        { one.x3,one.y3 },
        { one.x4,one.y4 },
        { one.x5,one.y5 },
        { one.x6,one.y6 },
        { one.x7,one.y7 },
        { one.x8,one.y8 },
        { one.x9,one.y9 },
    };
	setpolyfillmode(WINDING);
    setfillcolor(YELLOW);
    solidpolygon(thunder, 10);//����������ڻ����Ķ���Σ��ޱ߿򣩡�void solidpolygon( const POINT *points, int num);������points ÿ��������꣬����Ԫ�ظ���Ϊ num���ú������Զ����Ӷ������β��num����ζ���ĸ�����
    Sleep(200);
    clearpolygon(thunder, 10);
}

// ������
void main()
{
	int i;
	srand((unsigned)time(NULL)); // �������
	initgraph(600, 800);	// ��ͼ�δ���
	
	pool();   //Draw a pool......
	// ��ʼ������rain
	for(i=0; i<MAX; i++)
	{
		InitRain(i);
	}
 
	// ����rain����������˳�
	
	PlaySound (TEXT("Materier/2798.wav"),NULL,SND_FILENAME | SND_ASYNC| SND_LOOP );
	//PlaySound (TEXT("Materier/10379.wav"),NULL,SND_FILENAME | SND_ASYNC| SND_LOOP );     //This is rain sound         
	while(!kbhit())
	{
		for(i=0; i<MAX; i++)
			DropRain(i);
		thunder();
		Sleep(20);
	}
 
	closegraph();    // �ر�ͼ�δ���
}



/*
void CreateRain(Rain* rain)
{
	Rain *p,*q;
	int i;
	p = ra;
	for(i=0;i<40;i++)
	{
		q = (Rain *)malloc(sizeof(Rain));
		q->next = NULL;
		InitRain(q);
		p->next = q;
		p->n = i;
		p = q;
	}
	p->next = ra;
}

void rainMove(Rain *r) { GetCursorPos(&point); // ��ȡ���ָ��λ�ã���Ļ���꣩ 
	ScreenToClient(hwnd, &point); // �����ָ��λ��ת��Ϊ�������� 
	//�ж�����Ƿ��ڴ���֮�� 
	if (point.x >= 0 && point.x <= 640 && point.y >= 0 && point.y <= 480) 
	{ //��ε�x�����ı� //��ε�y������� 
		if (point.x >= 320) 
		{ 
			r->x0 += 20; r->y0 += (r->step + 10); 
		} 
		else { 
			r->x0 -= 20; 
			r->y0 += (r->step + 10); 
		} 
		sleeptime = 130;//�޸�Sleepʱ�䣬�ӿ����(ģ��������)
	} 
	else { 
		r->y0 = r->y0 + r->step; 
		sleeptime = 250;//�޸�Sleepʱ�䣬�������(ģ��ͷ�ϸ��) 
	}
}

//�߳���������ε���һ��λ�� 
void cleanRain(Rain *r) 
{ 
	setfillcolor(Getcolor(r->x0, r->y0));
	//��䱳����ɫ(�����) 
	setlinecolor(Getcolor(r->x0, r->y0));
	//��䱳��ɫ(�����) 
	fillpie(r->x0, r->y0, r->x0 + 20, r->y0 + 25, r->stangle, r->endangle);//������� 
}
	
//������� 
void drowRain(Rain *r) 
{ 
	setfillcolor(r->color);//��������ɫ(�����) 
	setlinecolor(r->color);//��������ɫ(�����) 
	fillpie(r->x0, r->y0, r->x0 + 20, r->y0 + 25, r->stangle, r->endangle);//������� 
}

//������εĶ���Ч�� 
void rainDrop(Rain *r) 
{ 
	if (r->y0 >= (300 + rand() % 180)) 
	{ 
		cleanrain(r); //�߳���� 
		r->x = r->x0; 
		r->y = r->y0; 
		m->rain = r; 
		_beginthreadex(0, 0, (unsigned int(__stdcall *)(void *))drawwave,(music*)m, 0, 0); 
		//���߳� 
		InitRain(r); 
		//ˢ����� 
	} 
	else 
	{
		cleanrain(r);
	//������� 
	rainmove(r);
	//���������һ��λ��        
	drowrain(r);//�������
    }
}
*/

