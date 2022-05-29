#include "Header.h"
#include "extgraph.h"
#include "selected.h"
#define MAX 100	//函数字符串最大长度
double point_r = 0.05;
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
		MovePen(5.2, 8);
		SetPointSize(70);
		SetPenColor("Navy");
		DrawTextString("几何画板");
		SetPointSize(25); 
		DrawImage("..\\5.bmp", 0, 0, 800, 533, 0,0, PixelsX(GetWindowWidth()), PixelsY(GetWindowHeight()));
		setButtonColors("Lightblue", "Slategray", "Lightblue", "Slategray", 1);
		if(button(GenUIID(0), 3, 5, 2.5, 1, "开始使用"))
		{
			dbgS("开始使用\n");
			pageid=2;
		}
		setButtonColors("Lightblue", "Navy", "Lightblue", "Slategray", 1);
		if(button(GenUIID(0), 9.5, 5, 2.5, 1 , "退出"))
		{
			exit(-1);
		}		
		//dbgS("窗口1绘制完成\n");
	}
	if(pageid==2)
	{
		//dbgS("开始绘制窗口2\n");
		DisplayClear();
		SetPointSize(15);
		setMenuColors("Lightblue", "Navy", "Lightblue", "Slategray", 1);
		if(button(GenUIID(0), 0.2, 9.7, 1, 0.5, "放大"))
		{
			scale += 0.02;
		}
		if(button(GenUIID(0), 0.2, 10.5, 1, 0.5, "缩小"))
		{
			scale-=0.02;
			if(scale <= 0.2)
			{
				scale = 0.2;
			}
		}
		if(button(GenUIID(0), 1.4, 10.1, 0.5, 0.5, "Left"))
		{
			centerX-=0.02;
			if(centerX <= Left_x)
			{
				centerX = Left_x;
			}
		}
		if(button(GenUIID(0), 2.0, 10.6, 0.5, 0.5, "Up"))
		{
			centerY+=0.02;
			if(centerY >= Right_y)
			{
				centerY = Right_y;
			}
		}
		if(button(GenUIID(0), 2.6, 10.1, 0.5, 0.5, "Right"))
		{
			centerX+=0.02;
			if(centerX >= Right_x)
			{
				centerX = Right_x;
			}
		}
		if(button(GenUIID(0), 2.0, 9.6, 0.5, 0.5, "Down"))
		{
			centerY-=0.02;
			if(centerY <= Left_y)
			{
				centerY = Left_y;
			}
		}
		static char * menuListFile[] = {"文件",
		                                "打开   | Ctrl-O", // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾
		                                "保存",
		                                "退出   | Ctrl-E"
		                               };
		static char * menuListTool[] = {"计算",
		                                "函数",
		                                "帮助 | Ctrl-T"
		                               };
		int selection  = menuList(GenUIID(0), 0, GetWindowHeight()-0.6, 1.5, 2.5, 0.6, menuListFile,sizeof(menuListFile)/sizeof(menuListFile[0]));
		int selection2 = menuList(GenUIID(0), 1.5, GetWindowHeight()-0.6, 1.5, 2.5, 0.6, menuListTool,sizeof(menuListTool)/sizeof(menuListTool[0]));
		drawedge();
		if(selection==1) read();
		if(selection==2) store();
		if(selection2==1)
		{
			pageid=3;
		}
		setButtonColors("Lightblue", "Navy", "Lightblue", "Slategray", 1);
		if(button(GenUIID(0), 4, 0.6, 1, 0.5, "点"))
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
		if(button(GenUIID(0), 5.8, 0.6, 1, 0.5, "直线"))
		{
			insert_state = 1; 
		}
		if(button(GenUIID(0), 7.8, 0.6, 1, 0.5, "线段"))
		{
			insert_state = 2;  
		}
		if(button(GenUIID(0), 9.8, 0.6, 1, 0.5, "多边形"))
		{
			insert_state = 3; 
		}
		if(button(GenUIID(0), 11.8, 0.6, 1, 0.5, "圆"))
		{
			insert_state = 4; 
		}
		if(button(GenUIID(0), 13.8, 0.6, 1, 0.5, "函数"))
		{
			pageid = 3;
		}
		
		drawtext();
		SetPenColor("Slategray");
		switch (insert_state) {
			case 0:
				drawLabel(4, 0.3, "在绘制区中按鼠标左键即可绘制点；点绘制完成后，请再次点击按钮，退出绘制点的功能");
				break;
			case 1:
				drawLabel(4, 0.3, "在绘制区中点击一次鼠标左键确定直线上一点，再次点击确定斜率，绘制直线；再次绘制需重新点击按钮");
				break;
			case 2:
				drawLabel(4, 0.3, "在绘制区中点击一次鼠标左键绘制线段一个端点，第二次点击绘制第二个端点并连接；再次绘制需重新点击按钮");
				break;
			case 3:
				drawLabel(4, 0.3, "在绘制区中点击一次鼠标左键绘制多边形的一个顶点，点击鼠标右键闭合多边形；再次绘制需重新点击按钮");
				break;
			case 4:
				drawLabel(4, 0.3, "在绘制区中点击一次鼠标左键确定圆的圆心，拉动鼠标确定半径，第二次点击绘制圆；再次绘制需重新点击按钮");
				break;
			case -1:
				drawLabel(4, 0.3, "点击相应的按钮进行绘制");
				break;
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
				SetPenColor("Navy");
				if(p->isChosen || p->isClicked == 1)
				{
					point_r = 0.08;
					SetPenColor("Shiningred");
				}
				
				DrawPoint(p->pHead->next->x, p->pHead->next->y);

				point_r = 0.05;
				//dbgS("点绘制完成\n");
			//	SetPenColor("Blue");
			}
			//绘制直线
			else if(p->ty == 1)	
			{
				cp = p->pHead->next;
				double i, cy, b;
				SetPenColor("Navy");
				if(!(cp->next)) 
				{
					DrawPoint(cp->x, cp->y);
					//dbgS("单个点情况\n");
				}
				else
				{
					if(p->isChosen || p->isClicked == 1)
					{
						point_r = 0.08;
						SetPenColor("Shiningred");
					}
					point_r = 0.05;
					DrawPoint(cp->x, cp->y);
					DrawPoint(cp->next->x, cp->next->y);
					if ((cp->y) == (cp->next->y)) {
						MovePen(Left_x,transferx(cp->y));
						DrawLine(0,10);
					}else if ((cp->x) == (cp->next->x)) {
						MovePen(transfery(cp->x),Left_y);
						DrawLine(10,0);
					} 
					else 
					{
						//dbgS("准备计算斜率\n");
						double slope;
						slope = (cp->next->y - cp->y) / (cp->next->x - cp->x);
						b = cp->y - slope * cp->x;
						//dbgS("斜率计算完成\n");
						int d = 1;
						for(i = -5/scale; i <= 5/scale; i += 0.1)
						{
							cy = i * slope + b;
							if(transfery(cy) < Left_y || transfery(cy) > Right_y) continue;
							if(d == 1)
							{
								MovePen(transferx(i), transfery(cy));
							}
							else DrawTo(i, cy);
							d++;
							dbgS("绘制直线次数：");dbgI(d);dbgC('\n');
						}
					} 
					
				}
				
			}
			//绘制线段
			else if(p->ty == 2)	
			{
				cp = p->pHead->next;
				SetPenColor("Navy");
				if(p->isChosen || p->isClicked == 1)
				{
					SetPenColor("Shiningred");
					point_r = 0.08;
				}
				if(cp->next)
				{
					DrawPoint(cp->x, cp->y);
					DrawTo(cp->next->x, cp->next->y);
					DrawPoint(cp->next->x, cp->next->y);
				}
				else
				{
					DrawPoint(cp->x, cp->y);
				}
				point_r = 0.05;
				//dbgS("线段绘制完成\n");
			}
			//绘制多边形
			else if(p->ty == 3)	
			{
				
				double hx, hy;
				SetPenColor("Navy");
				if(p->isChosen || p->isClicked == 1)
				{
					SetPenColor("Shiningred");
					point_r = 0.08;
				}
//				if(p->pHead->connect == -1)
//				{
//					dbgS("准备绘制已成立的多边形\n");
//					StartFilledRegion(0.5);
//					dbgS("进入填充状态\n");
//					for(cp = p->pHead->next; cp; cp = cp->next)
//					{
//						dbgS("-1进入绘制循环\n");
//						dbgS("connect:");dbgI(cp->connect);dbgC('\n');
//						if(cp->connect == 0)	
//						{
//							dbgS("-1准备绘制多边形头节点\n");
//							hx = cp->x;
//							hy = cp->y;
//							MovePen(transferx(hx),transfery(hy));
//						//	DrawPoint(cp->x, cp->y);
//						//	dbgS("多边形头节点绘制完成\n");
//						}
//						else if(cp->connect == 1)
//						{
//							DrawTo(cp->x, cp->y);
//						//	DrawPoint(cp->x, cp->y);
//							dbgS("-1多边形中间节点绘制完成\n");
//						}
//						else if(cp->connect == 2)
//						{
//							DrawTo(cp->x, cp->y);
//						//	DrawPoint(cp->x, cp->y);
//							//dbgS("多边形头节点坐标：");dbgD(hx);dbgD(hy);dbgC('\n');
//							DrawTo(hx, hy);
//							dbgS("-1绘制封闭线\n");
//							EndFilledRegion();
//						}
//					}
//					
//				}
//				else
//				{
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
							//dbgS("多边形中间节点绘制完成\n");
						}
						else if(cp->connect == 3)
						{
							DrawTo(cp->x, cp->y);
							DrawPoint(cp->x, cp->y);
						//	dbgS("多边形待定中间节点绘制完成\n");
						}
						else if(cp->connect == 2)
						{
							DrawTo(cp->x, cp->y);
							DrawPoint(cp->x, cp->y);
							//dbgS("多边形头节点坐标：");dbgD(hx);dbgD(hy);dbgC('\n');
							DrawTo(hx, hy);
						}
					}
