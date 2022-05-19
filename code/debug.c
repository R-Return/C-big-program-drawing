#include "Header.h"

FILE *fdebug;

void initDebug()	{fdebug = fopen("debug.txt","w");}
void dbgI(int x)	{fprintf(fdebug, "%d", x);}
void dbgC(char x)	{fprintf(fdebug, "%c", x);}
void dbgD(double x)	{fprintf(fdebug, "%lf", x);}
void dbgS(char *x)	{fprintf(fdebug, "%s", x);}