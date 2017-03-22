#include "../apue.h"

void sig_int(int s)
{//s 信号的值
	printf("SIGINT\n");
	sleep(5);
}

int main()
{
	signal(SIGINT, sig_int);
	//signal(SIGINT, SIG_IGN);//忽略信号
	//signal(SIGINT, SIG_DFL);	//默认动作
	//signal(SIGQUIT, sig_int);
	//signal(SIGTERM, sig_int);
	//signal(SIGKILL, sig_int);
	while (1) {
		write(1, "X", 1);
		usleep(200000);
	}
	return 0;
}
