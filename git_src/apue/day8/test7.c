#include "../apue.h"

int main(int argc, char **argv)
{//./test7 25678
	//  atoi()   char* --> int  "123"-->123
	kill(atoi(argv[1]), SIGINT);
	//kill(getpid(), SIGINT);  == raise(SIGINT);
	return 0;
}
