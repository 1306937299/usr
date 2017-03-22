#include "../apue.h"


int main()
{
	int i;
	pid_t pid[5];
	for ( i=0; i<5; i++) {
		pid[i] = fork();
		if ( pid[i] == 0 ) {
			printf("pid[%d]=%d\n", i, getpid());
			exit(i*100);//0 1 2 3 4
		}
	}

	getchar();

	pid_t pid_ret;
	int ret;
	for ( i=0; i<5; i++) {
		pid_ret = wait(&ret);
		//printf("pid_ret=%d ret=%d\n", pid_ret, WEXITSTATUS(ret));
		printf("pid_ret=%d ret=%d\n", pid_ret, (ret&0xff00)>>8);
	}
	// a/8 /16 /32 /64 /128 /256 /512 /1024
	// a/2  a>>1 
	// a/4  a>>2
	while (1)
		;

	return 0;
}
