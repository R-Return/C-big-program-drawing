#ifndef DRAWING_H
#define DRAWING_H

#include "Header.h"

void DrawRectangle(double px, double py, double qx, double qy);
void FillRectangle(double px, double py, double qx, double qy);
void drawedge();
int inDraw(double x, double y);
double transferx(double x);
double transfery(double y);
void DrawTo(double x, double y);
void DrawPoint(double x, double y);
#endif //DRAWING_H