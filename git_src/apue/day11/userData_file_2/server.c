#include "network.h"
#include <glob.h>
#include <pthread.h>
#include "ThreadPool.h"

int sfd = -1;				//UDP套接字

void init_network();		//初始化网络
void destroy_network();		//关闭网络



void register_func(const services_t *pmsg);
void    login_func(const services_t *pmsg);
void changepw_func(const services_t *pmsg);
void      cat_func(const services_t *pmsg);

void (*pfunc[])(const services_t *) = {
	NULL, register_func, login_func, changepw_func, cat_func
};

void init_userData()
{
	mkdir("./plugins", 0755);//创建用户资料的目录
}

void *thr_func(void *arg)
{
	services_t msg;

	while (1) {
		threadpool_get_services(&msg);

		pfunc[msg.cli_msg.req_type](&msg); 
		fprintf(stderr, "request deal Ok!\n");
	}
	return NULL;
}


int main(int argc, char **argv)
{
	socklen_t addr_len;
	int ret;
	services_t *msg;

	init_network();
	
	init_userData();

	threadpool_init(atoi(argv[1]), thr_func, NULL);


	while (1) {
		msg = malloc(sizeof(services_t));
		bzero(msg, sizeof(services_t));

		addr_len = sizeof(struct sockaddr_in);
		ret = recvfrom(sfd, &msg->cli_msg, sizeof(c2s_req_t), 0, 
							(struct sockaddr*)&msg->cli_addr, &addr_len);
		if ( ret <= 0 ) {
			break;
		}
		fprintf(stderr, "receive request type %u from <%s,%d>\n", 
						msg->cli_msg.req_type, inet_ntoa(msg->cli_addr.sin_addr), 
						ntohs(msg->cli_addr.sin_port));

		if ( msg->cli_msg.req_type <= C2S_REQ_MINFLAG || 
				msg->cli_msg.req_type >= C2S_REQ_MAXFLAG ) {
			fprintf(stderr, "unknow network request type\n");
			continue;
		}
		if ( msg->cli_msg.req_type == C2S_REQ_QUIT ) {//客户端退出的请求
			continue;
		} 
		threadpool_add_services(msg);
		free(msg);
	}

	threadpool_destroy();
	destroy_network();
	return 0;
}

void init_network()
{
	struct sockaddr_in addr;
	int ret;
	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if ( sfd < 0 ) {
		perror("socket()");
		exit(1);
	}

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7788);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
	if ( ret != 0 ) {
		perror("bind()");
		exit(1);
	}
}
void destroy_network()
{
	close(sfd);
}

void register_func(const services_t *pmsg)
{
	s2c_rep_t snd_msg;
	sleep(5);

	bzero(&snd_msg, sizeof(snd_msg));
	snd_msg.rep_type = S2C_REP_REGISTER;

	//查找注册用户是否存在  
	glob_t globres;
	char buf[64];
	int i;
	glob("./plugins/*", 0, NULL, &globres);
	// "./plugins/aaa" "./plugins/bbb" "./plugins/ccc"
	sprintf(buf, "./plugins/%s", pmsg->cli_msg.req_arg.register_arg.login_name);
	for ( i=0; i<globres.gl_pathc; i++) {
		if ( strcmp(buf, globres.gl_pathv[i]) == 0 ) {
			break;
		}
	}
	if ( i == globres.gl_pathc ) {//注册成功
		mkdir(buf, 0755);
		strcat(buf, "/info"); // "./plugins/ddd/info"
		int fd;
		fd = open(buf, O_WRONLY|O_TRUNC|O_CREAT, 0644);
		write(fd, &pmsg->cli_msg.req_arg.register_arg, sizeof(userInfo_t));
		close(fd);
		snd_msg.rep_arg.register_arg.op = S2C_REP_REGISTER_ACCEPT;
	}
	else {//注册失败
		snd_msg.rep_arg.register_arg.op = S2C_REP_REGISTER_REJECT;
	}
	sendto(sfd, &snd_msg, sizeof(snd_msg), 0, 
			(struct sockaddr*)&pmsg->cli_addr, sizeof(struct sockaddr_in));
	globfree(&globres);
}

