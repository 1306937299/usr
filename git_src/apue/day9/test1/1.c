#include "../../apue.h"


int main()
{
	int sfd, afd;
	struct sockaddr_in local_addr, peer_addr;
	socklen_t addr_len;
	int ret;
	//socket
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	//bind
	bzero(&local_addr, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(4567);
	local_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ret = bind(sfd, (struct sockaddr*)&local_addr, sizeof(local_addr));
	//listen
	listen(sfd, 1);
	//accpet
	bzero(&peer_addr, sizeof(peer_addr));
	addr_len = sizeof(peer_addr);
	afd = accept(sfd, (struct sockaddr*)&peer_addr, &addr_len);
	//
	char buf[32] = {0};
	recv(afd, buf, 32, 0);

	printf("receive: %s\n", buf);

	close(afd);
	close(sfd);

	return 0;
}
