#include "../apue.h"

int my_max(int a, int b)
{
	return a>b?a:b;
}

int main()
{
	int ret;

	int (*pfunc)(int , int);	//定义一个函数指针

	pfunc = my_max;	//函数指针指向一个函数


	ret = pfunc(1, 2);	//通过函数指针调用指向的函数

	printf("ret=%d\n", ret);

	return 0;
}
