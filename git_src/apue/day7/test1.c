#include "../apue.h"


int main()
{
	pid_t pid1;


	pid1 = fork();

	printf("hello world! %d %d pid1=%d\n", getpid(), getppid(), pid1);

	sleep(1);
	return 0;
}
