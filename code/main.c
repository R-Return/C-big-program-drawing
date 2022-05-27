#include "Header.h"
#include "extgraph.h"
#define MAX 100	//函数字符串最大长度
#define point_r 0.05
int pageid=1;
int insert_state = -1;
double Left_x = 4, Left_y = 1.5, Right_x = 14, Right_y = 11.5;
double centerX, centerY, scale=1;
char str[MAX] = "";
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
		DrawImage("..\\1.bmp", 0, 0, 879, 526, 0,0, PixelsX(GetWindowWidth()), PixelsY(GetWindowHeight()));
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
		
		if(button(GenUIID(0), 0.2, 8, 1, 0.5, "点"))
		{
			 
			if(insert_state == 0)
			{
				insert_state = -1;
			}
			else
			{
				insert_state = 0;
			}
		}
		if(button(GenUIID(0), 0.2, 7, 1, 0.5, "直线"))
		{
			insert_state = 1; 
		}
		if(button(GenUIID(0), 0.2, 6, 1, 0.5, "线段"))
		{
			insert_state = 2;  
		}
		if(button(GenUIID(0), 0.2, 5, 1, 0.5, "多边形"))
		{
			insert_state = 3; 
		}
		if(button(GenUIID(0), 0.2, 4, 1, 0.5, "圆"))
		{
			insert_state = 4; 
		}
		if(button(GenUIID(0), 0.2, 3, 1, 0.5, "函数"))
		{
			pageid = 3;
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
				DrawPoint(p->pHead->next->x, p->pHead->next->y);
				//dbgS("点绘制完成\n");
			}
			//绘制线段
			else if(p->ty == 2)	
			{
				cp = p->pHead->next;
				if(cp->next)
				{
					DrawPoint(cp->x, cp->y);
					DrawSegment(cp->x, cp->y, cp->next->x, cp->next->y);
				}
				else
				{
					DrawPoint(cp->x, cp->y);
				}
				//dbgS("线段绘制完成\n");
			}
			//绘制多边形
			else if(p->ty == 3)	
			{
				
				double hx, hy;
				if(p->pHead->connect == -1)
				{
					dbgS("准备绘制已成立的多边形\n");
					StartFilledRegion(0.5);
					dbgS("进入填充状态\n");
					for(cp = p->pHead->next; cp; cp = cp->next)
					{
						dbgS("进入绘制循环\n");
						dbgS("connect:");dbgI(cp->connect);dbgC('\n');
						if(cp->connect == 0)	
						{
							dbgS("准备绘制多边形头节点\n");
							hx = cp->x;
							hy = cp->y;
							MovePen(transferx(hx),transfery(hy));
						//	DrawPoint(cp->x, cp->y);
						//	dbgS("多边形头节点绘制完成\n");
						}
						else if(cp->connect == 1)
						{
							DrawTo(cp->x, cp->y);
						//	DrawPoint(cp->x, cp->y);
							dbgS("多边形中间节点绘制完成\n");
						}
						else if(cp->connect == 2)
						{
							DrawTo(cp->x, cp->y);
						//	DrawPoint(cp->x, cp->y);
							//dbgS("多边形头节点坐标：");dbgD(hx);dbgD(hy);dbgC('\n');
							DrawTo(hx, hy);
							dbgS("绘制封闭线\n");
							EndFilledRegion();
						}
					}
					
				}
				else
				{
					for(cp = p->pHead->next; cp; cp = cp->next)
					{
						if(cp->connect == 0)	
						{
						//	dbgS("准备绘制多边形头节点\n");
							hx = cp->x;
							hy = cp->y;
							DrawPoint(cp->x, cp->y);
						//	dbgS("多边形头节点绘制完成\n");
						}
						else if(cp->connect == 1)
						{
							DrawTo(cp->x, cp->y);
							DrawPoint(cp->x, cp->y);
						//	dbgS("多边形中间节点绘制完成\n");
						}
						else if(cp->connect == 3)
						{
							DrawTo(cp->x, cp->y);
							DrawPoint(cp->x, cp->y);
						//	dbgS("多边形待定中间节点绘制完成\n");
						}
					}
				}
				
			}
			//绘制圆
			else if(p->ty == 4)
			{
				MovePen(transferx(p->c.x + p->c.r * scale), transfery(p->c.y));
				DrawArc(p->c.r * scale, 0, 360);
				//dbgS("圆绘制完成\n");
			}
			//绘制函数
			else if(p->ty == 5)
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
					if(x < Left_x || x > Right_x || y < Left_y || y > Right_y) continue;
					if(opposite == 1)	
					{
						MovePen(x, y);
						opposite = 0;
					}
					else if(d == 1)	MovePen(x, y);
					else	
					{
						DrawTo(cp->x, cp->y);
					}
					d ++;
					//dbgS("绘制完成次数：");dbgI(d);dbgC('\n');
				}//for
				FuncColor ++;
				SetPenColor("Blue");
				//dbgS("绘制完成次数：");dbgI(d);dbgC('\n');
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
	SetWindowSize(15, 12);
	InitGraphics();
	initDebug();
	SetWindowTitle("几何画板");
	dbgS("开始运行\n");
	registerCharEvent(CharEventProcess);        // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	//registerTimerEvent(TimerEventProcess);      // 定时器
	centerX=(Left_x +Right_x)/2;
	centerY=(Left_y +Right_y)/2;
	dbgS("全局变量初始化完成\n");
	display();
	//初始化链表
	initLinkList();
}

