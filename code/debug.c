#include "debug.h"

FILE *fdebug;

void initDebug()	{fdebug = fopen("debug.txt","w");}
void dbgI(int x)	
{
	fdebug = fopen("debug.txt","a");
	fprintf(fdebug, "%d", x);
	fclose(fdebug);
}
void dbgC(char x)
{
	fdebug = fopen("debug.txt","a");
	fprintf(fdebug, "%c", x);
	fclose(fdebug);
}
void dbgD(double x)
{
	fdebug = fopen("debug.txt","a");
	fprintf(fdebug, "%lf", x);
	fclose(fdebug);
}
void dbgS(char *x)
{
	fdebug = fopen("debug.txt","a");
	fprintf(fdebug, "%s", x);
	fclose(fdebug);
}