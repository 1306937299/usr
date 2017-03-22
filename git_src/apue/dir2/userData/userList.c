#include "userList.h"


pUserList userlist_init()
{//1. 开辟一个结点空间  2.为结点的中成员初始化
	pUserList p;
	p = (pUserList)malloc(sizeof(sUserList));
	if ( p == NULL ) {
		perror("malloc");
		exit(1);
	}
	bzero(&p->data, sizeof(userInfo_t));

	p->next = p->prev = p;
	return p;
}

void userlist_destroy(pUserList p)
{
	if ( p != NULL ) {
		free(p);
		p = NULL;
	}
}

