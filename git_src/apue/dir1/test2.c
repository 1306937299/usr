#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
	int fd;
	//O_RDONLY  O_WRONLY  O_RDWR   
	//O_CREAT 如果文件不存在则创建
	//O_TRUNC 如果文件存在则清零0
	//O_APPEND 如果文件存在则定位到文件末尾     
	//open的第三个参数，在打开方式中有O_CREAT有意义，指定被创建文件的权限
	
	umask(0777);
	//close(1);
	fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0777);
	if ( fd < 0 ) {
		perror("open()");
		return -1;
	} 
	printf("fd=%d\n", fd);
	char *p = "hello world";
	write(fd, p, 11/*strlen(p)*/);


	close(fd);
	return 0;
}
