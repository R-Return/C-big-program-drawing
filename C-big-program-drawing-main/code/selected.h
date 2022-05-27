#ifndef SELECTED_H
#define SELECTED_H

#define Pi 3.1415926
#include "Header.h"
static int chose;				//判断点线等是否选中的参数 ，初始置0为未选中
static double distant_segement;		//储存线段长度
static double distant_point;
static double degree_point;
static double degree_segement;
static double area;

//函数声明
extern void MouseEventProcess(int x, int y, int button, int event);
extern void Select_Point(int nowx, int nowy, struct Point *head) ;
extern void Select_Line(int nowx, int nowy, struct Point *head);
extern void Select_Poly(int nowx, int nowy, struct Point *head);
extern double CalculateDistance_segement(void);
extern double CalculateDistance_point(void);
extern double CalculateDegree_point(void);
extern double CalculateDegree_segement(void);
extern double Calculatearea_polygon(void);

#endif//SELECTED_H
