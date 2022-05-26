#ifndef DRAWING_H
#define DRAWING_H

#include "Header.h"

void DrawRectangle(double px, double py, double qx, double qy);
void FillRectangle(double px, double py, double qx, double qy);
void drawedge();
//double transfer(char* a,double x);
double transferx(double x);
double transfery(double y);
void DrawTo(double x, double y);
void DrawPoint(double x, double y);
void DrawSegment(double a, double b, double c, double d);
#endif //DRAWING_H