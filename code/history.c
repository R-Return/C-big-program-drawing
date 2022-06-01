#include "history.h"
Record *r_head, *r_end;

void initRecordList(void)
{
//	dbgS("开始历史链表初始化\n");
	r_head = (Record*)malloc(sizeof(Record));
	r_end = (Record*)malloc(sizeof(Record));
    r_end->next = NULL;
    r_end->before = r_head;
    r_head->next = r_end;

//    dbgS("历史链表初始化完成\n");
}

void Add_Shape(Shape *p)
{
//	dbgS("添加-历史记录\n");
	Record *r;
	r = (Record*)malloc(sizeof(Record));
	r->ty = 0;
	r->addedShape = p;
	r_end->before->next = r;
	r->before = r_end->before;
	r->next = r_end;
	r_end->before = r;
//	dbgS("添加-历史记录完成\n");
}

void Del_Shape(Shape *p)
{
//	dbgS("删除-历史记录\n");
	Record *r;
	r = (Record*)malloc(sizeof(Record));
	r->ty = 1;
	r->deletedShape = p;
	r_end->before->next = r;
	r->before = r_end->before;
	r->next = r_end;
	r_end->before = r;
//	dbgS("删除-历史记录完成\n");
}