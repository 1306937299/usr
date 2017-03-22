#include "../../apue.h"

int main()
{
	int sfd, afd;
	struct sockaddr_in local_addr, peer_addr;;
	int ret;
	socklen_t addr_len;
	//1.socket()	---  有了套接字才能进行网络通信
	sfd = socket(AF_INET, SOCK_STREAM, /*0*/ IPPROTO_TCP);
	if ( sfd < 0 ) {
		perror("socket()");
		return -1;
	}

	//2.bind()   --- 确定套接字上的地址（端口号）
	bzero(&local_addr, sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(9999);
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);	//任意的IP
	ret = bind(sfd, (struct sockaddr*)&local_addr, sizeof(local_addr));
	if ( ret != 0 ) {
		perror("bind()");
		return -11;
	}

	//3.listen()  --- 调用后，可以接受连接请求
	listen(sfd, 200);//sfd成为监听套接字

	while (1) {
		//4.accept() --- 获得一个完成的连接，使用该套接字进行通信
		bzero(&peer_addr, sizeof(peer_addr));
		addr_len = sizeof(peer_addr);
		afd = accept(sfd, (struct sockaddr*)&peer_addr, &addr_len);
		if ( afd < 0 ) {
			perror("accpet()");
			return -1;
		}
		//sfd: 监听套接字  用来等待连接的
		//afd：连接套接字  用来通信的

		//5.read()/write()
		char buf[32];
		bzero(buf, 32);
		read(afd, buf, 32);
		printf("receive %s from %s %d\n", buf, 
				inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));

		char *p = "这里是东软睿道";
		write(afd, p, strlen(p));

		close(afd);
	}
	//6.close()
	close(sfd);
	return 0;
}
