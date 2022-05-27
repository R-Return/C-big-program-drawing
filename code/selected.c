#include "selected.h"

void MouseEventProcess(int x, int y, int button, int event);
void Select_Point(int nowx, int nowy, struct Point *head) ;
void Select_Line(int nowx, int nowy, struct Point *head);
void Select_Poly(int nowx, int nowy, struct Point *head);
double CalculateDistance_segement(void);
double CalculateDistance_point(void);
double CalculateDegree_point(void);
double CalculateDegree_segement(void);
double Calculatearea_polygon(void);

//#include "selected.h"

void MouseEventProcess(int x, int y, int button, int event) {
	double mouse_x = 0, mouse_y = 0;
	static int hasAdded = 0, modify = 0;
	uiGetMouse(x, y, button, event);
	mouse_x = ScaleXInches(x);
	mouse_y = ScaleYInches(y);
	
		Shape *sh_chose;
		for ( sh_chose = head->next; sh_chose != end; sh_chose = sh_chose->next ) 
		{
			//dbgS("���ѡ��\n");
			switch (sh_chose->ty) {
				case 0:
					Select_Point((mouse_x-centerX)/scale, (mouse_y-centerY)/scale, sh_chose->pHead);
					break;
				case 2:
					Select_Line((mouse_x-centerX)/scale, (mouse_y-centerY)/scale, sh_chose->pHead);
					break;
				case 3:
					Select_Poly((mouse_x-centerX)/scale, (mouse_y-centerY)/scale, sh_chose->pHead);
					break;
			}
			if (chose) {			//�����ѡ�еĵ���� ��struct�е�chose������1
				sh_chose->isChosen = 1;
			}
			else sh_chose->isChosen = 0;
			switch (event) {
				case BUTTON_DOWN:
					if (button == LEFT_BUTTON && chose)
						sh_chose->isClicked = -sh_chose->isClicked;
						modify = 1;
					break;
				case BUTTON_DOUBLECLICK:
					break;
				case BUTTON_UP:
					if(button == LEFT_BUTTON)modify = 0;
					break;
				case MOUSEMOVE:
//					if(modify == 1)
					break;
			}
		}//for
		//���Ƶ㡢�ߡ������
		switch(event)
		{
			case BUTTON_DOWN:
				if(mouse_x >= Left_x && mouse_x <= Right_x 
					&& mouse_y >= Left_y && mouse_y <= Right_y)
				{
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
					else break;
				}
				else break;
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
				
				break;
			default:
				break;
		}
	

//	switch (button) {						//���ܰ�ťѡ��
//		case 1:
//			distant_segement = CalculateDistance_segement();
//		case 2:
//			distant_point = CalculateDistance_point();
//		case 3:
//			degree_point = CalculateDegree_point();
//		case 4:
//			degree_segement = CalculateDegree_segement();
//		case 5:
//			area = Calculatearea_polygon();
//	}
//
	display();
}

//������ѡ�е��ж�
//ͨ���Ƚ��������λ���Ƿ��ڵ����ڵ���Χ֮�ڣ����ж��Ƿ�ѡ��״̬
void Select_Point(int nowx, int nowy, struct Point *head) {
	//dbgS("ѡ�е��ж�\n");										//ѡ�е�ķ�Χ
	int d; 															//������������ľ���
	d = pow( nowx - head->next->x, 2 ) + pow( nowy - head->next->y, 2);
	if ( pow(d, 0.5) <= point_r ) {
		chose = 1;												//sh->chosen
	}
	//dbgS("ѡ�е��ж����\n");
	/*struct Point *point_ptr;
	for ( point_ptr = head; point_ptr != NULL; point_ptr = point_ptr->next)
	{
		d = pow( nowx - point_ptr->x, 2 ) + pow( nowy - point_ptr->y, 2);
		if ( pow(d, 0.5) <= point_r )
		{
			point_ptr->chose = 1;
		}
	}*/
}

//ѡ���߶��ж�
//ͨ���Ƚ��߶�б�����������λ���γɵ�б�ʣ��Ƿ�����Χ֮�ڣ����ж��Ƿ�ѡ��״̬
void Select_Line(int nowx, int nowy, struct Point *head) {
	//dbgS("ѡ���߶��ж�\n");
	double slope, nowslope, error = 0.001;							//ѡȡ�������
	int x1, y1, x2, y2;												//�߶������˵������
	struct Point *p;
	p = head->next;
	x1 = p->x;
	y1 = p->y;
	if(p->next)
	{
		p = p->next;
		x2 = p->x;
		y2 = p->y;
		//dbgS("����������\n");
	//	slope = (y2 - y1) / (x2 - x1);									//��ǰ�߶ε�б��
	//	nowslope = (nowy - y1) / (nowx - x1);								//�������λ����˵��γ�б��
		if ( ((nowx - x1) * (y2 - y1) <= ((nowy - y1) * (x2 - x1) + error)) 
			&& ((nowx - x1) * (y2 - y1) >= ((nowy - y1) * (x2 - x1) - error))) 
		{
			chose = 1;
		}
	}
	else;
	
	//dbgS("ѡ���߶��ж����\n");
}

void Select_Poly(int nowx, int nowy, struct Point *head) {
	//dbgS("ѡ�ж�����ж�\n");
	int x[80], y[80];
	struct Point *temp;
	int count = 0, i = 0;
	for( temp = head->next; temp; temp = temp->next )
	{
		x[i] = temp->x;
		y[i] = temp->y;
		i++;
	}
	int j;
	for( j = 0; j < i; j = j+2 )
	{
		if( (( x[j] > nowx ) != ( x[j+1] > nowx)) 
		   && ((nowx - x[j]) * (y[j+1] - y[j]) >= ( x[j+1] - x[j]) * (nowy - y[j])))
		   count++;
	}
	if( count % 2 != 0)
		chose = 1;
	//dbgS("ѡ�ж�����ж����\n");
}

double CalculateDistance_segement(void) {
	dbgS("��ʼ�����߶γ���\n");
	Shape *sort;
	double sum = 0;
	int x1, y1, x2, y2;
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
	int x[2], y[2];
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
	int x1, y1, x2, y2;
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
	int x[80], y[80];
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
