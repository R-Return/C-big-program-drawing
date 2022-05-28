#include "LinkList.h"
#include <math.h>
#include <string.h>
Shape *head, *end;

struct Point *e, *be;	//点池尾结点
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

/*
*i控制插入状态，第一个点是0，后面插入为1；ty表示类型，
*connect表示连接度，0为不与前相连，1为与前连的确认点，2为多边形尾结点，3为未确认点
*多边形的pHead的connect为-1时，表示多边形构建完成
*/
void insertPoint(int i, int ty, int connect, double x, double y) //i控制插入状态，第一个点是0，后面插入为1；ty表示类型
{
    //dbgS("开始插入点节点\n");
	Shape *q;
	struct Point *r;    //点链表当前位置
	char a[MAX];
    r = (struct Point*)malloc(sizeof(struct Point));
    r->x = x;
    r->y = y;
    r->connect = connect;
    r->next = NULL;
    //dbgS("新节点建立完成\n");
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
	    
        e = q->pHead;
    }
//绘制动画
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
//		dbgS("尾结点设立，头节点connect置-1\n");
//	}
	
	if (ty == 0) {
		sprintf(a, "(%.2f , %.2f)", x, y);
		strcpy(q->expression, a);
		dbgS(q->expression);
		dbgC('\n');
	} else if ((ty == 2 || ty == 1)&& connect == 1) {
		//dbgS("准备计算表达式\n");
		q = end->before;
		if ((q->pHead->next->x) != (r->x) && (q->pHead->next->y) != (r->y)) {
			//dbgS("准备计算斜率\n");
			double slope;
			slope = (r->y - q->pHead->next->y) / (r->x - q->pHead->next->x);
			//dbgS("斜率计算完成\n");
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
	//dbgS("点节点插入完成\n");
}


//confirm确认是否为最终圆
void insertCircle(int i, int confirm, double x, double y)
{
    //dbgS("开始插入圆节点\n");
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
		//dbgS("当前圆心：");dbgD(q->c.x);dbgC(' ');dbgD(q->c.y);dbgC('\n');
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
	//dbgS("圆节点插入完成\n");
}

void insertFunc(char a[])
{
    //dbgS("开始插入函数\n");
	int tmp;
	tmp = strlen(a);
	a[tmp] = '#';
	a[tmp + 1] = '\0'; 
	dbgS("当前函数式为：");dbgS(a);dbgC('\n');
    double y;
	int d = 1, interrupt = 0;
	double j;
	double Last_y;
	for(j=-9;j<=9;j+=0.01)
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
		else if(Last_y * y <-800)
		{
			insertPoint(1, 5, 0, j, y);
			//dbgS("y的值为：");dbgD(y);dbgC('\n');
		}
		else
		{
			insertPoint(1, 5, 1, j, y);
		}
		//dbgS( "完成计算函数点次数：");dbgI(d);dbgS( "函数纵坐标为：");dbgD(y);dbgC('\n');
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
	
    dbgS("函数插入完成\n");
}

void deleteList(void)
{
    dbgS("开始删除节点\n");
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
    dbgS("节点删除完成\n");
}
