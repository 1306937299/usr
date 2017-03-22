#include "network.h"


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
	int afd, fd;
	struct sockaddr_in peer_addr;
	socklen_t addr_len;
	c2s_t rcv_msg;
	s2c_t snd_msg;


	init_network();

	while (1) {
		//4.accept()
		bzero(&peer_addr, sizeof(peer_addr));
		addr_len = sizeof(peer_addr);
		afd = accept(sfd, (struct sockaddr*)&peer_addr, &addr_len);
		printf("connect with %s %d\n", inet_ntoa(peer_addr.sin_addr), 
				ntohs(peer_addr.sin_port));

		//5.read()/write()
		bzero(rcv_msg, sizeof(rcv_msg));
		recv(afd, rcv_msg, sizeof(rcv_msg), 0);

		fd = open(rcv_msg, O_RDONLY);
		if ( fd < 0 ) {//文本不存在
			bzero(&snd_msg, sizeof(snd_msg));
			snd_msg.type = S2C_NOEXIST;
			send(afd, &snd_msg, sizeof(snd_msg), 0);
		}
		else {
			while (1) {
				bzero(&snd_msg, sizeof(snd_msg));
				snd_msg.size = read(fd, snd_msg.filecontent, 
								sizeof(snd_msg.filecontent));
				if ( snd_msg.size <= 0 ) {
					break;
				}
				snd_msg.type = S2C_FILECONTENT;
				send(afd, &snd_msg, sizeof(snd_msg), 0);
			}
			bzero(&snd_msg, sizeof(snd_msg));
			snd_msg.type = S2C_FILEEND;
			send(afd, &snd_msg, sizeof(snd_msg), 0);
			close(fd);
		}


		//6.close()
		close(afd);
	}
	//7.close()
	destroy_network();
	return 0;
}
