#include "LinkList.h"
#include <math.h>
Shape *head, *end;
void initLinkList(void)
{
    dbgS("开始链表初始化\n");
	head = (Shape*)malloc(sizeof(Shape));
    end = (Shape*)malloc(sizeof(Shape));
    end->next = NULL;
    end->before = head;
    head->next = end;
    dbgS("链表初始化完成\n");
}

void insertPoint(int i, int ty, double x, double y) //i控制插入状态，第一个点是0，后面插入为1；ty表示类型
{
    dbgS("开始插入点节点\n");
	Shape *p, *q;
    struct Point *r;    //点链表当前位置
    static struct Point *e; //点链表尾结点
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
    dbgS("点节点插入完成\n");
}

void insertCircle(int i, double x, double y)
{
    dbgS("开始插入圆节点\n");
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
    dbgS("圆节点插入完成\n");
}

void insertFunc(char a[])
{
    dbgS("开始插入函数\n");
	Shape *q;
    //p = end->before;
    q = (Shape*)malloc(sizeof(Shape));
    //dbgS("shape指针空间分配完成\n");
    end->before->next = q;
    q->before = end->before;
    q->next = end;
    end->before = q;
    q->isChosen = 0;
    q->isClicked = -1;
    q->ty = 5;
    //dbgS("开始拷贝函数\n");
    strcpy(q->f.function, a);
    dbgS("函数拷贝完成：");dbgS(q->f.function);dbgC('\n');
    dbgS("函数插入完成\n");
}

void deleteList(void)
{
    dbgS("开始删除节点\n");
	Shape *p = head;
    while(p->next != end)
    {
        if (p->isClicked == 1) p->before->next = p->next;
        break;
    }
    dbgS("节点删除完成\n");
}