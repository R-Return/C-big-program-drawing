#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include "Header.h"
#define maxFunc 100	//函数字符串最大长度
enum ShapeType {
    point, line, segment, poly, circle, function
};

struct Point {
    double x, y;
    struct Point *next;
};

struct Func {
    string f[maxFunc];	//a-幂函数, b-指数函数, c-对数函数, d-三角函数, e-反三角函数
    struct Func *next;
};

struct Circle {
    double x, y, r;
    struct Circle *next;
};

typedef struct shape{
    enum ShapeType ty;		// point, line, segment, poly, circle; function
    int isChosen;
    int isClicked;
    struct Point *pHead;		// point list, for point, line, segment, poly
    struct Circle c;
    struct Func f;
    struct shape *before;
    struct shape *next;
}Shape;

Shape *head, *end;

//函数声名
void initLinkList(void);
void insertPoint(int i, int ty, double x, double y);
void insertCircle(int i, double x, double y);
void insertFunc(char *a);
void deleteList(void);

#endif	//_LINKLIST_H_