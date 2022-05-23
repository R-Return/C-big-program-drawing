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
		if (chose) {			//�����ѡ�еĵ���� ��struct�е�chose������1
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

//	switch (button) {						//���ܰ�ťѡ��
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
		dbgS("��ʼ���ƴ���1\n");
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
		dbgS("����1�������\n");
	}
	if(pageid==2)
	{
		dbgS("��ʼ���ƴ���2\n");
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
	if(pageid==3)
	{
		DisplayClear();	
		//calculate();
		textbox(GenUIID(0), 1, 5, 8, 0.5, str, sizeof(str));
		if(button(GenUIID(0), 1.5, 1.5, 2, 1, "ȷ��"))
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
	//��ʼ�����ں�ͼ��ϵͳ
	InitGraphics();
	initDebug();
	SetWindowTitle("���λ���");
	dbgS("��ʼ����\n");
	registerCharEvent(CharEventProcess);        // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	//registerTimerEvent(TimerEventProcess);      // ��ʱ��
	centerX=6.1;
	centerY=4;
	scale=1;
	dbgS("ȫ�ֱ�����ʼ�����\n");
	display();
	//��ʼ������
	//initLinkList();
	
	
}

