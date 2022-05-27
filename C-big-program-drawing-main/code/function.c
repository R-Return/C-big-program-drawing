#include <stdio.h>
#include <math.h>
#include "function.h"
#include "debug.h"
#define MAXSIZE 100
#define PI 3.1415926536
#define e 2.718281828459045

typedef struct {
	char data[MAXSIZE];
	int top;
} Stack1;

typedef struct {
	double data[MAXSIZE];
	int top;
} Stack2;

int change;

//操作符相关操作
void InitStack1 (Stack1 *s) {
	s->top = -1;
}

int Empty_Stack1(Stack1 *s) {
	if (s->top != -1)
		return 1;
	else
		return 0;
}

int PushStack1(Stack1 *s, char x) {
	if (s->top == (MAXSIZE - 1))
		return 0;
	else
		s->data[++(s->top)] = x;
	return 1;
}

char PopStack1(Stack1 *s) {
	char x;
	if (!Empty_Stack1(s))
		return 0;
	else {
		x = s->data[s->top];
		s->top--;
		return x;
	}
}

char GetStack1(Stack1 *s) {
	char x;
	if (!Empty_Stack1(s))
		return 0;
	else
		x = s->data[s->top];
	return x;
}

//数字符相关操作
void InitStack2 (Stack2 *s) {
	s->top = -1;
}

int Empty_Stack2(Stack2 *s) {
	if (s->top != -1)
		return 1;
	else
		return 0;
}

int PushStack2(Stack2 *s, double x) {
	if (s->top == (MAXSIZE - 1))
		return 0;
	else
		s->data[++(s->top)] = x;
	return 1;
}

double PopStack2(Stack2 *s) {
	double x;
	if (!Empty_Stack2(s))
		return 0;
	else {
		x = s->data[s->top];
		s->top--;
		return x;
	}
}

double GetStack2(Stack2 *s) {
	double x;
	if (!Empty_Stack2(s)) {
		dbgS("stack 2 empty!");
		dbgC('\n');
		return 0;
	}

	else
		x = s->data[s->top];
	return x;
}

int isOptr(char c) {
	int x;
	switch (c) {
		case '+':
		case '-':
			x = 1;
			break;
		case '*':
		case '/':
			x = 2;
			break;
		case '^':
			x = 3;
			break;
		case 'a':
		case 'b':
		case 'c':
		case 'd':
			x = 4;
			break;
	}
	return x;
}

