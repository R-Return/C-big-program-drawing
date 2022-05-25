#include "Header.h"
#define maxFunc 100	//�����ַ�����󳤶�
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
		//dbgS("��ʼ���ƴ���1\n");
		MovePen(4,5);
		SetPointSize(50);
		DrawTextString("���λ���");
		SetPointSize(20); 
		if(button(GenUIID(0), 2, 1.5, 2, 1, "��ʼʹ��"))
		{
			dbgS("ѡ�񡰿�ʼʹ�á���ť\n");
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
			; 
		}
		if(button(GenUIID(0), 0.2, 4, 1, 0.5, "ֱ��"))
		{
			; 
		}
		if(button(GenUIID(0), 0.2, 3, 1, 0.5, "�����"))
		{
			; 
		}
		//DisplayClear();	
		
		//����
		Shape *p;
		int FuncColor;
		FuncColor = 0;
		for(p = head->next;p != end; p = p->next)
		{
			//���ƺ���
			if(p->ty == 5)
			{
				double oy,cy;
				int interupt = 0;
				SetPenColor(Function_Color[FuncColor % 7]);
				d = 1;
				for(j=3;j<9.2;j+=0.05)
				{ 
					//dbgS( "�滭������");dbgI(d);dbgC('\n');
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
					dbgS( "��ɻ滭������");dbgI(d);dbgC('\n');
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

