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

	while(temp->next!=NULL)
	{
		fprintf(fp,"%d %d %d",temp->isChosen,temp->isClicked,temp->ty); //status
		dbgS("end 1");
		if(temp->ty!=3)
		{
			struct Point* ptemp=temp->pHead;
			while(ptemp->next!=NULL)
			{
				fprintf(fp,"%f %f %d",ptemp->x,ptemp->y,ptemp->connect);
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
//void read()
//{
//	FILE* fp;
//	Shape* temp;
//	fp=fopen("storage.txt","r");
//	//	typedef struct shape{
////    enum ShapeType ty;		// point, line, segment, poly, circle; function
////    int isChosen;
////    int isClicked;
////    struct Point *pHead;		// point list, for point, line, segment, poly
////    struct Circle c;
////    struct shape *before;
////    struct shape *next;
////}Shape;
//	while(feof(fp)==0)
//	{
//		fscanf("%d %d %d",temp->isChosen,temp->isClicked,temp->ty);
//		if(temp->ty==0)
//		{
//			while(1)
//			{
//				fscanf("%f %f",ptemp->x,ptemp->y);
//				ptemp=ptemp->next;
//			}
//		}
//		
//		
//
//
//
//		temp=temp->next;
//	}
