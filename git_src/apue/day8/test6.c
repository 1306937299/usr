#include "../apue.h"
#include <sys/time.h>

int token = 1;	//令牌  可用的资源数

void sig_alrm(int s)
{
	token++;
}

int main(int argc, char **argv)
{
	int fd;

	signal(SIGALRM, sig_alrm);//将SIGALRM信号的回调函数设置为sig_alrm

	fd = open(argv[1], O_RDONLY);
	if ( fd < 0 ) {
		perror("open()");
		return -1;
	}


	//ualarm(100000, 500000);//安排一个SIGALRM在3s之后到达
	struct itimerval it;
	it.it_value.tv_sec = 1;
	it.it_value.tv_usec = 500000;
	it.it_interval.tv_sec = 0;
	it.it_interval.tv_usec = 500000;
	setitimer(ITIMER_REAL, &it, NULL);
	char ch;
	int ret;
	while (1)	{
		while ( token == 0  ) {
			;
		}
		ret = read(fd, &ch, 1);
		if ( ret <= 0 ) {
			break;
		}
		write(1, &ch, 1);
		token--;
	}
	close(fd);
	return 0;
}

//练习：slowcat  要求每隔1s打印文件中的一个字符  使用SIGALRM
