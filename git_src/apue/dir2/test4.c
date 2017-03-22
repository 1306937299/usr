#include "../apue.h"


int main()
{
	/*
	printf("1 hello world!\n");
	fprintf(stdout, "2 hello world!\n");
	fprintf(stderr, "3 hello world!\n");
	*/

	//fprintf(stdout, "abcdef");
	//fprintf(stderr, "ABCDEF");


	write(1, "abcdef", 6);
	write(2, "ABCDEF", 6);

	//sleep(5);
	return 0;
}
