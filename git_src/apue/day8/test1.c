#include "../apue.h"


int main()
{
	char *exec_argv[] = {
		"/bin/ls", "-l", "/root", NULL
	};
	printf("test1 begin.\n");

	//execve(exec_argv[0], exec_argv, NULL);
	execlp("ls", "/bin/ls", "-l", "/root", NULL, NULL);

	printf("test1 end.\n");
	return 0;
}
