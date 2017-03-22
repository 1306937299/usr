#include "../apue.h"


int main()
{

	if ( fork() == 0 ) {
		printf("child. pid=%d ppid=%d\n", getpid(), getppid());
		sleep(3);
		printf("child. pid=%d ppid=%d\n", getpid(), getppid());
	}
	else {
		printf("parent. pid=%d ppid=%d\n", getpid(), getppid());
		sleep(1);
		while (1)
			;
	}

	return 0;
}
