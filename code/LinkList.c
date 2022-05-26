#include "LinkList.h"
#include <math.h>
Shape *head, *end;
struct Func_expression *fHead, *fEnd;

struct Point *e;	//点池尾结点
void initLinkList(void)
{
    dbgS("开始链表初始化\n");
	head = (Shape*)malloc(sizeof(Shape));
    end = (Shape*)malloc(sizeof(Shape));
    end->next = NULL;
    end->before = head;
    head->next = end;
    
//    fHead = (struct Func_expression*)malloc(sizeof(struct Func_expression));
//    fHead->next = NULL;
//    fEnd = fHead;
    dbgS("链表初始化完成\n");
}

void insertPoint(int i, int ty, int connect, double x, double y) //i控制插入状态，第一个点是0，后面插入为1；ty表示类型
{
    //dbgS("开始插入点节点\n");
	Shape *q;
	struct Point *r;    //点链表当前位置
    r = (struct Point*)malloc(sizeof(struct Point));
    r->x = x;
    r->y = y;
    r->connect = connect;
    r->next = NULL;
//    dbgS("新节点建立完成\n");
    if(i == 0)
    {
        //点链表初始化
        q = (Shape*)malloc(sizeof(Shape));
        q->pHead = (struct Point*)malloc(sizeof(struct Point));
        
        end->before->next = q;
        q->before = end->before;
	    q->next = end;
	    end->before = q;
	    q->isChosen = 0;
	    q->isClicked = -1;
	    q->ty = ty;
	    
//        q->pHead->next = q->pHead;
        e = q->pHead;
    }
//    dbgS("当前尾结点地址：");dbgP(e);dbgC('\n');
    e->next = r;
//    r->next = q->pHead;
//    dbgI(2);
    e = r;
//    dbgS("当前尾结点地址：");dbgP(e);dbgC('\n');
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
	//插入表达式
	struct Func_expression *fp, *fend;
	fp = (struct Func_expression*)malloc(sizeof(struct Func_expression));
	strcpy(fp->func, a);
	fEnd->next = fp;
	fp->next = NULL;
	fEnd = fp;
	
    double y;
	int d = 1, interrupt = 0;
	double j;
	double Last_y;
//	struct Function *p;
	for(j=-5;j<5;j+=0.01)
	{ 
		//dbgS( "计算函数点次数：");dbgI(d);dbgC('\n');
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
		else if(Last_y * y <-100)
		{
			insertPoint(1, 5, 0, j, y);
//			dbgS("y的值为：");dbgD(y);dbgC('\n');
		}
		else
		{
			insertPoint(1, 5, 1, j, y);
		}
		//dbgS( "完成计算函数点次数：");dbgI(d);dbgC('\n');
		d++;
		Last_y = y;
	}
    dbgS("函数插入完成\n");
}

void deleteList(void)
{
    dbgS("开始删除节点\n");
	Shape *p = head;
	struct Func_expression *fp = fHead, *fo;
    while(p != end)
    {
		if (p->isClicked == 1) 
		{
			p->before->next = p->next;
			p->next->before = p->before;
			if(p->ty == 5)fo->next = fp->next;
			break;
		}
		if(p->ty == 5) 
		{
			fo = fp;
			fp = fp->next;
		}
        p = p->next;
    }
    dbgS("节点删除完成\n");
}
