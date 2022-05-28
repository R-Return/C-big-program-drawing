#include "drawing.h"

 
void DrawRectangle(double px,double py,double qx,double qy){
	//dbgS("开始绘制矩形\n");
	MovePen(px,py);
	DrawLine(qx-px,0);
	DrawLine(0,qy-py);
	DrawLine(px-qx,0);
	DrawLine(0,py-qy);
	//dbgS("矩形绘制完成\n");
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
	//dbgS("开始绘制边框\n");
	//SetPenColor(Timecolor);
	DrawRectangle(Left_x, Left_y, Right_x, Right_y);
	//dbgS("开始绘制坐标轴\n");
	SetPenColor("Gray");
	MovePen(Left_x, centerY);
	DrawLine(Right_x-Left_x,0);
	//dbgS("横坐标绘制完成\n");
	MovePen(centerX, Left_y);
	DrawLine(0,Right_y-Left_y);
	MovePen(centerX+0.04, centerY-0.16);
	DrawTextString("0");
	SetPenColor("Blue");
	//dbgS("边框绘制完成\n");
}

void drawtext()
{
	//dbgs("开始绘制输出框\n")
	SetPenColor("Salmon");
	DrawRectangle(0.5, 1, 3.5, 9.5); 
}

//double transfer(char *a,double x)
//{
//	dbgS("当前函数：");dbgS(a);dbgS("现在传入x：");dbgD(x);dbgC('\n');
//	double y, Function_y;
//	static double Function_origion_y;
//	Function_y = calculate(a,((x-centerX)/scale));
//	dbgS("Function_y的值为：");dbgD(Function_y);dbgC('\n');
//	if(x <= 3.03) Function_origion_y = Function_y;
//	if(Function_y*Function_origion_y < -100) change = 1;
//	Function_origion_y = Function_y;
////	y = scale*(Function_y+centerY);
////	dbgS("y的值为：");dbgD(y);dbgC('\n');
//	return y;
//}
double transferx(double x)
{
	//dbgS("现在传入x：");dbgD(x);
	return (x*scale+centerX);
}

double transfery(double y)
{
	//dbgS("现在传入y：");dbgD(y);dbgC('\n');
	return (y*scale+centerY);
}

void DrawTo(double x, double y)
{
	double ox, oy;
	ox = GetCurrentX();
	oy = GetCurrentY();
	DrawLine(transferx(x)-ox, transfery(y)-oy);
}

void DrawPoint(double x, double y)
{
	MovePen((x+centerX)*scale + point_r, (y+centerY)*scale);
//	if()
	SetPenColor("Blue");
	StartFilledRegion(1);
	DrawArc(point_r, 0, 360);
	EndFilledRegion();
	MovePen((x+centerX)*scale, (y+centerY)*scale);
	//dbgS("点绘制完成\n");
}

void DrawSegment(double a, double b, double c, double d)	//绘制一个端点加线段
{
	SetPenColor("Blue");
//	MovePen((a+centerX)*scale, (b+centerY)*scale);
	DrawLine((c-a)*scale, (d-b)*scale);
	DrawPoint(c, d);
	//dbgS("线段绘制完成\n");
}
