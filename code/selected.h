#ifndef SELECTED_H
#define SELECTED_H

#define Pi 3.1415926
#include "Header.h"
static int chose = 0;				//�жϵ��ߵ��Ƿ�ѡ�еĲ��� ����ʼ��0Ϊδѡ��
static double distant_segement;		//�����߶γ���
static double distant_point;
static double degree_point;
static double degree_segement;
static double area;

//��������
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