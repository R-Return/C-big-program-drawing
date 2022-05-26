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
	static int hasAdded = 0;
	uiGetMouse(x, y, button, event);
	mouse_x = ScaleXInches(x);
	mouse_y = ScaleYInches(y);
	
		Shape *sh_chose;
		for ( sh_chose = head->next; sh_chose != end; sh_chose = sh_chose->next ) 
		{
			//dbgS("���ѡ��\n");
			switch (sh_chose->ty) {
				case 0:
					Select_Point(mouse_x, mouse_y, sh_chose->pHead);
					break;
				case 2:
					Select_Line(mouse_x, mouse_y, sh_chose->pHead);
					break;
				case 3:
					Select_Poly(mouse_x, mouse_y, sh_chose->pHead);
					break;
			}
			if (chose) {			//�����ѡ�еĵ���� ��struct�е�chose������1
				sh_chose->isChosen = 1;
			}
			switch (event) {
				case BUTTON_DOWN:
					if (button == LEFT_BUTTON && chose)
						sh_chose->isClicked = -sh_chose->isClicked;
					break;
				case BUTTON_DOUBLECLICK:
					break;
				case BUTTON_UP:
					break;
				case MOUSEMOVE:
					break;
			}
		}//for
		//���Ƶ㡢�ߡ������
		switch(event)
		{
			case BUTTON_DOWN:
				if(insert_state == 0 && button == LEFT_BUTTON) 
				{
					insertPoint(0, 0, 0, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
					insert_state = -1;
					hasAdded = 0;
					dbgS("������\n");
				}
				else if(insert_state == 2 && button == LEFT_BUTTON) 
				{
					if(hasAdded)
					{
						insertPoint(1, 2, 1, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
						insert_state = -1;
						hasAdded = 0;
						dbgS("�߶β������\n");
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
						dbgS("׼�����������ڶ˵�\n");
						insertPoint(1, 3, 1, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
						dbgS("������ڶ˵�������\n");
					}
					else
					{
						dbgS("׼����������ͷ�˵�\n");
						insertPoint(0, 3, 0, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
						hasAdded = 1;
						dbgS("�����ͷ�˵�������\n");
					}
				}
				else if(insert_state == 3 && button == RIGHT_BUTTON)
				{
					dbgS("׼����������β�˵�\n");
					insertPoint(0, 3, 2, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
					insert_state = -1;
					hasAdded = 0;
					dbgS("�����β�˵�������\n");
				}
				else;
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
	dbgS("ѡ�е��ж�\n");
	int r_point = 0.01;												//ѡ�е�ķ�Χ
	int d; 															//������������ľ���
	d = pow( nowx - head->x, 2 ) + pow( nowy - head->y, 2);
	if ( pow(d, 0.5) <= r_point ) {
		chose = 1;												//sh->chosen
	}
	dbgS("ѡ�е��ж����\n");
	/*struct Point *point_ptr;
	for ( point_ptr = head; point_ptr != NULL; point_ptr = point_ptr->next)
	{
		d = pow( nowx - point_ptr->x, 2 ) + pow( nowy - point_ptr->y, 2);
		if ( pow(d, 0.5) <= r_point )
		{
			point_ptr->chose = 1;
		}
	}*/
}

//ѡ���߶��ж�
//ͨ���Ƚ��߶�б�����������λ���γɵ�б�ʣ��Ƿ�����Χ֮�ڣ����ж��Ƿ�ѡ��״̬
void Select_Line(int nowx, int nowy, struct Point *head) {
	dbgS("ѡ���߶��ж�\n");
	double slope, nowslope, error = 0.001;							//ѡȡ�������
	int x1, y1, x2, y2;												//�߶������˵������
	x1 = head->x;
	y1 = head->y;
	head = head->next;
	x2 = head->x;
	y2 = head->y;
	slope = (y2 - y1) / (x2 - x1);									//��ǰ�߶ε�б��
	nowslope = (nowy - y1) / (nowx - x1);								//�������λ����˵��γ�б��
	if ( (nowslope = slope + error) && (nowslope = slope - error) ) {
		chose = 1;
	}
	dbgS("ѡ���߶��ж����\n");
}

void Select_Poly(int nowx, int nowy, struct Point *head) {
	//dbgS("ѡ�ж�����ж�\n");
	int x[80], y[80];
	struct Point *temp;
	int count = 0, i = 0;
	for( temp = head; temp != NULL; temp = temp->next )
	{
		x[i] = temp->x;
		y[i] = temp->y;
		i++;
	}
	int j;
	for( j = 0; j < i; j = j+2 )
	{
		if( (( x[j] > nowx ) != ( x[j+1] > nowx)) 
		   && (nowx > ( x[j+1] - x[j]) * (nowy - y[j]) / (y[j+1] - y[j]) + x[j]) )
		   count++;
	}
	if( count % 2 != 0)
		chose = 1;
	//dbgS("ѡ�ж�����ж����\n");
}

double CalculateDistance_segement(void) {
	dbgS("��ʼ�����߶ξ���\n");
	Shape *sort;
	double sum = 0;
	int x1, y1, x2, y2;
	for ( sort = head; sort != NULL; sort = sort->next ) {
		struct Point *temp;
		if (sort->isChosen == 1 && sort->ty == 2) {
			temp = sort->pHead;
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
	for ( sort = head; sort != NULL; sort = sort->next ) {
		struct Point *temp;
		if (sort->isClicked == 1 && sort->ty == 0) {
			temp = sort->pHead;
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
	for ( sort = head; sort != NULL; sort = sort->next ) {
		struct Point *temp;
		if ( sort->isClicked == 1 && sort->ty == 2) {
			temp = sort->pHead;
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
		int temp_k = fabs(k[1] - k[0]);
		sum = atan(temp_k) * 180 / Pi;
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
	for ( sort = head; sort != NULL; sort = sort->next ) {
		struct Point *temp;
		if ( sort->isClicked == 1 && sort->ty == 3 ) {
			temp = sort->pHead;
			for (i = 0; i <= 80 && temp != NULL; i++) {
				x[i] = temp->x;
				y[i] = temp->y;
				temp = temp->next;
			}
			break;
		}
	}
	int j;
	for (j = 0; j <= i; j++) {
		if (j == i)
			j = -1;
		sum = sum + x[j] * y[j + 1] - x[j + 1] * y[j];
	}
	sum = 0.5 * fabs(sum);
	dbgS("��������������ɣ�");dbgD(sum);dbgC('\n');
	return sum;
}
