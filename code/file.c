#include "Header.h"
#include "LinkList.h"
void store()
{
	FILE* fp;
	Shape* temp=head->next;
	fp=fopen("storage.mydraw","w");
//	dbgS("start storing");
//	typedef struct shape{
//    enum ShapeType ty;		// point, line, segment, poly, circle; function
//    int isChosen;
//    int isClicked;
//    struct Point *pHead;		// point list, for point, line, segment, poly
//    struct Circle c;
//    struct shape *before;
//    struct shape *next;
//}Shape;

	while(temp!=end)
	{
		fprintf(fp,"%d %d %d ",temp->isChosen,temp->isClicked,temp->ty); //status
		fprintf(fp,"%s",temp->expression);
		fputc('\n',fp);
//		dbgS("״̬�������\n");
		if(temp->ty!=4)
		{
			struct Point* ptemp=temp->pHead->next;
			while(ptemp->next!=NULL)
			{
				fprintf(fp,"%f %f %d ",ptemp->x,ptemp->y,ptemp->connect);
				
				ptemp=ptemp->next;
//				dbgS("��������\n");
			}
			fprintf(fp,"%f %f %d",ptemp->x,ptemp->y,ptemp->connect);
				
			ptemp=ptemp->next;
//			dbgS("��������\n");
		}
		else if(temp->ty==4)
		{
//			dbgS("��ʼ��Բ\n");
			fprintf(fp,"%f %f %f",temp->c.r,temp->c.x,temp->c.y);
//			dbgS("Բ�������\n");
		}
		
		fputc('#',fp);
		temp=temp->next;
	}
	fclose(fp);
//	dbgS("end store");
} 

void read()
{
	FILE* fp;
	char c;
	
//	head->next=end;
//	end->before = head->next;
	char s;
	fp=fopen("storage.mydraw","r");
//	dbgS("start reading\n"); 
	while((c = fgetc(fp)) != EOF)
	{
		Shape* temp;
//		dbgS("׼������״̬\n");
		temp=(Shape*)malloc(sizeof(Shape));
		temp->isChosen =  c- '0';    
		fscanf(fp," %d %d",&temp->isClicked, &temp->ty);
//		dbgI(temp->isChosen);dbgI(temp->isClicked);dbgI(temp->ty);dbgC('\n');
//		dbgS("״̬�������\n");
		fgetc(fp);
		fgets(temp->expression,MAX,fp);
		temp->expression[strlen(temp->expression)-1] = '\0';
//		fgetc(fp);
//		dbgS(temp->expression);dbgS("���ʽ�������\n");
		if(temp->ty!=4)
		{
			struct Point *e;
			temp->pHead = malloc(sizeof(struct Point));
			e = temp->pHead;
			while(1)
			{
				struct Point *ptemp;
				ptemp=(struct Point*)malloc(sizeof(struct Point));
				ptemp->next = NULL;
				e->next = ptemp;
				fscanf(fp,"%lf %lf %d",&ptemp->x,&ptemp->y,&ptemp->connect);
//				dbgD(ptemp->x);dbgD(ptemp->y);dbgI(ptemp->connect);dbgC('\n');
				if(fgetc(fp)=='#') break;
				e = ptemp;
//				dbgS("����һ���ڵ�\n");
			}
		}
		else if(temp->ty==4)
		{
			fscanf(fp,"%lf %lf %lf",&temp->c.r,&temp->c.x,&temp->c.y);
			fgetc(fp);
//			dbgS("Բ�ڵ�������\n");
		}
//		dbgD(temp->pHead->next->x);dbgC('\n');
		temp->before=end->before;
		end->before->next = temp;
		temp->next = end;
		end->before = temp;
		temp= NULL;
		
//		dbgS("1 loop\n");
	}
//	dbgS("ѭ������\n");
	fclose(fp);
//	dbgS("������ȡ\n");
	Shape *temp;
	for(temp = head->next; temp != end; temp = temp->next)
	{
//		dbgS(temp->expression);
//		dbgD(temp->pHead->next->x);dbgC('\n');
	}
	display();
}
