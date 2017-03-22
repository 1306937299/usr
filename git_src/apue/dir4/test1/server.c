#include "../../apue.h"
#define SERVER_PORT	8888

static int sfd;//静态全局变量的作用域被限定在当前文件中

void init_network()
{
	struct sockaddr_in addr;
	int ret;
	//1.socket()
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if ( sfd < 0 ) {
		perror("socket()");
		exit(1);
	}
	//2.bind()
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
	if ( ret != 0 ) {
		perror("bind()");
		exit(1);
	}
	//3.listen()
	listen(sfd, 20);
}
void destroy_network()
{
	close(sfd);
}


int main()
{
	int afd;
	struct sockaddr_in peer_addr;
	time_t t;
	socklen_t addr_len;
	char buf[64];
	struct tm *ptm;

	init_network();

	while (1) {
		//4.accept()
		bzero(&peer_addr, sizeof(peer_addr));
		addr_len = sizeof(peer_addr);
		afd = accept(sfd, (struct sockaddr*)&peer_addr, &addr_len);
		printf("connect with %s %d\n", inet_ntoa(peer_addr.sin_addr), 
				ntohs(peer_addr.sin_port));

		//5.read()/write()
		
		//6.close()
		close(afd);
	}
	//7.close()
	destroy_network();
	return 0;
}
