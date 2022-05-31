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
	double i;
	//dbgS("��ʼ���Ʊ߿�\n");
	//SetPenColor(Timecolor);
	
	//dbgS("��ʼ����������\n");
	SetPenColor("Light Gray");
	for(i = centerX; i <= Right_x; i += 0.5*scale)
	{
		MovePen(i, Left_y);
		DrawLine(0,Right_y-Left_y);
	}
	for(i = centerX; i >= Left_x; i -= 0.5*scale)
	{
		MovePen(i, Left_y);
		DrawLine(0,Right_y-Left_y);
	}
	for(i = centerY; i <= Right_y; i += 0.5*scale)
	{
		MovePen(Left_x, i);
		DrawLine(Right_x-Left_x,0);
	}
	for(i = centerY; i >= Left_y; i -= 0.5*scale)
	{
		MovePen(Left_x, i);
		DrawLine(Right_x-Left_x,0);
	}
	SetPenColor("Black");
	MovePen(Left_x, centerY);
	DrawLine(Right_x-Left_x,0);
	//dbgS("������������\n");
	MovePen(centerX, Left_y);
	DrawLine(0,Right_y-Left_y);
	MovePen(centerX+0.04, centerY-0.22);
	DrawTextString("0");
	DrawRectangle(Left_x, Left_y, Right_x, Right_y);
	SetPenColor("Blue");
	//dbgS("�߿�������\n");
}

void drawtext()
{
	//dbgS("��ʼ���������\n");
	SetPenColor("Salmon");
	DrawRectangle(0.5, 1, 3.5, 9.5);
	Shape *p;
	int count = 0, total = 0;
	for(p = head->next;p != end; p = p->next)
	{	
	//	p->static_page = page;
		if(p->static_page == page)
		{
		if(p->ty == 3)
			continue;
		SetPenColor("Slategray");
		if(p->isChosen || p->isClicked == 1)
		{
			SetPenColor("Shiningred");
		}
		if(p->ty == 4)SetPointSize(15);
		drawLabel(0.6, 9.2 - count * 0.4, p->expression);
		//dbgS("���ʽ�������\n");
		SetPenColor("Salmon");
		MovePen(0.5, 9.2 - count * 0.4-0.05);
		DrawLine(3, 0);
		count++;
		total++;
		SetPointSize(20);
		}
		if ( count >  20 )
		{ 
			page++;
		//	SetPenColor("White");
		//	drawRectangle(0.51, 1.05, 2.98, 8.4, 1); 
			count = 0;
		}
		//static_flag = 1;
	} 
	//dbgS("��ʼ���������\n");
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
	MovePen((x*scale+centerX) + point_r, (y*scale+centerY));
	StartFilledRegion(1);
	DrawArc(point_r, 0, 360);
	EndFilledRegion();
	MovePen((x*scale+centerX), (y*scale+centerY));
	//dbgS("��������\n");
}
