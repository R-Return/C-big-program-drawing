#include "Header.h"
#define maxFunc 100	//函数字符串最大长度
int pageid=1;
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
			dbgS("选择“开始使用”按钮\n");
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
		
		//绘制
		Shape *p;
		int FuncColor;
		FuncColor = 0;
		for(p = head->next;p != end; p = p->next)
		{
			//绘制函数
			if(p->ty == 5)
			{
				double oy,cy;
				int interupt = 0;
				SetPenColor(Function_Color[FuncColor % 7]);
				d = 1;
				for(j=3;j<9.2;j+=0.05)
				{ 
					//dbgS( "绘画次数：");dbgI(d);dbgC('\n');
					change = 0;
					cy = transfer(p->f.function,j);
					if(change)
					{
						oy = cy;
						interupt = 1;
						continue;
					} 
					if((cy <= 0.5 || cy >= 7))
					{
						oy = cy;
						interupt = 1;
						continue;
					}
					if(d == 1 || interupt == 1)
					{
						oy = cy;
						MovePen(j,cy);
						interupt = 0;
					}
					else
					{
						DrawLine(0.05,cy-oy);
					}
					dbgS( "完成绘画次数：");dbgI(d);dbgC('\n');
					d++;
					oy=cy;
				}
				FuncColor ++;
				SetPenColor("Blue");
			}
		}
		
	}
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

