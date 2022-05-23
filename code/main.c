#include "Header.h"
int pageid=1;
char str[100]="" ;
static double j;
double cx,cy,ox,oy;

void CharEventProcess(char ch)
{
	uiGetChar(ch); /*获取字符*/
	display(); /*更新显示*/
}

void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); /*获取键盘*/
	display(); /*更新显示*/
}

void MouseEventProcess(int x, int y, int button, int event) {
	uiGetMouse(x, y, button, event);
	Shape *sh_chose;
	for ( sh_chose = head; sh_chose != NULL; sh_chose = sh_chose->next ) {
		switch (sh_chose->ty) {
			case 0:
				Select_Point(x, y, sh_chose->pHead);
			case 2:
				Select_Line(x, y, sh_chose->pHead);
			case 3:
				Select_Poly(x, y, sh_chose->pHead);
		}
		if (chose) {			//如果有选中的点或线 将struct中的chose变量置1
			sh_chose->isChosen = 1;
			display();
		}
		switch (event) {
			case BUTTON_DOWN:
				if (button == LEFT_BUTTON && chose)
					sh_chose->isClicked = -sh_chose->isClicked;
					display();
				break;
			case BUTTON_DOUBLECLICK:
				break;
			case BUTTON_UP:
				break;
			case MOUSEMOVE:
				break;
		}
	}

//	switch (button) {						//功能按钮选择
//		case 1:
//			distant_segement = CalculateDistance_segement();
//		case 2:
//			distant_point = CalculateDistance_point();
////		case 3:
////			degree_point = CalculateDegree_point();
//		case 3:
//			degree_segement = CalculateDegree_segement();
//		case 4:
//			area = Calculatearea_polygon();
//	}
//
//	display();
}

void display()
{
	//DisplayClear();	
	static int d = 1;
	static double j;
	if(pageid==1)
	{
		dbgS("开始绘制窗口1\n");
		MovePen(4,5);
		SetPointSize(50);
		DrawTextString("几何画板");
		SetPointSize(20); 
		if(button(GenUIID(0), 2, 1.5, 2, 1, "开始使用"))
		{
			pageid=2;
		}
		if(button(GenUIID(0), 6, 1.5, 2, 1 , "退出"))
		{
			exit(-1);
		}	
		dbgS("窗口1绘制完成\n");
	}
	if(pageid==2)
	{
		dbgS("开始绘制窗口2\n");
		DisplayClear();	
		static char * menuListFile[] = {"文件",
		                                "打开   | Ctrl-O", // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾
		                                "保存",
		                                "退出   | Ctrl-E"
		                               };
		static char * menuListTool[] = {"计算",
		                                "函数",
		                                "帮助 | Ctrl-T"
		                               };
		int selection  = menuList(GenUIID(0), 0, GetWindowHeight()-0.3 , 1, 1.5, 0.3, menuListFile,sizeof(menuListFile)/sizeof(menuListFile[0]));
		int selection2 = menuList(GenUIID(0), 1, GetWindowHeight()-0.3, 1, 1.5, 0.3, menuListTool,sizeof(menuListTool)/sizeof(menuListTool[0]));
		drawedge();
		if(selection2==1)
		{
			pageid=3;
		}
		
		if(button(GenUIID(0), 0.2, 5, 1, 0.5, "点"))
		{
			; 
		}
		if(button(GenUIID(0), 0.2, 4, 1, 0.5, "直线"))
		{
			; 
		}
		if(button(GenUIID(0), 0.2, 3, 1, 0.5, "多边形"))
		{
			; 
		}
		//DisplayClear();	
		oy=transfery(calculate(str,-4));
		ox=transferx(-4);
		MovePen(ox,oy);
		for(j=-4;j<4;j+=0.01)
		{ 
			dbgS( "绘画次数：");dbgI(d);dbgC('\n');
			cy=transfery(calculate(str,j));
			dbgS( "现在纵坐标是：");dbgD(cy);dbgC('\n');
			cx=transferx(j);
			dbgS( "现在横坐标是：");dbgD(cx);dbgC('\n');
			DrawLine(cx-ox,cy-oy);
			dbgS( "完成绘画次数：");dbgI(d);dbgC('\n');
			d++;
			ox=cx;
			oy=cy;
		}
	}
	if(pageid==3)
	{
		DisplayClear();	
		//calculate();
		textbox(GenUIID(0), 1, 5, 8, 0.5, str, sizeof(str));
		if(button(GenUIID(0), 1.5, 1.5, 2, 1, "确认"))
		{
			pageid=2;
		}
	if(pageid==4)
	{
		;
	}
	}
}

void Main()
{
	//初始化窗口和图形系统
	InitGraphics();
	initDebug();
	SetWindowTitle("几何画板");
	dbgS("开始运行\n");
	registerCharEvent(CharEventProcess);        // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	//registerTimerEvent(TimerEventProcess);      // 定时器
	centerX=6.1;
	centerY=4;
	scale=1;
	dbgS("全局变量初始化完成\n");
	display();
	//初始化链表
	//initLinkList();
	
	
}

