#include "Header.h"
#include "LinkList.h"
void store()
{
	FILE* fp;
	Shape* temp=head->next;
	fp=fopen("storage.txt","w");
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
		fprintf(fp,"%d %d %d",temp->isChosen,temp->isClicked,(int)temp->ty); //status
		fprintf(fp,"%s",temp->expression);
		dbgS("end 1");
		if(temp->ty!=3)
		{
			struct Point* ptemp=temp->pHead;
			while(ptemp->next!=NULL)
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
		temp=temp->next;
	}
	fclose(fp);
	dbgS("end store");
} 

void read()
{
	FILE* fp;
	Shape* temp=(Shape*)malloc(sizeof(Shape));
	head->next=temp;
	char s;
	fp=fopen("storage.txt","r");
	dbgS("start reading"); 
//	typedef struct shape{
//    enum ShapeType ty;		// point, line, segment, poly, circle; function
//    int isChosen;
//    int isClicked;
//    struct Point *pHead;		// point list, for point, line, segment, poly
//    struct Circle c;
//    struct shape *before;
//    struct shape *next;
//}Shape;
	while(feof(fp)==0)
	{
		dbgS("step 1");      
		fscanf(fp,"%d %d %d",temp->isChosen,temp->isClicked,temp->ty);
		dbgS("step 1");
		fscanf(fp,"%s",temp->expression);
		dbgS("step 1");
		if(temp->ty!=3)
		{
			struct Point* ptemp=malloc(sizeof(struct Point));
			temp->pHead=ptemp;
			dbgS("step 2");
			while(1)
			{
				dbgS("step 2.1");
				fscanf(fp,"%f %f %d",ptemp->x,ptemp->y,ptemp->connect);
				dbgS("step 2.5");
				if(fgetc(fp)=='\n') break;
				ptemp->next=(struct Point*)malloc(sizeof(struct Point));
				ptemp=ptemp->next;
				dbgS("step 3");
			}
		}
		if(temp->ty==3)
		{
			fscanf(fp,"%f %f %f",temp->c.r,temp->c.x,temp->c.y);
		}

		temp->before=temp;
		temp->next=(Shape*)malloc(sizeof(Shape));
		temp=temp->next;
		dbgS("1 loop");
	}
	end=temp->next;
	fclose("fp");
	
}