void    login_func(const services_t *pmsg)
{
	s2c_rep_t snd_msg;

	sleep(10);

	bzero(&snd_msg, sizeof(snd_msg));
	snd_msg.rep_type = S2C_REP_LOGIN;

	//找用户
	glob_t globres;
	char buf[64];
	int i;
	glob("./plugins/*", 0, NULL, &globres);
	sprintf(buf, "./plugins/%s", pmsg->cli_msg.req_arg.login_arg.login_name);
	for ( i=0; i<globres.gl_pathc; i++) {
		if ( strcmp(buf, globres.gl_pathv[i]) == 0 ) {
			break;
		}
	}
	if ( i == globres.gl_pathc ) { //登录失败
		snd_msg.rep_arg.login_arg.op = S2C_REP_LOGIN_REJECT;
	}
	else {//用户找到了
		//判断密码
		userInfo_t info;
		int fd;
		strcat(buf, "/info");
		fd = open(buf, O_RDONLY);
		read(fd, &info, sizeof(info));
		close(fd);
		if ( strcmp(info.login_passwd, pmsg->cli_msg.req_arg.login_arg.login_passwd) == 0 ) {
			//登录成功
			snd_msg.rep_arg.login_arg.op = S2C_REP_LOGIN_ACCEPT;
			strcpy(snd_msg.rep_arg.login_arg.login_name, info.login_name);
			strcpy(snd_msg.rep_arg.login_arg.real_name, info.real_name);
			snd_msg.rep_arg.login_arg.user_sex = info.user_sex;
			snd_msg.rep_arg.login_arg.user_age = info.user_age;
		}
		else {//登录失败
			snd_msg.rep_arg.login_arg.op = S2C_REP_LOGIN_REJECT;
		}
	}

	sendto(sfd, &snd_msg, sizeof(snd_msg), 0, 
			(struct sockaddr*)&pmsg->cli_addr, sizeof(struct sockaddr_in));
}
void changepw_func(const services_t *pmsg)
{
	s2c_rep_t snd_msg;

	bzero(&snd_msg, sizeof(snd_msg));
	snd_msg.rep_type = S2C_REP_CHANGEPW;

	//找用户
	glob_t globres;
	char buf[64];
	int i;
	glob("./plugins/*", 0, NULL, &globres);
	sprintf(buf, "./plugins/%s", pmsg->cli_msg.req_arg.login_arg.login_name);
	for ( i=0; i<globres.gl_pathc; i++) {
		if ( strcmp(buf, globres.gl_pathv[i]) == 0 ) {
			break;
		}
	}
	if ( i == globres.gl_pathc ) { //查找失败
		snd_msg.rep_arg.changepw_arg.op = S2C_REP_CHANGEPW_REJECT;
	}
	else {
		userInfo_t info;
		int fd;
		strcat(buf, "/info");
		fd = open(buf, O_RDWR);
		read(fd, &info, sizeof(info));
		if ( strcmp(info.login_passwd, pmsg->cli_msg.req_arg.changepw_arg.old_passwd) == 0 ) {
			//密码相等
			bzero(info.login_passwd, sizeof(info.login_passwd));
			strcpy(info.login_passwd, pmsg->cli_msg.req_arg.changepw_arg.new_passwd);
			lseek(fd, 0, SEEK_SET);
			write(fd, &info, sizeof(info));
			snd_msg.rep_arg.changepw_arg.op = S2C_REP_CHANGEPW_ACCEPT;
		}
		else {//登录失败
			snd_msg.rep_arg.changepw_arg.op = S2C_REP_CHANGEPW_REJECT;
		}
		close(fd);
	}

	sendto(sfd, &snd_msg, sizeof(snd_msg), 0, 
			(struct sockaddr*)&pmsg->cli_addr, sizeof(struct sockaddr_in));

}

void      cat_func(const services_t *pmsg)
{
	s2c_rep_t snd_msg;
	int fd;
	int ret;

	fd = open(pmsg->cli_msg.req_arg.cat_arg.filename, O_RDONLY);
	if (fd < 0 ) {
		bzero(&snd_msg, sizeof(snd_msg));
		snd_msg.rep_type = S2C_REP_CAT;
		snd_msg.rep_arg.cat_arg.op = S2C_REP_CAT_NOEXIST;
		sendto(sfd, &snd_msg, sizeof(snd_msg), 0, 
			(struct sockaddr*)&pmsg->cli_addr, sizeof(struct sockaddr_in));
	}
	else {
		bzero(&snd_msg, sizeof(snd_msg));
		snd_msg.rep_type = S2C_REP_CAT;
		snd_msg.rep_arg.cat_arg.op = S2C_REP_CAT_EXIST;
		
		sendto(sfd, &snd_msg, sizeof(snd_msg), 0, 
			(struct sockaddr*)&pmsg->cli_addr, sizeof(struct sockaddr_in));
		int tcp_sfd;
		struct sockaddr_in addr;
		tcp_sfd = socket(AF_INET, SOCK_STREAM, 0);
		bzero(&addr, sizeof(addr));
		addr.sin_family =AF_INET;
		addr.sin_port = htons(8899);
		addr.sin_addr.s_addr = pmsg->cli_addr.sin_addr.s_addr;
		connect(tcp_sfd, (struct sockaddr*)&addr, sizeof(addr));
		char buf[64];
		while (1) {
			ret = read(fd, buf, 64);
			if ( ret <= 0 )
				break;
			send(tcp_sfd, buf, ret, 0);
		}

		close(tcp_sfd);
	}
}

