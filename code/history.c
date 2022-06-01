#include "history.h"
Record *r_head, *r_end;

void initRecordList(void)
{
//	dbgS("��ʼ��ʷ�����ʼ��\n");
	r_head = (Record*)malloc(sizeof(Record));
	r_end = (Record*)malloc(sizeof(Record));
    r_end->next = NULL;
    r_end->before = r_head;
    r_head->next = r_end;

//    dbgS("��ʷ�����ʼ�����\n");
}

void Add_Shape(Shape *p)
{
//	dbgS("���-��ʷ��¼\n");
	Record *r;
	r = (Record*)malloc(sizeof(Record));
	r->ty = 0;
	r->addedShape = p;
	r_end->before->next = r;
	r->before = r_end->before;
	r->next = r_end;
	r_end->before = r;
//	dbgS("���-��ʷ��¼���\n");
}

void Del_Shape(Shape *p)
{
//	dbgS("ɾ��-��ʷ��¼\n");
	Record *r;
	r = (Record*)malloc(sizeof(Record));
	r->ty = 1;
	r->deletedShape = p;
	r_end->before->next = r;
	r->before = r_end->before;
	r->next = r_end;
	r_end->before = r;
//	dbgS("ɾ��-��ʷ��¼���\n");
}