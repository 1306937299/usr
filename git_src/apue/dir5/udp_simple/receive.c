#include "../../apue.h"


int main()
{
	int sfd;
	struct sockaddr_in local_addr, rcv_addr;
	int ret;
	char buf[64];
	socklen_t addr_len;
	char *p = "欢迎来到东软睿道";

	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if ( sfd < 0 ) {
		perror("socket()");
		return -1;
	}

	bzero(&local_addr, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(7777);
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(sfd, (struct sockaddr*)&local_addr, sizeof(local_addr));
	if ( ret != 0 ) {
		perror("bind()");
		return -1;
	}

	while (1) {
		bzero(buf, sizeof(buf));
		bzero(&rcv_addr, sizeof(rcv_addr));
		addr_len = sizeof(rcv_addr);
		recvfrom(sfd, buf, sizeof(buf), 0, 
					(struct sockaddr*)&rcv_addr, &addr_len);
		printf("receive %s from <%s %d>\n", buf, 
					inet_ntoa(rcv_addr.sin_addr), ntohs(rcv_addr.sin_port));
		sendto(sfd, p, strlen(p), 0, 
					(struct sockaddr*)&rcv_addr, sizeof(rcv_addr));
	}


	close(sfd);
	return 0;
}
