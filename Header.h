#ifndef HEADER_H
#define HEADER_H

extern int pageid;
//void calculate();
//void drawedge();

#include <stdio.h>
#include <windows.h>
#include <winuser.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"
#include <string.h>
#include "strlib.h"
#include "simpio.h"
#include "genlib.h"
#include "gcalloc.h" 

#include "debug.h"
#include "function.h"
#include "drawing.h"
#define maxFunc 100	//函数最大长度

double centerX, centerY, scale;

enum ShapeType {
	point, line, segment, poly, circle, function
};

enum ActionType {
	add, modify, move, del
}; 
struct Point {
	double x, y;
	struct Point *next;
};

struct Func {
	string f[maxFunc];		//a-幂函数, b-指数函数, c-对数函数, d-三角函数, e-反三角函数
	struct Func *next;
};

struct Circle {
	double x, y, r;
	struct Circle *next;
};

struct Shape {
	enum ShapeType ty;		// point, line, segment, poly; circle, function

	struct Point *head;		// point list, for point, line, segment, poly
	//struct Circle *head;	// for circle

	struct Shape *next;
};

struct Record {
	enum ActionType ty; 			// add, modify, move, del

	// add
	bool isAddedShape;
	struct Shape *addedShape;
	struct Function *addedFunc;

	// modify
	bool isModifiedPoint;
	struct Point *modifiedPoint;
	double mpOldX, mpOldY;

	struct Func *modifiedFunc;
	struct Func *oldFunc;

	// move
	struct Shape *movedShape;
	double deltaX, deltaY;

	// del
	bool isDelShape;
	struct Shape *deletedShape;
	struct Func *deletedFunc;

	struct Record *next;
};

//main.c函数声明
void CharEventProcess(char ch);
void KeyboardEventProcess(int key, int event);
void MouseEventProcess(int x, int y, int button, int event);
void display();

#endif //HEADER_H