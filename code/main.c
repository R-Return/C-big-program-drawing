#include "Header.h"
#define maxFunc 100	//函数字符串最大长度
#define point_r 0.05
int pageid=1;
int insert_point_state = 0, insert_segment_state = 0, insert_polygon_state = 0;
double centerX=6.1, centerY=4, scale=1;
char str[maxFunc] = "";
char *Function_Color[]={"Dark Gray", "Red", "Green",  
						"Cyan", "Blue", "Magenta"};

void display()
{
	int d;
	double j;
	if(pageid==1)
	{
		//dbgS("开始绘制窗口1\n");
		MovePen(4,5);
		SetPointSize(50);
		DrawTextString("几何画板");
		SetPointSize(20); 
		if(button(GenUIID(0), 2, 1.5, 2, 1, "开始使用"))
		{
			dbgS("开始使用\n");
			pageid=2;
		}
		if(button(GenUIID(0), 6, 1.5, 2, 1 , "退出"))
		{
			exit(-1);
		}	
		//dbgS("窗口1绘制完成\n");
	}
	if(pageid==2)
	{
		//dbgS("开始绘制窗口2\n");
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
			insert_point_state = 1; 
		}
		if(button(GenUIID(0), 0.2, 4, 1, 0.5, "线段"))
		{
			insert_point_state = 1; 
		}
		if(button(GenUIID(0), 0.2, 3, 1, 0.5, "多边形"))
		{
			insert_point_state = 1; 
		}
		//DisplayClear();	
		
		//绘制
		Shape *p;
		struct Point *cp;
		int FuncColor;
		int opposite = 0;
		FuncColor = 0;
		for(p = head->next;p != end; p = p->next)
		{
			//绘制点
			if(p->ty == 0)
			{
				SetPenColor("Red");
				MovePen(p->pHead->next->x, p->pHead->next->y);
				StartFilledRegion(0.8);
				DrawArc(point_r, 0, 360);
				EndFilledRegion();
				dbgS("点绘制完成\n");
			}
			
			//绘制函数
			if(p->ty == 5)
			{
				double x,y;
				SetPenColor(Function_Color[FuncColor % 7]);
				int d = 1;
				
				for(cp = p->pHead->next; cp->next; cp = cp->next)
				{
					if(!cp->connect)
					{
						opposite = 1;
					}
					x = transferx(cp->x);
					y = transfery(cp->y);
					if(x < 3 || x >9.2 || y < 0.5 || y > 7) continue;
					if(opposite == 1)	
					{
						MovePen(x, y);
						opposite = 0;
					}
					else if(d == 1)	MovePen(x, y);
					else	
					{
						DrawTo(x, y);
					}
					d ++;
				}//for
				FuncColor ++;
				SetPenColor("Blue");
				dbgS("绘制完成次数：");dbgI(d);dbgC('\n');
			}//if 函数绘制结束
			
			//绘制函数表达式
//			MovePen(0.5,0.5);
//			DrawTextString(fHead->next->func);
		}//for
		
	}//if
	if(pageid==3)
	{
		DisplayClear();	
		//calculate();
		textbox(GenUIID(0), 1, 5, 8, 0.5, str, sizeof(str));
		if(button(GenUIID(0), 1.5, 1.5, 2, 1, "确认"))
		{
			insertFunc(str);
			str[0] = '\0';
			pageid=2;
		}
	if(pageid==4)
	{
		;
	}
	}
}

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
//	centerX=6.1;
//	centerY=4;
//	scale=1;
	str[0]='\0';
	dbgS("全局变量初始化完成\n");
	display();
	//初始化链表
	initLinkList();
}

