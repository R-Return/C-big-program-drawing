#include "LinkList.h"
#include <math.h>
void initLinkList(void)
{
    dbgS("��ʼ�����ʼ����\n");
	head = (Shape*)malloc(sizeof(Shape));
    end = (Shape*)malloc(sizeof(Shape));
    end->next = NULL;
    head->next = end;
    dbgS("�����ʼ����ɡ�\n");
}

void insertPoint(int i, int ty, double x, double y) //i���Ʋ���״̬����һ������0���������Ϊ1��ty��ʾ����
{
    dbgS("��ʼ�����ڵ�\n");
	Shape *p, *q;
    struct Point *r;    //������ǰλ��
    static struct Point *e; //������β���
    r = (struct Point*)malloc(sizeof(struct Point));
    r->x = x;
    r->y = y;
    r->next = NULL;
    if(i == 0)
    {
        p = end->before;
        q = (Shape*)malloc(sizeof(Shape));
        p->next = q;
        q->next = end;
        q->isChosen = 0;
        q->isClicked = -1;
        q->ty = ty;
        e = q->pHead;
    }
    e->next = r;
    dbgS("��ڵ�������\n");
}

void insertCircle(int i, double x, double y)
{
    dbgS("��ʼ����Բ�ڵ�\n");
	Shape *p, *q;
    struct Circle r;
    p = end->before;
    q = (Shape*)malloc(sizeof(Shape));
    p->next = q;
    q->next = end;
    q->isChosen = 0;
    q->isClicked = -1;
    q->ty = 4;
    if(i == 0)
    {
        r.x = x;
        r.y = y;
    }else{
        r.r = pow((pow(x-(r.x),2)+pow(y-(r.y),2)),0.5);
    }
    dbgS("Բ�ڵ�������\n");
}

void insertFunc(char *a)
{
    dbgS("��ʼ���뺯��\n");
	Shape *p, *q;
    p = end->before;
    q = (Shape*)malloc(sizeof(Shape));
    p->next = q;
    q->next = end;
    q->isChosen = 0;
    q->isClicked = -1;
    q->ty = 5;
    q->f.function = a;
    dbgS("�����������\n");
}

void deleteList(void)
{
    dbgS("��ʼɾ���ڵ�\n");
	Shape *p = head;
    while(p->next != end)
    {
        if (p->isClicked == 1) p->before->next = p->next;
        break;
    }
    dbgS("�ڵ�ɾ�����\n");
}