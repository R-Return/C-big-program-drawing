#include "Header.h"
int pageid=1;
char str[100]="" ;
static double j;
double cx,cy,ox,oy;

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


void MouseEventProcess(int x, int y, int button, int event)
{
	/*������Ļ*/
	DisplayClear();

	/* ��ȡ���״̬ */
	uiGetMouse(x,y,button,event);

	/* ������ʾ������ʾ���� */
	display();
}

void display()
{
	static int d = 1;
	static double j;
	if(pageid==1)
	{
		MovePen(4,5);
		SetPointSize(50);
		DrawTextString("���λ���");
		SetPointSize(20); 
		if(button(GenUIID(0), 2, 1.5, 2, 1, "��ʼʹ��"))
		{
			pageid=2;
		}
		if(button(GenUIID(0), 6, 1.5, 2, 1 , "�˳�"))
		{
			exit(-1);
		}	
	}
	if(pageid==2)
	{
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
	}
	if(pageid==3)
	{
		DisplayClear();	
		//calculate();
		textbox(GenUIID(0), 1, 5, 8, 0.5, str, sizeof(str));
		if(button(GenUIID(0), 1.5, 1.5, 2, 1, "ȷ��"))
		{
			pageid=2;
		oy=transfery(calculate(str,-4));
		ox=transferx(-4);
		MovePen(ox,oy);
		for(j=-4;j<4;j+=0.01)
		{ 
			dbgS( "�滭������");dbgI(d);dbgC('\n');
			cy=transfery(calculate(str,j));
			dbgS( "�����������ǣ�");dbgD(cy);dbgC('\n');
			cx=transferx(j);
			dbgS( "���ں������ǣ�");dbgD(cx);dbgC('\n');
			DrawLine(cx-ox,cy-oy);
			dbgS( "��ɻ滭������");dbgI(d);dbgC('\n');
			d++;
			ox=cx;
			oy=cy;
		}
		}
	}
}

void Main()
{
	//��ʼ�����ں�ͼ��ϵͳ
	InitGraphics();
	initDebug();
	SetWindowTitle("���λ���");
	registerCharEvent(CharEventProcess);        // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	//registerTimerEvent(TimerEventProcess);      // ��ʱ��
	centerX=6.1;
	centerY=2;
	scale=1;
	
	dbgS("��ʼ����\n");
}

