#include "../../apue.h"

int main(int argc, char *argv[])
{
	int sfd;
	struct sockaddr_in  peer_addr;
	int ret;
	//1.socket()
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if ( sfd < 0 ) {
		perror("socket()");
		return -1;
	}
	//2.connect()
	bzero(&peer_addr, sizeof(peer_addr));
	peer_addr.sin_family = AF_INET;
	peer_addr.sin_port = htons(9999);
	peer_addr.sin_addr.s_addr = inet_addr(argv[1]);
	ret = connect(sfd, (struct sockaddr*)&peer_addr, sizeof(peer_addr));
	if ( ret != 0 ) {
		perror("connect()");
		return -1;
	}

	//3.read()/write()
	write(sfd, argv[2], strlen(argv[2]));

	//4.close()
	close(sfd);
	return 0;
}
