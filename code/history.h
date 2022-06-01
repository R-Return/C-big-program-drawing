#ifndef HISTORY_H
#define HISTORY_H

#include "Header.h"
#include "LinkList.h"


enum ActionType {
    add, del
};

typedef struct record {
    enum ActionType ty; 			// add, modify, move, del

    // add
    struct shape *addedShape;
//    struct Function *addedFunc;
//
//    // modify
//    struct Point *modifiedPoint;
//    double mpOldX, mpOldY;
//
//    struct Func *modifiedFunc;
//    struct Func *oldFunc;
//
//    // move
//    Shape *movedShape;
//    double deltaX, deltaY;

    // del
    struct shape *deletedShape;
//    struct Func *deletedFunc;

    struct record *before;
	struct record *next;
}Record;

extern Record *r_head, *r_end;
void initRecordList(void);
void Add_Shape(struct shape *p);
void Del_Shape(struct shape *p);
#endif	//HISTORY_H