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
#include <math.h>

#include "debug.h"
#include "function.h"
#include "drawing.h"
#include "LinkList.h"
//#include "history.h"
#include "selected.h"
#define maxFunc 100	//函数字符串最大长度

extern double centerX, centerY, scale;

extern char str[maxFunc];

#endif //HEADER_H
