#include "../apue.h"


int main(int argc, char **argv)
{
	int pfd[2];
	int ret;
	pid_t pid;

	ret = pipe(pfd);
	if ( ret != 0 ) {
		perror("pipe()");
		return -1;
	}


	pid = fork();
	if ( pid == 0 ) { //child
		close(pfd[1]);
		
		char buf[32];
		bzero(buf, 32);
		read(pfd[0], buf, 32);
		printf("receive : %s\n", buf);

		close(pfd[0]);
	}
	else { //parent
		close(pfd[0]);

		write(pfd[1], argv[1], strlen(argv[1]));

		close(pfd[1]);
		wait(NULL);
	}



	return 0;
}
