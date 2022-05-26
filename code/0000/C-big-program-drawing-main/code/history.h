#ifndef HISTORY_H
#define HISTORY_H

#include "Header.h"
enum ActionType {
    add, modify, move, del
};

typedef struct record {
    enum ActionType ty; 			// add, modify, move, del

    // add
    Shape *addedShape;
    struct Function *addedFunc;

    // modify
    struct Point *modifiedPoint;
    double mpOldX, mpOldY;

    struct Func *modifiedFunc;
    struct Func *oldFunc;

    // move
    Shape *movedShape;
    double deltaX, deltaY;

    // del
    Shape *deletedShape;
    struct Func *deletedFunc;

    struct record *next;
}Record;

#endif	//HISTORY_H