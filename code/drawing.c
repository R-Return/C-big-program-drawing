#include "drawing.h"
 
void DrawRectangle(double px,double py,double qx,double qy){
	dbgS("开始绘制矩形\n");
	MovePen(px,py);
	DrawLine(qx-px,0);
	DrawLine(0,qy-py);
	DrawLine(px-qx,0);
	DrawLine(0,py-qy);
	dbgS("矩形绘制完成\n");
}
void FillRectangle(double px,double py,double qx,double qy){
	dbgS("开始绘制填充矩形\n");
	MovePen(px,py);
	StartFilledRegion(1);
	DrawRectangle(px,py,qx,qy);
	EndFilledRegion();
	dbgS("填充矩形绘制完成\n");
}
//void calculate()

	
//	if(button(GenUIID(0), 1.5, 1.5, 2, 1, "sin()"))
//	{
//		if(str[i]=='\0')
//		str
//	}
	

void drawedge()
{
	dbgS("开始绘制边框\n");
	//SetPenColor(Timecolor);
	DrawRectangle(3,7,9.2,0.5);
	SetPenColor("Blue");
	dbgS("边框绘制完成\n");
}

double transferx(double X)
{
	dbgS("现在传入x：");dbgD(X);dbgC('\n');
	double X2;
	X2=X*scale+centerX;
	return X2;
}
double transfery(double Y)
{
	dbgS("现在传入y：");dbgD(Y);dbgC('\n');
	double Y2;
	Y2=Y*scale+centerY;
	return Y2;
}
