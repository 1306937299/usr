#include "network.h"

#define SERVER_PORT	7788


#ifndef SIP
#define SERVER_IP	"192.168.1.254"
#else
#define SERVER_IP	SIP
#endif

const char *psex[3] = {
	NULL, "男性", "女性"
};


int main()
{
	int sfd;
	struct sockaddr_in ser_addr;
	unsigned int choose;
	c2s_req_t snd_msg;
	s2c_rep_t rcv_msg;
	int ret;

	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if ( sfd < 0 ) {
		perror("socket()");
		return -1;
	}

	bzero(&ser_addr, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(SERVER_PORT);
	ser_addr.sin_addr.s_addr = inet_addr(SERVER_IP);


	while (1) {
		printf("1.login 2.register 3.quit:");
		scanf("%u", &choose);
		if ( choose == 1 ) {
			char login_name[NAME_LEN];

			bzero(&snd_msg, sizeof(snd_msg));
			snd_msg.req_type = C2S_REQ_LOGIN;
			printf("input login name:");
			scanf("%s", snd_msg.req_arg.login_arg.login_name);
			strcpy(snd_msg.req_arg.login_arg.login_passwd, getpass("input password:"));
			sendto(sfd, &snd_msg, sizeof(snd_msg), 0, 
					(struct sockaddr*)&ser_addr, sizeof(ser_addr));

			do {
				bzero(&rcv_msg, sizeof(rcv_msg));
				recv(sfd, &rcv_msg, sizeof(rcv_msg), 0);
			} while ( rcv_msg.rep_type != S2C_REP_LOGIN );
			if ( rcv_msg.rep_arg.login_arg.op == S2C_REP_LOGIN_ACCEPT ) {
				//登录成功
				printf("登录成功!\n");
				printf("<登录名:%s , 用户名:%s , 性别:%s , 年龄:%d>\n", 
						rcv_msg.rep_arg.login_arg.login_name,
						rcv_msg.rep_arg.login_arg.real_name,
						psex[rcv_msg.rep_arg.login_arg.user_sex], 
						rcv_msg.rep_arg.login_arg.user_age);

				strcpy(login_name, rcv_msg.rep_arg.login_arg.login_name);
				while (1) {
					printf("1.修改密码 2.显示文件 3.quit:");
					scanf("%u", &choose);
					if ( choose == 1 ) {
						bzero(&snd_msg, sizeof(snd_msg));
						snd_msg.req_type = C2S_REQ_CHANGEPW;
						strcpy(snd_msg.req_arg.changepw_arg.login_name, login_name);
						strcpy(snd_msg.req_arg.changepw_arg.old_passwd, getpass("输入旧密码:"));
						strcpy(snd_msg.req_arg.changepw_arg.new_passwd, getpass("输入新密码:"));
						sendto(sfd, &snd_msg, sizeof(snd_msg), 0, 
								(struct sockaddr*)&ser_addr, sizeof(ser_addr));
						do {
							bzero(&rcv_msg, sizeof(rcv_msg));
							recv(sfd, &rcv_msg, sizeof(rcv_msg), 0);
						} while ( rcv_msg.rep_type != S2C_REP_CHANGEPW );

						if ( rcv_msg.rep_arg.changepw_arg.op == S2C_REP_CHANGEPW_ACCEPT ) {
							printf("修改成功!\n");
						}
						else {
							printf("修改失败!\n");
						}

					}
					else if ( choose == 2 ) {
						bzero(&snd_msg, sizeof(snd_msg));
						snd_msg.req_type = C2S_REQ_CAT;
						printf("input filename:");	
						scanf("%s", snd_msg.req_arg.cat_arg.filename);
					
						int tcp_sfd;
						struct sockaddr_in addr;
						socklen_t addr_len;
						tcp_sfd = socket(AF_INET, SOCK_STREAM, 0);
						bzero(&addr, sizeof(addr));
						addr.sin_family = AF_INET;
						addr.sin_port = htons(8899);
						addr.sin_addr.s_addr= htonl(INADDR_ANY);
						ret = bind(tcp_sfd, (struct sockaddr*)&addr, sizeof(addr));
						if ( ret != 0 ) {
							perror("bind()");
							return -1;
						}
						listen(tcp_sfd, 1);


						sendto(sfd, &snd_msg, sizeof(snd_msg), 0, 
								(struct sockaddr*)&ser_addr, sizeof(ser_addr));

						do {
							bzero(&rcv_msg, sizeof(rcv_msg));
							recv(sfd, &rcv_msg, sizeof(rcv_msg), 0);
						} while ( rcv_msg.rep_type != S2C_REP_CAT );

						if ( rcv_msg.rep_arg.cat_arg.op == S2C_REP_CAT_NOEXIST ) {
							close(tcp_sfd);
						}
						else {
							int afd;
							char buf[64];
							bzero(&addr, sizeof(addr));
							addr_len = sizeof(addr);
							afd= accept(tcp_sfd, (struct sockaddr*)&addr, &addr_len);

							while (1) {
								ret = recv(afd, buf, sizeof(buf), 0);
								//recv接受TCP连接的数据时，如果对方将连接关闭，recv将返回0
								if ( ret <= 0 ) {
									break;
								}
								write(1, buf, ret);
							}
							close(afd);
							close(tcp_sfd);
						}


					}
					else if ( choose == 3 ) {
						break;
					}
				}
			}
			else {
				//登录失败
				printf("登录失败!\n");
			}
		}
		else if ( choose == 2 ) {
			bzero(&snd_msg, sizeof(snd_msg));
			snd_msg.req_type = C2S_REQ_REGISTER;
			printf("input login name:");
			scanf("%s", snd_msg.req_arg.register_arg.login_name);
			strcpy(snd_msg.req_arg.login_arg.login_passwd, getpass("input password:"));
			printf("input real name:");
			scanf("%s", snd_msg.req_arg.register_arg.real_name);
			printf("input sex(1.男性 2.女性):");
			scanf("%u", &snd_msg.req_arg.register_arg.user_sex);
			printf("input age:");
			scanf("%u", &snd_msg.req_arg.register_arg.user_age);

			sendto(sfd, &snd_msg, sizeof(snd_msg), 0, 
					(struct sockaddr*)&ser_addr, sizeof(ser_addr));

			do {
				bzero(&rcv_msg, sizeof(rcv_msg));
				recv(sfd, &rcv_msg, sizeof(rcv_msg), 0);
			} while ( rcv_msg.rep_type != S2C_REP_REGISTER );
			if ( rcv_msg.rep_arg.register_arg.op == S2C_REP_REGISTER_ACCEPT ) {
				printf("注册成功!\n");
			}
			else {
				printf("注册失败!\n");
			}
		}
		else if ( choose == 3 ) {
			break;
		}
	}

	close(sfd);
	return 0;
}

