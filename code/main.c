#include "Header.h"
#include "extgraph.h"
#define MAX 100	//�����ַ�����󳤶�
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
		//dbgS("��ʼ���ƴ���1\n");
		MovePen(4,5);
		SetPointSize(50);
		DrawImage("..\\1.bmp", 0, 0, 879, 526, 0,0, PixelsX(GetWindowWidth()), PixelsY(GetWindowHeight()));
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
		
		if(button(GenUIID(0), 0.2, 8, 1, 0.5, "��"))
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
		if(button(GenUIID(0), 0.2, 7, 1, 0.5, "ֱ��"))
		{
			insert_state = 1; 
		}
		if(button(GenUIID(0), 0.2, 6, 1, 0.5, "�߶�"))
		{
			insert_state = 2;  
		}
		if(button(GenUIID(0), 0.2, 5, 1, 0.5, "�����"))
		{
			insert_state = 3; 
		}
		if(button(GenUIID(0), 0.2, 4, 1, 0.5, "Բ"))
		{
			insert_state = 4; 
		}
		if(button(GenUIID(0), 0.2, 3, 1, 0.5, "����"))
		{
			pageid = 3;
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
				DrawPoint(p->pHead->next->x, p->pHead->next->y);
				//dbgS("��������\n");
			}
			//�����߶�
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
				//dbgS("�߶λ������\n");
			}
			//���ƶ����
			else if(p->ty == 3)	
			{
				
				double hx, hy;
				if(p->pHead->connect == -1)
				{
					dbgS("׼�������ѳ����Ķ����\n");
					StartFilledRegion(0.5);
					dbgS("�������״̬\n");
					for(cp = p->pHead->next; cp; cp = cp->next)
					{
						dbgS("�������ѭ��\n");
						dbgS("connect:");dbgI(cp->connect);dbgC('\n');
						if(cp->connect == 0)	
						{
							dbgS("׼�����ƶ����ͷ�ڵ�\n");
							hx = cp->x;
							hy = cp->y;
							MovePen(transferx(hx),transfery(hy));
						//	DrawPoint(cp->x, cp->y);
						//	dbgS("�����ͷ�ڵ�������\n");
						}
						else if(cp->connect == 1)
						{
							DrawTo(cp->x, cp->y);
						//	DrawPoint(cp->x, cp->y);
							dbgS("������м�ڵ�������\n");
						}
						else if(cp->connect == 2)
						{
							DrawTo(cp->x, cp->y);
						//	DrawPoint(cp->x, cp->y);
							//dbgS("�����ͷ�ڵ����꣺");dbgD(hx);dbgD(hy);dbgC('\n');
							DrawTo(hx, hy);
							dbgS("���Ʒ����\n");
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
						//	dbgS("׼�����ƶ����ͷ�ڵ�\n");
							hx = cp->x;
							hy = cp->y;
							DrawPoint(cp->x, cp->y);
						//	dbgS("�����ͷ�ڵ�������\n");
						}
						else if(cp->connect == 1)
						{
							DrawTo(cp->x, cp->y);
							DrawPoint(cp->x, cp->y);
						//	dbgS("������м�ڵ�������\n");
						}
						else if(cp->connect == 3)
						{
							DrawTo(cp->x, cp->y);
							DrawPoint(cp->x, cp->y);
						//	dbgS("����δ����м�ڵ�������\n");
						}
					}
				}
				
			}
			//����Բ
			else if(p->ty == 4)
			{
				MovePen(transferx(p->c.x + p->c.r * scale), transfery(p->c.y));
				DrawArc(p->c.r * scale, 0, 360);
				//dbgS("Բ�������\n");
			}
			//���ƺ���
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
					//dbgS("������ɴ�����");dbgI(d);dbgC('\n');
				}//for
				FuncColor ++;
				SetPenColor("Blue");
				//dbgS("������ɴ�����");dbgI(d);dbgC('\n');
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
	SetWindowSize(15, 12);
	InitGraphics();
	initDebug();
	SetWindowTitle("���λ���");
	dbgS("��ʼ����\n");
	registerCharEvent(CharEventProcess);        // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	//registerTimerEvent(TimerEventProcess);      // ��ʱ��
	centerX=(Left_x +Right_x)/2;
	centerY=(Left_y +Right_y)/2;
	dbgS("ȫ�ֱ�����ʼ�����\n");
	display();
	//��ʼ������
	initLinkList();
}

