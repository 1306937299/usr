#include "../../apue.h"
#define SERVER_PORT	8888
// ./cli 192.168.2.252
int main(int argc, char **argv)
{
	int sfd;
	struct sockaddr_in ser_addr;
	int ret;
	if ( argc != 2 ) {
		printf("Usage:need server's address.\n");
		return -1;
	}
	bzero(&ser_addr, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(SERVER_PORT);
	ser_addr.sin_addr.s_addr = inet_addr(argv[1]);

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if ( sfd < 0 )  {
		perror("socket()");
		return -1;
	}
	ret = connect(sfd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
	if ( ret != 0 ) {
		perror("connect()");
		return -1;
	}



	close(sfd);
	return 0;
}
