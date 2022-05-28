#include "LinkList.h"
#include <math.h>
#include <string.h>
Shape *head, *end;

struct Point *e, *be;	//���β���
void initLinkList(void)
{
    dbgS("��ʼ�����ʼ��\n");
	head = (Shape*)malloc(sizeof(Shape));
    end = (Shape*)malloc(sizeof(Shape));
    end->next = NULL;
    end->before = head;
    head->next = end;

    dbgS("�����ʼ�����\n");
}

/*
*i���Ʋ���״̬����һ������0���������Ϊ1��ty��ʾ���ͣ�
*connect��ʾ���Ӷȣ�0Ϊ����ǰ������1Ϊ��ǰ����ȷ�ϵ㣬2Ϊ�����β��㣬3Ϊδȷ�ϵ�
*����ε�pHead��connectΪ-1ʱ����ʾ����ι������
*/
void insertPoint(int i, int ty, int connect, double x, double y) //i���Ʋ���״̬����һ������0���������Ϊ1��ty��ʾ����
{
    //dbgS("��ʼ�����ڵ�\n");
	Shape *q;
	struct Point *r;    //������ǰλ��
	char a[MAX];
    r = (struct Point*)malloc(sizeof(struct Point));
    r->x = x;
    r->y = y;
    r->connect = connect;
    r->next = NULL;
    //dbgS("�½ڵ㽨�����\n");
    if(i == 0)
    {
        //�������ʼ��
        q = (Shape*)malloc(sizeof(Shape));
        q->pHead = (struct Point*)malloc(sizeof(struct Point));
        
        end->before->next = q;
        q->before = end->before;
	    q->next = end;
	    end->before = q;
	    q->isChosen = 0;
	    q->isClicked = -1;
	    q->ty = ty;
	    
        e = q->pHead;
    }
//���ƶ���
	if(e->connect == 3)
	{
		be->next = r;
		e = r;
	}
	else
	{
		e->next = r;
		be = e;
		e = r;
	}
//	if(connect == 2 && ty == 3)
//	{
//		q->pHead->connect = -1;
//		dbgS("β���������ͷ�ڵ�connect��-1\n");
//	}
	
	if (ty == 0) {
		sprintf(a, "(%.2f , %.2f)", x, y);
		strcpy(q->expression, a);
		dbgS(q->expression);
		dbgC('\n');
	} else if ((ty == 2 || ty == 1)&& connect == 1) {
		//dbgS("׼��������ʽ\n");
		q = end->before;
		if ((q->pHead->next->x) != (r->x) && (q->pHead->next->y) != (r->y)) {
			//dbgS("׼������б��\n");
			double slope;
			slope = (r->y - q->pHead->next->y) / (r->x - q->pHead->next->x);
			//dbgS("б�ʼ������\n");
			sprintf(a, "y = %.2f x + %.2f", slope, r->y - slope * r->x);
		} else if ((q->pHead->next->x) == (r->x)) {
			sprintf(a, "x = %.2f", r->x);
		} else if ((q->pHead->next->y) == (r->y)) {
			sprintf(a, "y = %.2f", r->y);
		}
		strcpy(q->expression, a);
		dbgS(q->expression);
		dbgC('\n');
	}
	//dbgS("��ڵ�������\n");
}


//confirmȷ���Ƿ�Ϊ����Բ
void insertCircle(int i, int confirm, double x, double y)
{
    //dbgS("��ʼ����Բ�ڵ�\n");
	Shape *q;
	char a[MAX];
	
	if(!i)
	{
		q = (Shape *)malloc(sizeof(Shape));

		end->before->next = q;
		q->before = end->before;
		q->next = end;
		end->before = q;
		q->isChosen = 0;
		q->isClicked = -1;
		q->ty = 4;
	}
	else
	{
		q = end->before;
	}
	if (i == 0) {
		q->c.x = x;
		q->c.y = y;
		q->c.confirm = 0;
		//dbgS("��ǰԲ�ģ�");dbgD(q->c.x);dbgC(' ');dbgD(q->c.y);dbgC('\n');
	} else {
		q->c.confirm = confirm;
		q->c.r = pow((pow(x - (q->c.x), 2) + pow(y - (q->c.y), 2)), 0.5);
	}
	
	if (i && confirm) {
		sprintf(a, "(x %.2f)^2 + (y %.2f)^2 = %.2f", -1 * q->c.x, -1 * q->c.y, pow(q->c.r, 2));
		strcpy(q->expression, a);
		dbgS(q->expression);
		dbgC('\n');
	}
	//dbgS("Բ�ڵ�������\n");
}

void insertFunc(char a[])
{
    //dbgS("��ʼ���뺯��\n");
	int tmp;
	tmp = strlen(a);
	a[tmp] = '#';
	a[tmp + 1] = '\0'; 
	dbgS("��ǰ����ʽΪ��");dbgS(a);dbgC('\n');
    double y;
	int d = 1, interrupt = 0;
	double j;
	double Last_y;
	for(j=-9;j<=9;j+=0.01)
	{ 
		//dbgS( "���㺯���������");dbgI(d);dbgC('\n');
		change = 0;
		y = calculate(a,j);
		if(change)
		{
			interrupt = 1;
			continue;
		} 
		if(d == 1)
		{
			insertPoint(0, 5, 0, j, y);
		}
		else if(interrupt == 1)
		{
			insertPoint(1, 5, 0, j, y);
			interrupt = 0;
		}
		else if(Last_y * y <-800)
		{
			insertPoint(1, 5, 0, j, y);
			//dbgS("y��ֵΪ��");dbgD(y);dbgC('\n');
		}
		else
		{
			insertPoint(1, 5, 1, j, y);
		}
		//dbgS( "��ɼ��㺯���������");dbgI(d);dbgS( "����������Ϊ��");dbgD(y);dbgC('\n');
		d++;
		Last_y = y;
	}
	Shape *p;
	p = end->before;
	p->expression[0] = 'y';
	p->expression[1] = ' ';
	p->expression[2] = '=';
	p->expression[3] = ' ';
	p->expression[4] = '\0';
	a[strlen(a) - 1] = '\0';
	strcat( p->expression, a );
	
    dbgS("�����������\n");
}

void deleteList(void)
{
    dbgS("��ʼɾ���ڵ�\n");
	Shape *p = head;
    while(p != end)
    {
		if (p->isClicked == 1) 
		{
			p->before->next = p->next;
			p->next->before = p->before;
			break;
		}
        p = p->next;
    }
    dbgS("�ڵ�ɾ�����\n");
}
