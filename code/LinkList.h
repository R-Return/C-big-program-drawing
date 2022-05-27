#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include "Header.h"
#define MAX 100	//函数字符串最大长度
enum ShapeType {
    point, line, segment, poly, circle, function
};

struct Point {
    double x;
	double y;
	int connect;
//	struct Point *before;
    struct Point *next;
};


struct Circle {
    double x;
	double y;
	double r;
	int confirm;
};


typedef struct shape{
    enum ShapeType ty;		// point, line, segment, poly, circle; function
    int isChosen;
    int isClicked;
    struct Point *pHead;		// point list, for point, line, segment, poly
    struct Circle c;
    char expression[MAX];
    struct shape *before;
    struct shape *next;
}Shape;

extern Shape *head, *end;

void initLinkList(void);
void insertPoint(int i, int ty, int connect, double x, double y);
void insertCircle(int i, int confirm, double x, double y);
void insertFunc(char a[]);
void deleteList(void);

#endif	//_LINKLIST_H_