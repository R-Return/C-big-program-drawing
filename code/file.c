#include "Header.h"
#include "LinkList.h"
void store()
{
	FILE* fp;
	Shape* temp=head->next;
	fp=fopen("storage.mydraw","w");
	dbgS("start storing");
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
		dbgS("end 1");
		if(temp->ty!=3)
		{
			struct Point* ptemp=temp->pHead->next;
			while(ptemp!=NULL)
			{
				fprintf(fp,"%f %f %d ",ptemp->x,ptemp->y,ptemp->connect);
				
				ptemp=ptemp->next;
				dbgS("end 1");
			}
		}
		if(temp->ty==3)
		{
			fprintf(fp,"%f %f %f",temp->c.r,temp->c.x,temp->c.y);
		}
		//*****

		fputc('\n',fp);
		fputc('#',fp);
		temp=temp->next;
	}
	fclose(fp);
	dbgS("end store");
} 

void read()
{
	FILE* fp;
	char c;
	Shape* temp;
//	head->next=end;
//	end->before = head->next;
	char s;
	fp=fopen("storage.mydraw","r");
	dbgS("start reading\n"); 
//	typedef struct shape{
//    enum ShapeType ty;		// point, line, segment, poly, circle; function
//    int isChosen;
//    int isClicked;
//    struct Point *pHead;		// point list, for point, line, segment, poly
//    struct Circle c;
//    struct shape *before;
//    struct shape *next;
//}Shape;
	while((c = fgetc(fp)) != EOF)
	{
		dbgS("准备读入状态\n");
		temp=(Shape*)malloc(sizeof(Shape));
		temp->isChosen =  c- '0';    
		fscanf(fp," %d %d",&temp->isClicked, &temp->ty);
		dbgI(temp->isChosen);dbgI(temp->isClicked);dbgI(temp->ty);dbgC('\n');
		dbgS("状态读入完成\n");
		fgetc(fp);
		fgets(temp->expression,MAX,fp);
//		fgetc(fp);
		dbgS(temp->expression);dbgS("表达式读入完成\n");
		if(temp->ty!=3)
		{
			struct Point *ptemp;
			temp->pHead = malloc(sizeof(struct Point));
			temp->pHead->next=ptemp;
			while(1)
			{
				ptemp=(struct Point*)malloc(sizeof(struct Point));
				fscanf(fp,"%lf %lf %d ",&ptemp->x,&ptemp->y,&ptemp->connect);
				dbgD(ptemp->x);dbgD(ptemp->y);dbgI(ptemp->connect);dbgC('\n');
				if(fgetc(fp)=='#') break;
				ptemp=ptemp->next;
				dbgS("读入一个节点\n");
			}
		}
		if(temp->ty==3)
		{
			fscanf(fp,"%lf %lf %lf",&temp->c.r,&temp->c.x,&temp->c.y);
		}

		temp->before=end->before;
		end->before->next = temp;
		temp->next = end;
		end->before = temp;
		
		dbgS("1 loop\n");
	}
	dbgS("循环结束\n");
	fclose(fp);
	dbgS("结束读取\n");
	display();
}
