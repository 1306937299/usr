#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	struct stat statres;
	int ret;

	printf("%s\n", argv[1]);

	ret = stat(argv[1], &statres);
	if ( ret != 0 ) {
		perror("stat()");	//打印错误原因
		return -1;
	}

	printf("0%o %d %s\n", statres.st_mode&0777, statres.st_size, argv[1]);

	//rw-r--r--  0644
	//if ( statres.st_mode&0400 )
	//if ( (statres.st_mode>>8)&1  )
	if ( statres.st_mode & (1<<8) )  {
		printf("r");
	}
	else {
		printf("-");
	}
	if ( statres.st_mode & (1<<7) )  {
		printf("w");
	}
	else {
		printf("-");
	}
	if ( statres.st_mode & (1<<6) )  {
		printf("x\n");
	}
	else {
		printf("-\n");
	}


	return 0;
}
