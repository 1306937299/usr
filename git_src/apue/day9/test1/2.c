#include "../../apue.h"

int main(int argc, char **argv)
{
	int sfd;
	struct sockaddr_in addr;

	sfd =socket(AF_INET, SOCK_STREAM, 0);

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4567);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sfd, (struct sockaddr*)&addr, sizeof(addr));

	send(sfd, argv[1], strlen(argv[1]), 0);

	close(sfd);

	return 0;
}
