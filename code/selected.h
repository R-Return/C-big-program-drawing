#ifndef SELECTED_H
#define SELECTED_H

#define Pi 3.1415926
#include "Header.h"
static int chose = 0;				//判断点线等是否选中的参数 ，初始置0为未选中
static double distant_segement;		//储存线段长度
static double distant_point;
static double degree_point;
static double degree_segement;
static double area;

//函数声明
void MouseEventProcess(int x, int y, int button, int event);
void Select_Point(int nowx, int nowy, struct Point *head) ;
void Select_Line(int nowx, int nowy, struct Point *head);
void Select_Poly(int nowx, int nowy, struct Point *head);
double CalculateDistance_segement(void);
double CalculateDistance_point(void);
double CalculateDegree_point(void);
double CalculateDegree_segement(void);
double Calculatearea_polygon(void);

#endif//SELECTED_H