#include "Header.h"
 
void DrawRectangle(double px,double py,double qx,double qy){
	MovePen(px,py);
	DrawLine(qx-px,0);
	DrawLine(0,qy-py);
	DrawLine(px-qx,0);
	DrawLine(0,py-qy);
}
void FillRectangle(double px,double py,double qx,double qy){
	MovePen(px,py);
	StartFilledRegion(1);
	DrawRectangle(px,py,qx,qy);
	EndFilledRegion();
}
//void calculate()

	
//	if(button(GenUIID(0), 1.5, 1.5, 2, 1, "sin()"))
//	{
//		if(str[i]=='\0')
//		str
//	}
	

void drawedge()
{
	//SetPenColor(Timecolor);
	DrawRectangle(3,7,9.2,0.5);
	SetPenColor("Blue");
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