//				}
			point_r = 0.05;
				
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
		setTextBoxColors("Rosered", "Rosered", "Salmon", "Rosered", 0);
		textbox(GenUIID(0), 3.5, 8, 8, 1, str, sizeof(str));
		
		SetPenColor("Navy");
		drawLabel(2, 5,"仅支持一元函数，未知量请输入x");
		drawLabel(2, 4.5,"支持常用的运算符输入，如： *   /   +   - ");
		drawLabel(2, 4,"字符之间不能存在空格");
		drawLabel(2, 3.5,"支持 π ,e，但 π 需要用Pi 或者 pi来表示");
		drawLabel(2, 3,"不支持 * 省略，需要使用2*x，2*( )等");
		if(button(GenUIID(0), 6.5, 6, 2, 1, "确认"))
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

void InitColor()
{
	DefineColor("Salmon", 0.99607, 0.84705, 0.705882);
	DefineColor("Navy", 0.086274, 0.207843, 0.341176);
	DefineColor("Cyan", 0.733333, 0.854901, 0.862745);
	DefineColor("Slategray", 0.203921, 0.51372, 0.58039);
	DefineColor("Lightyellow", 0.98039, 0.95686, 0.71372);
	DefineColor("Rosered", 0.8, 0.47058, 0.47058);
	DefineColor("Pink", 0.98823, 0.70980, 0.62352);
	DefineColor("Lightblue", 0.90588, 0.95686, 0.95294);
	DefineColor("Shiningred", 0.890196, 0.145098, 0.2470588);
}

void Main()
{
	//初始化窗口和图形系统
	SetWindowSize(15, 12);
	InitGraphics();
	initDebug();
	InitColor();
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

