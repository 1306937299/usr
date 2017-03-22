#include "../apue.h"


int main(int argc, char **argv)
{
	int fd;
	char buf[64];
	int ret;

	fd = open(argv[1], O_RDONLY);
	if ( fd < 0 ) {
		perror("open()");
		return -1;
	}
	// I --> 处理 -->  O 
	while (1) {
		bzero(buf, 64);
		ret = read(fd, buf, 64);
		if ( ret <= 0 ) {
			break;
		}
		write(1, buf, ret);
	}
	
	close(fd);
	return 0;
}
