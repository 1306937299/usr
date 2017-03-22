#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
	char buf[32];

	bzero(buf, 32);	//按字节数清0

	read(0, buf, 32);	//gets
	write(1, buf, 32);	//puts


	return 0;
}
