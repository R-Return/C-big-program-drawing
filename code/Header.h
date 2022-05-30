#ifndef HEADER_H
#define HEADER_H

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
#include <stdlib.h>
#include "strlib.h"
#include "simpio.h"
#include "genlib.h"
#include "gcalloc.h" 
#include "boolean.h"
#include <math.h>

#include "debug.h"
#include "function.h"
#include "drawing.h"
#include "LinkList.h"
//#include "history.h"
#include "selected.h"
#define MAX 100	//函数字符串最大长度

extern double Left_x, Left_y, Right_x, Right_y;
extern double centerX, centerY, scale;
extern int insert_state;
extern int DisSeg, DisPoint, DegSeg, AreaPoly;
extern int result_DisSeg, result_DisPoint, result_DegSeg, result_AreaPoly;
extern char str[MAX];
extern double point_r;
extern void store();
extern void read();

#endif //HEADER_H
