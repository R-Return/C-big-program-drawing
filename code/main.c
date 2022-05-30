#include "Header.h"
#include "extgraph.h"
#include "selected.h"
#define MAX 100	//�����ַ�����󳤶�
double point_r = 0.05;
int pageid=1;
int insert_state = -1;
double Left_x = 4, Left_y = 1.5, Right_x = 14, Right_y = 11.5;
double centerX, centerY, scale=1;
char str[MAX] = "";
char *Function_Color[]={"BlueGray", "FuncRed", "vividGreen",  
						"FuncBlue",  "FuncOrange"};

void display()
{
	int d;
	double j;
	if(pageid==1)
	{
		//dbgS("��ʼ���ƴ���1\n");
		DrawImage("..\\5.bmp", 0, 0, 800, 533, 0,0, PixelsX(GetWindowWidth()), PixelsY(GetWindowHeight()));
		SetFont("����");
		MovePen(4, 8.6);
		SetPointSize(80);
		SetPenColor("Navy");
		DrawTextString("�� �� �� ��");
		SetPointSize(30); 
		
		setButtonColors("Lightblue", "Slategray", "Lightblue", "Slategray", 1);
		if(button(GenUIID(0), 9.5, 5, 2.5, 1, "��ʼʹ��"))
		{
			dbgS("��ʼʹ��\n");
			pageid=2;
		}
		setButtonColors("Lightblue", "Navy", "Lightblue", "Slategray", 1);
		if(button(GenUIID(0), 9.5, 3, 2.5, 1 , "�˳�"))
		{
			exit(-1);
		}		
		//dbgS("����1�������\n");
	}
	if(pageid==2)
	{
		//dbgS("��ʼ���ƴ���2\n");
		DisplayClear();
		SetPointSize(20);
		setMenuColors("Lightblue", "Navy", "Lightblue", "Slategray", 1);
		if(button(GenUIID(0), 0.2, 9.7, 1, 0.5, "�Ŵ�"))
		{
			scale += 0.02;
		}
		if(button(GenUIID(0), 0.2, 10.5, 1, 0.5, "��С"))
		{
			scale-=0.02;
			if(scale <= 0.2)
			{
				scale = 0.2;
			}
		}
		SetPointSize(15); 
		if(button(GenUIID(0), 1.5, 10.1, 0.6, 0.5, "Left"))
		{
			centerX-=0.02;
			if(centerX <= Left_x)
			{
				centerX = Left_x;
			}
		}
		if(button(GenUIID(0), 2.2, 10.7, 0.6, 0.5, "Up"))
		{
			centerY+=0.02;
			if(centerY >= Right_y)
			{
				centerY = Right_y;
			}
		}
		if(button(GenUIID(0), 2.9, 10.1, 0.6, 0.5, "Right"))
		{
			centerX+=0.02;
			if(centerX >= Right_x)
			{
				centerX = Right_x;
			}
		}
		if(button(GenUIID(0), 2.2, 9.55, 0.6, 0.5, "Down"))
		{
			centerY-=0.02;
			if(centerY <= Left_y)
			{
				centerY = Left_y;
			}
		}
		
		MovePen(4.2, 11.6);
		char s[10];
		sprintf(s, "x %.2f", scale);
		SetPenColor("Navy");
		SetPointSize(30); 
		DrawTextString(s);
		SetPointSize(20); 
		
		static char * menuListFile[] = {"�ļ�",
		                                "��   | Ctrl-O", // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
		                                "����",
		                                "�˳�   | Ctrl-E"
		                               };
		static char * menuListTool[] = {"����",
		                                "����",
		                                "���� | Ctrl-T"
		                               };
		int selection  = menuList(GenUIID(0), 0, GetWindowHeight()-0.6, 1.5, 2.5, 0.6, menuListFile,sizeof(menuListFile)/sizeof(menuListFile[0]));
		int selection2 = menuList(GenUIID(0), 1.5, GetWindowHeight()-0.6, 1.5, 2.5, 0.6, menuListTool,sizeof(menuListTool)/sizeof(menuListTool[0]));
		drawedge();
		if(selection==1) read();
		if(selection==2) store();
		if(selection==3) exit(-1);
		if(selection2==1)
		{
			pageid=3;
		}
		setButtonColors("Lightblue", "Navy", "Lightblue", "Slategray", 1);
		if(button(GenUIID(0), 4, 0.6, 0.8, 0.5, "��"))
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
		if(button(GenUIID(0), 5.2, 0.6, 0.8, 0.5, "ֱ��"))
		{
			insert_state = 1; 
		}
		if(button(GenUIID(0), 6.4, 0.6, 0.8, 0.5, "�߶�"))
		{
			insert_state = 2;  
		}
		if(button(GenUIID(0), 7.6, 0.6, 0.8, 0.5, "�����"))
		{
			insert_state = 3; 
		}
		if(button(GenUIID(0), 8.8, 0.6, 0.8, 0.5, "Բ"))
		{
			insert_state = 4; 
		}
		if(button(GenUIID(0), 10, 0.6, 0.8, 0.5, "����"))
		{
			pageid = 3;
		}
		setButtonColors("Salmon", "Shiningred", "Pink", "Shiningred", 1);
		if(button(GenUIID(0), 11.4, 0.6, 0.8, 0.5, "����"))
		{
			head->next = end;
			end->before = head;
		}
		setButtonColors("Lightblue", "Navy", "Lightblue", "Slategray", 1);
		drawtext();
		SetPointSize(15); 
		SetPenColor("Slategray");
		switch (insert_state) {
			case 0:
				drawLabel(4, 0.3, "�ڻ������а����������ɻ��Ƶ㣻�������ɺ����ٴε����ť���˳����Ƶ�Ĺ���");
				break;
			case 1:
				drawLabel(4, 0.3, "�ڻ������е��һ��������ȷ��ֱ����һ�㣬�ٴε��ȷ��б�ʣ�����ֱ�ߣ��ٴλ��������µ����ť");
				break;
			case 2:
				drawLabel(4, 0.3, "�ڻ������е��һ�������������߶�һ���˵㣬�ڶ��ε�����Ƶڶ����˵㲢���ӣ��ٴλ��������µ����ť");
				break;
			case 3:
				drawLabel(4, 0.3, "�ڻ������е��һ�����������ƶ���ε�һ�����㣬�������Ҽ��պ϶���Σ��ٴλ��������µ����ť");
				break;
			case 4:
				drawLabel(4, 0.3, "�ڻ������е��һ��������ȷ��Բ��Բ�ģ��������ȷ���뾶���ڶ��ε������Բ���ٴλ��������µ����ť");
				break;
			case -1:
				drawLabel(4, 0.3, "�����Ӧ�İ�ť���л���");
				break;
		}
		SetPointSize(20); 
		//DisplayClear();	
		
		//dbgS("��ʼ����\n");
		//����
		SetPenSize(2);
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
				SetPenColor("Navy");
				if(p->isChosen || p->isClicked == 1)
				{
					point_r = 0.08;
					SetPenColor("Shiningred");
				}
				
				DrawPoint(p->pHead->next->x, p->pHead->next->y);

				point_r = 0.05;
				dbgS("��������\n");
			//	SetPenColor("Blue");
			}
			//����ֱ��
			else if(p->ty == 1)	
			{
				cp = p->pHead->next;
				double i, cy, b;
				SetPenColor("Navy");
				if(!(cp->next)) 
				{
					DrawPoint(cp->x, cp->y);
					//dbgS("���������\n");
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
						//dbgS("׼������б��\n");
						double slope;
						slope = (cp->next->y - cp->y) / (cp->next->x - cp->x);
						b = cp->y - slope * cp->x;
						//dbgS("б�ʼ������\n");
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
							//dbgS("����ֱ�ߴ�����");dbgI(d);dbgC('\n');
						}
					} 
					
				}
				
			}
			//�����߶�
			else if(p->ty == 2)	
			{
				//dbgS("��ʼ�����߶�\n");
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
				//dbgS("�߶λ������\n");
			}
			//���ƶ����
			else if(p->ty == 3)	
			{
				
				double hx, hy;
				SetPenColor("Navy");
				if(p->isChosen == 1 || p->isClicked == 1)
				{
					SetPenColor("Shiningred");
					point_r = 0.08;
				}

					for(cp = p->pHead->next; cp; cp = cp->next)
					{
						if(cp->connect == 0)	
						{
							//dbgS("׼�����ƶ����ͷ�ڵ�\n");
							hx = cp->x;
							hy = cp->y;
							DrawPoint(cp->x, cp->y);
							//dbgS("�����ͷ�ڵ�������\n");
						}
						else if(cp->connect == 1)
						{
							DrawTo(cp->x, cp->y);
							DrawPoint(cp->x, cp->y);
							//dbgS("������м�ڵ�������\n");
						}
						else if(cp->connect == 3)
						{
							DrawTo(cp->x, cp->y);
							DrawPoint(cp->x, cp->y);
							//dbgS("����δ����м�ڵ�������\n");
						}
						else if(cp->connect == 2)
						{
							DrawTo(cp->x, cp->y);
							DrawPoint(cp->x, cp->y);
							//dbgS("�����ͷ�ڵ����꣺");dbgD(hx);dbgD(hy);dbgC('\n');
							DrawTo(hx, hy);
						}
					}
			point_r = 0.05;
				
			}
			//����Բ
			else if(p->ty == 4)
			{
				SetPenColor("Navy");
				if(p->isChosen || p->isClicked == 1)
				{
					SetPenColor("Shiningred");
					point_r = 0.08;
				}
				DrawPoint(p->c.x, p->c.y);
				MovePen(transferx(p->c.x + p->c.r * scale), transfery(p->c.y));
				DrawArc(p->c.r * scale, 0, 360);
				SetPenColor("Navy");
				//dbgS("Բ�������\n");
				point_r = 0.05;
			}
			//���ƺ���
			else if(p->ty == 5)
			{
				double x,y;
				SetPenColor(Function_Color[FuncColor % 5]);
				
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
		}//for-drawing
		SetPenSize(1);
		
	}//if
	if(pageid==3)
	{
		DisplayClear();	
		//calculate();
		setTextBoxColors("Rosered", "Rosered", "Salmon", "Rosered", 0);
		textbox(GenUIID(0), 3.5, 8, 8, 0.5, str, sizeof(str));
		MovePen(3, 8.2);
		DrawTextString("y = ");
		SetPenColor("Navy");
		drawLabel(2, 5,"��֧��һԪ������δ֪��������x");
		drawLabel(2, 4.5,"֧�ֳ��õ���������룬�磺 *   /   +   - ");
		drawLabel(2, 4,"֧�� �� ,e���� �� ��Ҫ��PI ���� pi����ʾ");
		drawLabel(2, 3.5,"�ַ�֮�䲻�ܴ��ڿո�");
		drawLabel(2, 3,"��֧�� * ʡ�ԣ���Ҫʹ��2*x��2*( )��");
		if(button(GenUIID(0), 6.5, 6, 2, 1, "ȷ��"))
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
	DefineColor("MildBlue", 0.537254, 0.717647, 0.9098039);
	
	//������ɫ
	DefineColor("BlueGray", 0.2745, 0.384314, 0.466667);
	DefineColor("FuncRed", 0.9411765, 0.133333, 0.172549);
	DefineColor("VividGreen", 0.529412, 0.6, 0.168627);
	DefineColor("FuncBlue", 0.30196, 0.61176, 0.63137);
	DefineColor("FuncOrange", 0.898039, 0.5647059, 0.411765);
	
}

void Main()
{
	//��ʼ�����ں�ͼ��ϵͳ
	SetWindowSize(15, 12);
	InitGraphics();
	initDebug();
	InitColor();
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

