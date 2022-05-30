#include "selected.h"
#include <math.h> 
#include <string.h>
#include "LinkList.h"

//void MouseEventProcess(int x, int y, int button, int event);
//void Select_Point(double nowx, double nowy, struct Point *head) ;
//void Select_Line(double nowx, double nowy, struct Point *head);
//void Select_Poly(double nowx, double nowy, struct Point *head);
//double CalculateDistance_segement(void);
//double CalculateDistance_point(void);
//double CalculateDegree_point(void);
//double CalculateDegree_segement(void);
//double Calculatearea_polygon(void);
int chose = 0;
//#include "selected.h"

void MouseEventProcess(int x, int y, int button, int event) {
	double mouse_x = 0, mouse_y = 0;
	static int hasAdded = 0;
	uiGetMouse(x, y, button, event);
	mouse_x = ScaleXInches(x);
	mouse_y = ScaleYInches(y);
	
	Shape *sh_chose;
		
		//���Ƶ㡢�ߡ������
		switch(event)
		{
			case BUTTON_DOWN:
				if(mouse_x >= Left_x && mouse_x <= Right_x 
					&& mouse_y >= Left_y && mouse_y <= Right_y)
				{
					if (button == LEFT_BUTTON )
					{
						for ( sh_chose = head->next; sh_chose != end; sh_chose = sh_chose->next ) 
						{
							
							if(sh_chose->isChosen == 1 && (insert_state == -1 || insert_state == 0))
							{
								if(insert_state == 0) insert_state = -1;
								sh_chose->isClicked = -1 * (sh_chose->isClicked);
								if(DisSeg == 0 && sh_chose->ty == 2)
								{
									result_DisSeg = CalculateDistance_segement();
									DisSeg = -1;
								}
								else if(DisPoint != -1 &&sh_chose->ty == 0)
								{
									DisPoint ++;
									if(DisPoint == 2)
									{
										result_DisPoint = CalculateDistance_point();
										DisPoint = -1;
									}
								}
								else if(DegSeg != -1 &&sh_chose->ty == 2)
								{
									DegSeg ++;
									if(DegSeg == 2)
									{
										result_DegSeg = CalculateDegree_segement();
										DegSeg = -1;
									}
								}
								else if(AreaPoly == 0 && sh_chose->ty == 3)
								{
									result_DegSeg = Calculatearea_polygon();
									AreaPoly = -1;
								}
							}
						}
					}
						
					if(insert_state == 0 && button == LEFT_BUTTON) 
					{
//						if(hasAdded == 1)
//						{
//							end->before->before->next = end;
//							end->before = end->before->before;
//						}
						insertPoint(0, 0, 0, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
						
						hasAdded = 0;
						//dbgS("������\n");
					}
					else if(insert_state == 1 && button == LEFT_BUTTON) 
					{
						if(hasAdded)
						{
							insertPoint(1, 1, 1, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
							insert_state = -1;
							hasAdded = 0;
							//dbgS("ֱ�߲������\n");
						}
						else
						{
							insertPoint(0, 1, 0, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
							hasAdded = 1;
						}
					}
					else if(insert_state == 2 && button == LEFT_BUTTON) 
					{
						if(hasAdded)
						{
							insertPoint(1, 2, 1, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
							insert_state = -1;
							hasAdded = 0;
							//dbgS("�߶β������\n");
						}
						else
						{
							insertPoint(0, 2, 0, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
							hasAdded = 1;
						}
					}
					else if(insert_state == 3 && button == LEFT_BUTTON)
					{
						if(hasAdded)
						{
							//dbgS("׼�����������ڶ˵�\n");
							insertPoint(1, 3, 1, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
							//dbgS("������ڶ˵�������\n");
						}
						else
						{
							//dbgS("׼����������ͷ�˵�\n");
							insertPoint(0, 3, 0, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
							hasAdded = 1;
							//dbgS("�����ͷ�˵�������\n");
						}
					}
					else if(insert_state == 3 && button == RIGHT_BUTTON)
					{
						//dbgS("׼����������β�˵�\n");
						insertPoint(0, 3, 2, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
						insert_state = -1;
						hasAdded = 0;
						//dbgS("�����β�˵�������\n");
					}
					else if(insert_state == 4 && button == LEFT_BUTTON)
					{
						//dbgS("׼������Բ\n");
						if(hasAdded)
						{
							insertCircle(1, 1, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
							insert_state = -1;
							hasAdded = 0;
							//dbgS("Բ�������\n");
						}
						else
						{
							insertCircle(0, 1, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
							hasAdded = 1;
						}
						
					}
//					else ;
					
							
				}
				
				break;
			case MOUSEMOVE:
				if(insert_state == 2 && hasAdded == 1)	//�߶�
				{
					insertPoint(1, 2, 3, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
				}
				else if(insert_state == 1 && hasAdded == 1)	//ֱ��
				{
					insertPoint(1, 1, 3, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
				}
				else if(insert_state == 3 && hasAdded == 1)	//�����
				{
					insertPoint(1, 3, 3, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
				}
				else if(insert_state == 4 && hasAdded == 1)	//Բ
				{
					insertCircle(1, 0, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
//					dbgS("��ʱԲ�������\n");
				}
				for ( sh_chose = head->next; sh_chose != end; sh_chose = sh_chose->next ) 
				{
					//dbgS("���ѡ��\n");
					switch (sh_chose->ty) {
						case 0:
							Select_Point((mouse_x-centerX)/scale, (mouse_y-centerY)/scale, sh_chose->pHead);
							break;
						case 1:
							Select_Line((mouse_x-centerX)/scale, (mouse_y-centerY)/scale, sh_chose->pHead);
							break;
						case 2:
							Select_Segment((mouse_x-centerX)/scale, (mouse_y-centerY)/scale, sh_chose->pHead);
							break;
						case 3:
							Select_Poly((mouse_x-centerX)/scale, (mouse_y-centerY)/scale, sh_chose->pHead);
							break;
						case 4:
							Select_Circle((mouse_x-centerX)/scale, (mouse_y-centerY)/scale, sh_chose->c.x, sh_chose->c.y, sh_chose->c.r);
							break;
						default:
							break;
					}
					if (chose == 1) {			//�����ѡ�еĵ���� ��struct�е�chose������1
						sh_chose->isChosen = 1;
					}
					else sh_chose->isChosen = 0;
			}
				break;
			default:
				break;
		}

	display();
}

//������ѡ�е��ж�
//ͨ���Ƚ��������λ���Ƿ��ڵ����ڵ���Χ֮�ڣ����ж��Ƿ�ѡ��״̬
void Select_Point(double nowx, double nowy, struct Point *head) {
	//dbgS("ѡ�е��ж�\n");										//ѡ�е�ķ�Χ
	double d; 															//������������ľ���
	d = pow( nowx - head->next->x, 2 ) + pow( nowy - head->next->y, 2);
	if ( pow(d, 0.5) <= 0.05 ) {
		chose = 1;											
	}
	else chose = 0;
	//dbgS("ѡ�е��ж����\n");
	
}

//ѡ��ֱ���ж�
//ͨ���Ƚ�ֱ��б�����������λ���γɵ�б�ʣ��Ƿ�����Χ֮�ڣ����ж��Ƿ�ѡ��״̬
void Select_Line(double nowx, double nowy, struct Point *head) {
	//dbgS("ѡ��ֱ���ж�\n");
	double slope, nowslope, error = 0.05;							//ѡȡ�������
	double x1, y1, x2, y2;												//�߶������˵������
	struct Point *p;
	p = head->next;
	x1 = p->x;
	y1 = p->y;
	if(p->next != NULL)
	{
		p = p->next;
		x2 = p->x;
		y2 = p->y;
		//dbgS("����������\n");
		if(x1!= x2 && nowx != x1)
		{
			slope = (y2 - y1) / (x2 - x1);									//��ǰ�߶ε�б��
			nowslope = (nowy - y1) / (nowx - x1);								//�������λ����˵��γ�б��
			if((nowslope <= slope + error) && (nowslope >= slope - error))
			{
				chose = 1;
			}
			else chose = 0;
		}
	}
//	else;
	
	//dbgS("ѡ��ֱ���ж����\n");
}

//ѡ���߶��ж�
//ͨ���Ƚ��߶�б�����������λ���γɵ�б�ʣ��Ƿ�����Χ֮�ڣ����ж��Ƿ�ѡ��״̬
void Select_Segment(double nowx, double nowy, struct Point *head) {
	//dbgS("ѡ���߶��ж�\n");
	double slope, nowslope, error = 0.05;							//ѡȡ�������
	double x1, y1, x2, y2;												//�߶������˵������
	struct Point *p;
	p = head->next;
	x1 = p->x;
	y1 = p->y;
	if(p->next != NULL)
	{
		p = p->next;
		x2 = p->x;
		y2 = p->y;
		//dbgS("����������\n");
		if(x1!= x2 && nowx != x1)
		{
			slope = (y2 - y1) / (x2 - x1);									//��ǰ�߶ε�б��
			nowslope = (nowy - y1) / (nowx - x1);								//�������λ����˵��γ�б��
			if(((nowslope <= slope + error) && (nowslope >= slope - error)) 
				&& (nowy - y2) * (nowy - y1) <= 0)
			{
				chose = 1;
			}
			else chose = 0;
		}
	}
//	else;
	
	//dbgS("ѡ���߶��ж����\n");
}

void Select_Poly(double nowx, double nowy, struct Point *head) {
	//dbgS("ѡ�ж�����ж�\n");
	double x[80], y[80];
	struct Point *temp;
	int count = 0, i = 0;
	for( temp = head->next; temp; temp = temp->next )
	{
		x[i] = temp->x;
		y[i] = temp->y;
		i++;
	}
	int j;
	for( j = 0; j < i-1; j = j+1 )
	{
		if( (( x[j] > nowx ) != ( x[j+1] > nowx))
		   && (nowx > ( x[j+1] - x[j]) * (nowy - y[j]) / (y[j+1] - y[j]) + x[j]))
		   count++;
	}
	if( (( x[j] > nowx ) != ( x[0] > nowx))
		   && (nowx > ( x[0] - x[j]) * (nowy - y[j]) / (y[0] - y[j]) + x[j]))
		   count++;
	if( count % 2 != 0)
	{
		chose = 1;
		dbgS("ѡ��\n");
	}
		
	else chose = 0;
	//dbgS("ѡ�ж�����ж����\n");
}

void Select_Circle(double nowx, double nowy, double x, double y, double r) {
	//dbgS("ѡ��Բ�ж�\n");
	double nowr;
	nowr = pow(pow(nowx - x, 2) + pow(nowy - y, 2),0.5);
	if( nowr <= r)
		chose = 1;
	else chose = 0;
	//dbgS("ѡ��Բ�ж����\n");
}

double CalculateDistance_segement(void) {
	dbgS("��ʼ�����߶γ���\n");
	Shape *sort;
	double sum = 0;
	double x1, y1, x2, y2;
	for ( sort = head->next; sort; sort = sort->next ) {
		struct Point *temp;
		if (sort->isClicked == 1 && sort->ty == 2) {
			temp = sort->pHead->next;
			x1 = temp->x;
			y1 = temp->y;
			temp = temp->next;
			x2 = temp->x;
			y2 = temp->y;
			sum = pow(pow(x2 - x1, 2) + pow(y2 - y1, 2), 0.5);
			break;
		}
	}
	dbgS("�߶ξ��������ɣ�����Ϊ��");dbgD(sum);dbgC('\n');
	return sum;
}

// ���sum���ص�ֵ������0 �����Ѿ�ѡ�������� ��������� ��timerʱ����ʾ�� ��ʱ��ѡ�в���ȫ����1 Ϊ��һ�μ�����׼��
// ����������������ͬ�ķ���
double CalculateDistance_point(void) {
	dbgS("��ʼ�����������\n");
	Shape *sort;
	double sum;
	double x[2], y[2];
	int count = 0;
	for ( sort = head->next; sort; sort = sort->next ) {
		struct Point *temp;
		if (sort->isClicked == 1 && sort->ty == 0) {
			temp = sort->pHead->next;
			x[count] = temp->x;
			y[count] = temp->y;
			count++;
		}
	}
	if (x[0] != 0 && x[1] != 0) {
		sum = pow(pow(x[1] - x[0], 2) + pow(y[1] - y[0], 2), 0.5);
	}
	dbgS("������������ɣ�����Ϊ��");dbgD(sum);dbgC('\n');
	return sum;
}

//double CalculateDegree_point(void) {
//	dbgS("��ʼ����Ƕ�\n");
//	Shape *sort;
//	double sum = 0;
//	int x[2], y[2];
//	int count = 0;
//	for ( sort = head; sort != NULL; sort = sort->next ) {
//		struct Point *temp;
//		if ( sort->isClicked == 1 && sort->ty == 0 ) {
//			temp = sort->pHead;
//			x[count] = temp->x;
//			y[count] = temp->y;
//			count++;
//		}
//	}
//	if ( x[0] != 0 && x[1] != 0 ) {
//		int k = (y[1] - y[0]) / (x[1] - x[0]);
//		sum = atan(k) * 180 / Pi;
//	}
//	dbgS("�Ƕȼ�����ɣ�");dbgD(sum);dbgC('\n');
//	return sum;
//}

double CalculateDegree_segement(void) {
	dbgS("��ʼ����Ƕ�\n");
	Shape *sort;
	double sum = 0;
	double k[2];
	int count = 0;
	double x1, y1, x2, y2;
	for ( sort = head->next; sort; sort = sort->next ) {
		struct Point *temp;
		if ( sort->isClicked == 1 && sort->ty == 2) {
			temp = sort->pHead->next;
			x1 = temp->x;
			y1 = temp->y;
			temp = temp->next;
			x2 = temp->x;
			y2 = temp->y;
			k[count] = (y2 - y1) / (x2 - x1);
			count++;
		}
	}
	if ( k[0] != 0 && k[1] != 0) {
		int sum = fabs(atan(k[1]) * 180 / Pi - atan(k[0]) * 180 / Pi);
	}
	dbgS("�Ƕȼ�����ɣ�");dbgD(sum);dbgC('\n');
	return sum;
}

double Calculatearea_polygon(void) {
	dbgS("��ʼ�����������\n");
	Shape *sort;
	double sum = 0;
	double x[80], y[80];
	int i;
	for ( sort = head->next; sort; sort = sort->next ) {
		struct Point *temp;
		if ( sort->isClicked == 1 && sort->ty == 3 ) {
			temp = sort->pHead->next;
			for (i = 0; i <= 80 && temp; i++, temp = temp->next) {
				x[i] = temp->x;
				y[i] = temp->y;
			}
			break;
		}
	}
	int j;
	for (j = 0; j <= i-1; j++) {
		sum = sum + x[j] * y[j + 1] - x[j + 1] * y[j];
	}
	sum = sum + x[i] * y[0] - x[0] * y[i];
	sum = 0.5 * fabs(sum);
	dbgS("��������������ɣ�");dbgD(sum);dbgC('\n');
	return sum;
}