char Precede(char a, char b) {
	static int i = 0, j = 0;

	char priority[12][12] = {
		{'>', '>', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>'},	//+
		{'>', '>', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>'},	//-
		{'>', '>', '>', '>', '<', '<', '<', '<', '<', '<', '>', '>'},	//*
		{'>', '>', '>', '>', '<', '<', '<', '<', '<', '<', '>', '>'},	//'/'
		{'>', '>', '>', '>', '>', '<', '<', '<', '<', '<', '>', '>'},	//^
		{'>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '0', '>'},	//sin-a
		{'>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '0', '>'},	//cos-b
		{'>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '0', '>'},	//tan-c
		{'>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '0', '>'},	//ln-d
		{'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '=', '0'},	//(
		{'>', '>', '>', '>', '>', '>', '>', '>', '>', '0', '>', '>'},	//)
		{'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '0', '='},	//#
	};

	switch (a) {
		case'+':
			i = 0;
			break;
		case'-':
			i = 1;
			break;
		case'*':
			i = 2;
			break;
		case'/':
			i = 3;
			break;
		case'^':
			i = 4;
			break;
		case'a': i = 5; break;
			case'b': i = 6; break;
				case'c': i = 7; break;
					case'd': i = 8; break;
						case'(':
			i = 9;
			break;
		case')':
			i = 10;
			break;
		case'#':
			i = 11;
			break;
	}
	switch (b) {
		case'+':
			j = 0;
			break;
		case'-':
			j = 1;
			break;
		case'*':
			j = 2;
			break;
		case'/':
			j = 3;
			break;
		case'^':
			j = 4;
			break;
		case'a': j = 5; break;
			case'b': j = 6; break;
				case'c': j = 7; break;
					case'd': j = 8; break;
						case'(':
			j = 9;
			break;
		case')':
			j = 10;
			break;
		case'#':
			j = 11;
			break;
	}
	return priority[i][j];
}
double Operate(double m, double n, char x) {
	double result;
	if (x == '+')
		result = m + n;
	if (x == '-')
		result = m - n;
	if (x == '*')
		result = m * n;
	if (x == '/') {
		if (n != 0)
			result = m / n;
		else {
			change = 1;
			result = 0;
		}
	}
	if (x == '^')
		result = pow(m, n);
	//dbgS("计算结果是：");dbgD(result);dbgC('\n');
	return result;
}
double Function(char x, double m) {
	if (x == 'a')
		return sin(m);
	if (x == 'b')
		return cos(m);
	if (x == 'c') {
		if ((m - PI / 2) / (PI / 2) == 0) {
			change = 1;
			return 0;
		} else
			return tan(m);
	}
	if (x == 'd') {
		if (m <= 0) {
			change = 1;
			return 0;
		} else
			return log(m);
	}
}

char GetC(char a[], int *i) {
	char c;
	if (a[*i] == 's' && a[*i + 1] == 'i' && a[*i + 2] == 'n') {
		c = 'a';
		(*i) += 3;
	} else if (a[*i] == 'c' && a[*i + 1] == 'o' && a[*i + 2] == 's') {
		c = 'b';
		(*i) += 3;
	} else if (a[*i] == 't' && a[*i + 1] == 'a' && a[*i + 2] == 'n') {
		c = 'c';
		(*i) += 3;
	} else if (a[*i] == 'l' && a[*i + 1] == 'n') {
		c = 'd';
		(*i) += 2;
	} else if (a[*i] == '\0') {
		c = a[*i];
	} else {
		c = a[*i];
		(*i)++;
	}
	return c;
}

double calculate(char a[], double x) {
	//dbgS("现在进行运算\n");
	//dbgS("现在传入函数为：");dbgS(a);dbgC('\n');
	//dbgS("现在传入x：");dbgD(x);dbgC('\n');
	Stack1 operater;
	Stack2 operand;
	char c, o;
	int i = 0;
	double t = 0, k = 0;
	change = 0;//无穷大，换符号
	InitStack1(&operater);
	InitStack2(&operand);
	PushStack1(&operater, '#');
	c = GetC(a, &i);
	//dbgS("当前i：");dbgI(i);dbgC('\n');
	while (c != '\0'
	        && (Empty_Stack1(&operater))
	        && !change) {
		//dbgC(c);dbgC('\n');
		//数字部分
		t = 0;
		k = 0;
		while (c >= '0' && c <= '9' || c == '.') {
			if (c == '.')
				k = 0.1;
			if (k == 0)
				k = 1;
			if (k == 1) {
				t = t * 10 + c - '0';
			} else {
				t = t + (c - '0') * k;
				k = k * 0.1;
			}
			c = GetC(a, &i);
			//dbgC(c);dbgC('\n');
		}//while
		if (k) {
			if (PushStack2(&operand, t) == 0) {
				dbgS( "溢出");
				dbgC('\n');
			}
		}//if
		if (c == 'x') {
			//dbgS("读到x\n");
			if (PushStack2(&operand, x) == 0) {
				dbgS( "溢出");
				dbgC('\n');
			}
			c = GetC(a, &i);
		}//if
		if (c == 'P' || c == 'p') {
			if (PushStack2(&operand, PI) == 0) {
				dbgS( "溢出");
				dbgC('\n');
			}
			i++;
			c = GetC(a, &i);
		}//if
		if (c == 'e') {
			if (PushStack2(&operand, e) == 0) {
				dbgS( "溢出");
				dbgC('\n');
			}
			c = GetC(a, &i);
		}//if
		//操作数部分
		//dbgS("待处理操作数：");dbgC(c);dbgC('\n');
		//dbgS("操作数栈顶：");dbgC(GetStack1(&operater));dbgC('\n');
		switch (Precede(o = GetStack1(&operater), c)) {
			case '<':   //继续存放
				PushStack1(&operater, c);
				//dbgS("继续存放的操作数：");dbgC(c);dbgC('\n');
				//dbgS("当前i：");dbgI(i);dbgC('\n');
				c = GetC(a, &i);
				//dbgS("当前i：");dbgI(i);dbgC('\n');
				//dbgS("新读取操作数：");dbgC(c);dbgC('\n');
				break;
			case '>':   //计算
				if (isOptr(o) == 4)
					PushStack2(&operand, Function(PopStack1(&operater), PopStack2(&operand)));
				else
					PushStack2(&operand, Operate(PopStack2(&operand), PopStack2(&operand), PopStack1(&operater)));
				if (change == 1)
					return -1;
				break;
			case '=':
				PopStack1(&operater);
				c = GetC(a, &i);
				break;
		}//switch
	}//while
	double result;
	if (change)
		result = 0;
	else
		result = GetStack2(&operand);
	//dbgS( "---------运算结束，结果为：");dbgD(result);dbgC('\n');
	return result;
}

