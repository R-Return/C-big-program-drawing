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
//	dbgS("开始绘制填充矩形\n");
	MovePen(px,py);
	StartFilledRegion(1);
	DrawRectangle(px,py,qx,qy);
	EndFilledRegion();
//	dbgS("填充矩形绘制完成\n");
}
//void calculate()

	
//	if(button(GenUIID(0), 1.5, 1.5, 2, 1, "sin()"))
//	{
//		if(str[i]=='\0')
//		str
//	}
	

void drawedge()
{
	int i;
	char a[5];
	//SetPenColor(Timecolor);
	//dbgS("开始绘制坐标轴\n");
	SetPenColor("Light Gray");
	for(i = 1; centerX + i * 0.5 * scale <= Right_x; i ++)
	{
		MovePen(centerX + i * 0.5 * scale, Left_y);
		DrawLine(0,Right_y-Left_y);
		if( i%2 == 0 && centerX + i * 0.5 * scale + 0.08 <= Right_x)
		{
			SetPenColor("Gray");
			MovePen(centerX + i * 0.5 * scale + 0.04, centerY - 0.22);
			sprintf(a, "%d",i/2);
			DrawTextString(a);
			SetPenColor("Light Gray");
		}
	}
	for(i = 1; centerX - i * 0.5 * scale >= Left_x; i ++)
	{
		MovePen(centerX - i * 0.5 * scale, Left_y);
		DrawLine(0,Right_y-Left_y);
		if( i%2 == 0)
		{
			SetPenColor("Gray");
			MovePen(centerX - i * 0.5 * scale + 0.04, centerY - 0.22);
			sprintf(a, "-%d",i/2);
			DrawTextString(a);
			SetPenColor("Light Gray");
		}
	}
	for(i = 1; centerY + i * 0.5 * scale <= Right_y; i ++)
	{
		MovePen(Left_x, centerY + i * 0.5 * scale);
		DrawLine(Right_y-Left_y,0);
		if( i%2 == 0)
		{
			SetPenColor("Gray");
			MovePen(centerX + 0.04, centerY + i * 0.5 * scale - 0.22);
			sprintf(a, "%d",i/2);
			DrawTextString(a);
			SetPenColor("Light Gray");
		}
	}
	for(i = 1; centerY - i * 0.5 * scale >= Left_y; i ++)
	{
		MovePen(Left_x, centerY - i * 0.5 * scale);
		DrawLine(Right_y-Left_y,0);
		if( i%2 == 0 &&  centerY - i * 0.5 * scale - 0.22>= Left_y)
		{
			SetPenColor("Gray");
			MovePen(centerX + 0.04, centerY - i * 0.5 * scale - 0.22);
			sprintf(a, "-%d",i/2);
			DrawTextString(a);
			SetPenColor("Light Gray");
		}
	}
	//dbgS("开始绘制边框\n");
	SetPenColor("Black");
	MovePen(Left_x, centerY);
	DrawLine(Right_x-Left_x,0);
	//dbgS("横坐标绘制完成\n");
	MovePen(centerX, Left_y);
	DrawLine(0,Right_y-Left_y);
	MovePen(centerX+0.04, centerY-0.22);
	DrawTextString("0");
	DrawRectangle(Left_x, Left_y, Right_x, Right_y);
	SetPenColor("Blue");
	//dbgS("边框绘制完成\n");
}

int inDraw(double x, double y)
{
	if(x >= Left_x && x <= Right_x && y >= Left_y && y <= Right_y)
	return 1;
	else return 0;
}

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
	MovePen((x*scale+centerX) + point_r, (y*scale+centerY));
	StartFilledRegion(1);
	DrawArc(point_r, 0, 360);
	EndFilledRegion();
	MovePen((x*scale+centerX), (y*scale+centerY));
	//dbgS("点绘制完成\n");
}
