#ifndef FUNCTION_H
#define FUNCTION_H
/*
 * sin->a, cos->b, tan->c, ln->d，且后面一定要紧跟()
 * 式子以 # 结尾，字符之间不能存在空格
 * 支持π->p, e
 * 不支持 * 省略，需要使用2*x，2*()等
 */
extern int change;//判断是否符合规范，若值为1，应该加大一点再算
double calculate(char a[], double x);//调用计算，只支持一个变量x
#endif //FUNCTION_H
