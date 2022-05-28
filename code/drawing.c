#include "drawing.h"

 
void DrawRectangle(double px,double py,double qx,double qy){
	//dbgS("��ʼ���ƾ���\n");
	MovePen(px,py);
	DrawLine(qx-px,0);
	DrawLine(0,qy-py);
	DrawLine(px-qx,0);
	DrawLine(0,py-qy);
	//dbgS("���λ������\n");
}
void FillRectangle(double px,double py,double qx,double qy){
	dbgS("��ʼ����������\n");
	MovePen(px,py);
	StartFilledRegion(1);
	DrawRectangle(px,py,qx,qy);
	EndFilledRegion();
	dbgS("�����λ������\n");
}
//void calculate()

	
//	if(button(GenUIID(0), 1.5, 1.5, 2, 1, "sin()"))
//	{
//		if(str[i]=='\0')
//		str
//	}
	

void drawedge()
{
	//dbgS("��ʼ���Ʊ߿�\n");
	//SetPenColor(Timecolor);
	DrawRectangle(Left_x, Left_y, Right_x, Right_y);
	//dbgS("��ʼ����������\n");
	SetPenColor("Gray");
	MovePen(Left_x, centerY);
	DrawLine(Right_x-Left_x,0);
	//dbgS("������������\n");
	MovePen(centerX, Left_y);
	DrawLine(0,Right_y-Left_y);
	MovePen(centerX+0.04, centerY-0.16);
	DrawTextString("0");
	SetPenColor("Blue");
	//dbgS("�߿�������\n");
}

void drawtext()
{
	//dbgs("��ʼ���������\n")
	SetPenColor("Salmon");
	DrawRectangle(0.5, 1, 3.5, 9.5); 
}

//double transfer(char *a,double x)
//{
//	dbgS("��ǰ������");dbgS(a);dbgS("���ڴ���x��");dbgD(x);dbgC('\n');
//	double y, Function_y;
//	static double Function_origion_y;
//	Function_y = calculate(a,((x-centerX)/scale));
//	dbgS("Function_y��ֵΪ��");dbgD(Function_y);dbgC('\n');
//	if(x <= 3.03) Function_origion_y = Function_y;
//	if(Function_y*Function_origion_y < -100) change = 1;
//	Function_origion_y = Function_y;
////	y = scale*(Function_y+centerY);
////	dbgS("y��ֵΪ��");dbgD(y);dbgC('\n');
//	return y;
//}
double transferx(double x)
{
	//dbgS("���ڴ���x��");dbgD(x);
	return (x*scale+centerX);
}

double transfery(double y)
{
	//dbgS("���ڴ���y��");dbgD(y);dbgC('\n');
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
	//dbgS("��������\n");
}

void DrawSegment(double a, double b, double c, double d)	//����һ���˵���߶�
{
	SetPenColor("Blue");
//	MovePen((a+centerX)*scale, (b+centerY)*scale);
	DrawLine((c-a)*scale, (d-b)*scale);
	DrawPoint(c, d);
	//dbgS("�߶λ������\n");
}
