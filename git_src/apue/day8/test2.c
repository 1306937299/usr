#include "../apue.h"
#include <pwd.h>


void print_prompt()
{
	struct passwd *ppa;
	char hn[32], cwd[64];
	ppa = getpwuid(getuid());

	gethostname(hn, 32);
	getcwd(cwd, 64);	//current work directory

	printf("[%s@%s %s]# ", ppa->pw_name, hn, cwd);
}


int main()
{
	char buf[32];
	while (1) {
		print_prompt();
		scanf("%s", buf);
		if ( fork() == 0 ) {
			execlp(buf, buf, NULL);
			perror("execlp()");
			exit(1);
		}
		else {
			wait(NULL);
		}
	}

	return 0;
}






