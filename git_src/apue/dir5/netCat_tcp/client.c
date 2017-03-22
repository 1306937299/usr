#include "network.h"

// ./cli 192.168.2.252
int main(int argc, char **argv)
{
	int sfd;
	struct sockaddr_in ser_addr;
	int ret;
	s2c_t rcv_msg;

	if ( argc != 3 ) {
		printf("Usage:need server's address and filename.\n");
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

	send(sfd, argv[2], strlen(argv[2]), 0);
	
	while (1) {
		bzero(&rcv_msg, sizeof(rcv_msg));
		recv(sfd, &rcv_msg, sizeof(rcv_msg), 0);
		if ( rcv_msg.type == S2C_NOEXIST ) {
			fprintf(stderr, "File %s is not exist!\n", argv[2]);
			break;
		}
		else if ( rcv_msg.type ==  S2C_FILEEND ) {
			fprintf(stderr, "\n\tFile Cat is Ok!\n");
			break;
		}
		else if ( rcv_msg.type == S2C_FILECONTENT ) {
			write(1, rcv_msg.filecontent, rcv_msg.size);
		}
	}

	close(sfd);
	return 0;
}
