#include "Header.h"
#define maxFunc 100	//�����ַ�����󳤶�
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
		//dbgS("��ʼ���ƴ���1\n");
		MovePen(4,5);
		SetPointSize(50);
		DrawTextString("���λ���");
		SetPointSize(20); 
		if(button(GenUIID(0), 2, 1.5, 2, 1, "��ʼʹ��"))
		{
			dbgS("��ʼʹ��\n");
			pageid=2;
		}
		if(button(GenUIID(0), 6, 1.5, 2, 1 , "�˳�"))
		{
			exit(-1);
		}	
		//dbgS("����1�������\n");
	}
	if(pageid==2)
	{
		//dbgS("��ʼ���ƴ���2\n");
		DisplayClear();
		static char * menuListFile[] = {"�ļ�",
		                                "��   | Ctrl-O", // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
		                                "����",
		                                "�˳�   | Ctrl-E"
		                               };
		static char * menuListTool[] = {"����",
		                                "����",
		                                "���� | Ctrl-T"
		                               };
		int selection  = menuList(GenUIID(0), 0, GetWindowHeight()-0.3 , 1, 1.5, 0.3, menuListFile,sizeof(menuListFile)/sizeof(menuListFile[0]));
		int selection2 = menuList(GenUIID(0), 1, GetWindowHeight()-0.3, 1, 1.5, 0.3, menuListTool,sizeof(menuListTool)/sizeof(menuListTool[0]));
		drawedge();
		if(selection2==1)
		{
			pageid=3;
		}
		
		if(button(GenUIID(0), 0.2, 5, 1, 0.5, "��"))
		{
			insert_point_state = 1; 
		}
		if(button(GenUIID(0), 0.2, 4, 1, 0.5, "�߶�"))
		{
			insert_point_state = 1; 
		}
		if(button(GenUIID(0), 0.2, 3, 1, 0.5, "�����"))
		{
			insert_point_state = 1; 
		}
		//DisplayClear();	
		
		//����
		Shape *p;
		struct Point *cp;
		int FuncColor;
		int opposite = 0;
		FuncColor = 0;
		for(p = head->next;p != end; p = p->next)
		{
			//���Ƶ�
			if(p->ty == 0)
			{
				SetPenColor("Red");
				MovePen(p->pHead->next->x, p->pHead->next->y);
				StartFilledRegion(0.8);
				DrawArc(point_r, 0, 360);
				EndFilledRegion();
				dbgS("��������\n");
			}
			
			//���ƺ���
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
				dbgS("������ɴ�����");dbgI(d);dbgC('\n');
			}//if �������ƽ���
			
			//���ƺ������ʽ
//			MovePen(0.5,0.5);
//			DrawTextString(fHead->next->func);
		}//for
		
	}//if
	if(pageid==3)
	{
		DisplayClear();	
		//calculate();
		textbox(GenUIID(0), 1, 5, 8, 0.5, str, sizeof(str));
		if(button(GenUIID(0), 1.5, 1.5, 2, 1, "ȷ��"))
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
	uiGetChar(ch); /*��ȡ�ַ�*/
	display(); /*������ʾ*/
}

void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); /*��ȡ����*/
	display(); /*������ʾ*/
}

void Main()
{
	//��ʼ�����ں�ͼ��ϵͳ
	InitGraphics();
	initDebug();
	SetWindowTitle("���λ���");
	dbgS("��ʼ����\n");
	registerCharEvent(CharEventProcess);        // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	//registerTimerEvent(TimerEventProcess);      // ��ʱ��
//	centerX=6.1;
//	centerY=4;
//	scale=1;
	str[0]='\0';
	dbgS("ȫ�ֱ�����ʼ�����\n");
	display();
	//��ʼ������
	initLinkList();
}

