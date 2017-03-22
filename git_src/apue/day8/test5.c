#include "../apue.h"

void sig_alrm(int s)
{
	write(1, "X", 1);
	alarm(3);
}

int main()
{

	signal(SIGALRM, sig_alrm);//将SIGALRM信号的回调函数设置为sig_alrm

	alarm(3);//安排一个SIGALRM在3s之后到达

	while (1)	{
		pause();	//pause()将进程挂起 至从一个信号处理函数返回
	}

	return 0;
}

//练习：slowcat  要求每隔1s打印文件中的一个字符  使用SIGALRM
