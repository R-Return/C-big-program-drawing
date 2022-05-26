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
			//dbgS("检测选中\n");
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
			if (chose) {			//如果有选中的点或线 将struct中的chose变量置1
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
		//绘制点、线、多边形
		switch(event)
		{
			case BUTTON_DOWN:
				if(insert_state == 0 && button == LEFT_BUTTON) 
				{
					insertPoint(0, 0, 0, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
					insert_state = -1;
					hasAdded = 0;
					dbgS("插点完成\n");
				}
				else if(insert_state == 2 && button == LEFT_BUTTON) 
				{
					if(hasAdded)
					{
						insertPoint(1, 2, 1, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
						insert_state = -1;
						hasAdded = 0;
						dbgS("线段插入完成\n");
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
						dbgS("准备插入多边形内端点\n");
						insertPoint(1, 3, 1, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
						dbgS("多边形内端点插入完成\n");
					}
					else
					{
						dbgS("准备插入多边形头端点\n");
						insertPoint(0, 3, 0, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
						hasAdded = 1;
						dbgS("多边形头端点插入完成\n");
					}
				}
				else if(insert_state == 3 && button == RIGHT_BUTTON)
				{
					dbgS("准备插入多边形尾端点\n");
					insertPoint(0, 3, 2, (mouse_x-centerX)/scale, (mouse_y-centerY)/scale);
					insert_state = -1;
					hasAdded = 0;
					dbgS("多边形尾端点插入完成\n");
				}
				else;
				break;
			default:
				break;
		}
	

//	switch (button) {						//功能按钮选择
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

//函数：选中点判断
//通过比较鼠标所在位置是否在点所在的误差范围之内，来判断是否选中状态
void Select_Point(int nowx, int nowy, struct Point *head) {
	dbgS("选中点判断\n");
	int r_point = 0.01;												//选中点的范围
	int d; 															//鼠标与遍历到点的距离
	d = pow( nowx - head->x, 2 ) + pow( nowy - head->y, 2);
	if ( pow(d, 0.5) <= r_point ) {
		chose = 1;												//sh->chosen
	}
	dbgS("选中点判断完成\n");
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

//选中线段判断
//通过比较线段斜率与鼠标所在位置形成的斜率，是否在误差范围之内，来判断是否选中状态
void Select_Line(int nowx, int nowy, struct Point *head) {
	dbgS("选中线段判断\n");
	double slope, nowslope, error = 0.001;							//选取容许误差
	int x1, y1, x2, y2;												//线段两个端点的坐标
	x1 = head->x;
	y1 = head->y;
	head = head->next;
	x2 = head->x;
	y2 = head->y;
	slope = (y2 - y1) / (x2 - x1);									//当前线段的斜率
	nowslope = (nowy - y1) / (nowx - x1);								//鼠标所在位置与端点形成斜率
	if ( (nowslope = slope + error) && (nowslope = slope - error) ) {
		chose = 1;
	}
	dbgS("选中线段判断完成\n");
}

void Select_Poly(int nowx, int nowy, struct Point *head) {
	//dbgS("选中多边形判断\n");
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
	//dbgS("选中多边形判断完成\n");
}

double CalculateDistance_segement(void) {
	dbgS("开始计算线段距离\n");
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
	dbgS("线段距离计算完成，距离为：");dbgD(sum);dbgC('\n');
	return sum;
}

// 如果sum返回的值不等于0 代表已经选中两个点 并计算距离 （timer时间显示后） 这时将选中参数全部置1 为下一次计算做准备
// 以下三个函数用相同的方法
double CalculateDistance_point(void) {
	dbgS("开始计算两点距离\n");
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
	dbgS("两点距离计算完成，距离为：");dbgD(sum);dbgC('\n');
	return sum;
}

//double CalculateDegree_point(void) {
//	dbgS("开始计算角度\n");
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
//	dbgS("角度计算完成：");dbgD(sum);dbgC('\n');
//	return sum;
//}

double CalculateDegree_segement(void) {
	dbgS("开始计算角度\n");
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
	dbgS("角度计算完成：");dbgD(sum);dbgC('\n');
	return sum;
}

double Calculatearea_polygon(void) {
	dbgS("开始计算多边形面积\n");
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
	dbgS("多边形面积计算完成：");dbgD(sum);dbgC('\n');
	return sum;
}
