#define Pi 3.1415926
static int chose = 0;												//�жϵ��ߵ��Ƿ�ѡ�еĲ��� ����ʼ��0Ϊδѡ�� 
static double distant_segement;										//�����߶γ��� 
static double distant_point;
static double degree_point;
static double degree_segement;
static double area;
// static Shape *shead
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);
	struct Shape *sh_chose;
	for( sh_chose = shead; sh_chose != NULL; sh_chose = sh_chose->next )					//*shead
	{
		switch(sh_chose->ty)
		{
			case 0: Select_Point(x, y, sh_chose->head);
			case 2: Select_Line(x, y, sh_chose->head);
			case 3: Select_Poly(x, y, sh_chose->head);
		}
		if(chose)													//�����ѡ�еĵ���� ��struct�е�chose������1 
		{
			sh_chose->chosen = 1;
		}
		switch(event)
		{
			case BUTTON_DOWN:
				if (button == LEFT_BUTTON && chose)
					sh_chose->click = -sh_chose->click;
				break;
			case BUTTON_DOUBLECLICK:
				break;
			case BUTTON_UP:
				break;
			case MOUSEMOVE:
				break;
		}
	}
	
	switch(button)													//���ܰ�ťѡ�� 
	{
		case 1: distant_segement = CalculateDistance_segement();
		case 2: distant_point = CalculateDistance_point();
		case 3: degree_point = CalculateDegree_point();
		case 4: degree_segement = CalculateDegree_segement();
		case 5: area = Calculatearea_polygon();
	}	
	
	display();
}

//������ѡ�е��ж� 
//ͨ���Ƚ��������λ���Ƿ��ڵ����ڵ���Χ֮�ڣ����ж��Ƿ�ѡ��״̬
void Select_Point(int nowx, int nowy, struct Point *head)
{
	int r_point = 0.01;												//ѡ�е�ķ�Χ 
	int d; 															//������������ľ��� 
	d = pow( nowx - head->x, 2 ) + pow( nowy - head->y, 2);
	if ( pow(d, 0.5) <= r_point )
	{
		chose = 1;												//sh->chosen
	}
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
void Select_Line(int nowx, int nowy, struct Point *head)
{
	double slope, nowslope, error = 0.001;							//ѡȡ������� 
	int x1, y1, x2, y2;												//�߶������˵������ 
	x1 = head->x;
	y1 = head->y;
	head = head->next;
	x2 = head->x;
	y2 = head->y;
	slope = (y2 - y1)/(x2 - x1);									//��ǰ�߶ε�б��										
	nowslope = (nowy - y1)/(nowx - x1);								//�������λ����˵��γ�б�� 
	if( (nowslope = slope + error) && (nowslope = slope - error) )
	{
		chose = 1;
	}
}

void Select_Poly(int nowx, int nowy, struct Point *head)
{
	int x[80], y[80];
	struct Point *temp;
	int count = 0;
	
	
}

double CalculateDistance_segement(void)
{
	struct Shape *sort;
	double sum = 0;
	int x1, y1, x2, y2;	
	for( sort = shead; sort != NULL; sort = sort->next )
	{
		struct Point *temp;
		if(sort->chosen == 1 && sort->ty == 2)
		{
			temp = sort->head;
			x1 = temp->x;
			y1 = temp->y;
			temp = temp->next;
			x2 = temp->x;
			y2 = temp->y;
			sum = pow(pow(x2 - x1, 2) + pow(y2 - y1, 2), 0.5);
			break;
		}
	}
	return sum;
}

// ���sum���ص�ֵ������0 �����Ѿ�ѡ�������� ��������� ��timerʱ����ʾ�� ��ʱ��ѡ�в���ȫ����1 Ϊ��һ�μ�����׼�� 
// ����������������ͬ�ķ��� 
double CalculateDistance_point(void)
{
	struct Shape *sort;
	double sum;
	int x[2], y[2];
	int count = 0;
	for( sort = shead; sort != NULL; sort = sort->next )
	{
		struct Point *temp;
		if(sort->click == 1 && sort->ty == 0)
		{
			temp = sort->head;
			x[count] = head->x;
			y[count] = head->y;
			count++;
		}
	}
	if(x[0] != 0 && x[1] != 0)
	{
		sum = pow(pow(x[1] - x[0], 2) + pow(y[1] - y[0], 2), 0.5);
	}
	return sum;
}

double CalculateDegree_point(void)
{
	struct Shape *sort;
	double sum = 0;
	int x[2], y[2];
	int count = 0;
	for( sort = shead; sort != NULL; sort = sort->next )
	{
		struct Point *temp;
		if( sort->click == 1 && sort->ty == 0 )
		{
			temp = sort->head;
			x[count] = temp->x;
			y[count] = temp->y;
			count++;
		}
	}
	if( x[0] != 0 && x[1] != 0 )
	{
		int k = (y2 - y1)/(x2 - x1);
		sum = atan(k) * 180 / Pi;
	}
	return sum;
}

double CalculateDegree_segement(void)
{
	struct Shape *sort;
	double sum = 0; 
	double k[2];
	int count = 0;
	int x1, y1, x2, y2;
	for( sort = shead; sort != NULL; sort = sort->next )
	{
		struct Point *temp;
		if( sort->click == 1 && sort->ty == 2)
		{
			temp = sort->head;
			x1 = temp->x;
			y1 = temp->y;
			temp = temp->next;
			x2 = temp->x;
			y2 = temp->y;
			k[count] = (y2 - y1)/(x2 - x1);
			count++;
		}
	}
	if( k[0] != 0 && k[1] != 0)
	{
		int k = fabs(k[1] - k[0]);
		sum = atan(k) * 180 / Pi;
	}
	return sum;
}

double Calculatearea_polygon(void)
{
	struct Shape *sort;
	double sum = 0;
	int x[80], y[80];
	int i;
	for( sort = shead; sort != NULL; sort = sort->next )
	{
		struct Point *temp;
		if( sort->click == 1 && sort->ty == 3 )
		{
			temp = sort->head;
			for(i = 0; i<= 80 && temp != NULL; i++)
			{
				x[i] = temp->x;
				y[i] = temp->y;
				temp = temp->next;
			}
			break;
		}
	}
	for(int j = 0; j <= i; j++)
	{
		if(j == i)
			j = -1;
		sum = sum + x[j] * y[j+1] - x[j+1] * y[j];
	}
	sum = 0.5 * fabs(sum);
	return sum;
}