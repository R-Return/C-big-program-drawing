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
	DrawRectangle(3,7,9.2,0.5);
	//dbgS("��ʼ����������\n");
	SetPenColor("Gray");
	MovePen(3, centerY);
	DrawLine(6.2,0);
	//dbgS("������������\n");
	MovePen(centerX, 0.5);
	DrawLine(0,6.5);
	MovePen(centerX+0.04, centerY-0.16);
	DrawTextString("0");
	SetPenColor("Blue");
	//dbgS("�߿�������\n");
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
	DrawLine(x-ox, y-oy);
}
